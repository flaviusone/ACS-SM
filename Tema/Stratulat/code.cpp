#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <jpeglib.h>
#include <math.h>

#if defined(MPI_MODE)
  #include <mpi.h>
#elif defined(PTHREADS_MODE)
  #define THREAD_LOAD 7740
  #include <pthread.h>
#endif

using namespace std;

#define EPSILON 0.02

int img_cols;
int img_rows;

static int minf(uint8_t a, uint8_t b, uint8_t c) {
    if ((a < b) && (a < c)) {
        return a;
    } else if ((b < a) && (b < c)) {
        return b;
    } else {
        return c;
    }
}

static int maxf(uint8_t a, uint8_t b, uint8_t c) {
    if ((a > b) && (a > c)) {
        return a;
    } else if ((b > a) && (b > c)) {
        return b;
    } else {
        return c;
    }
}


static void RGBtoHSV(uint8_t * src) {
    uint8_t min, max;
    float max2;
    float delta;
    float h;

    min = minf(src[0], src[1], src[2]);
    max = maxf(src[0], src[1], src[2]);

    max2 = max + EPSILON;

    delta = max2 - min;

    if (src[0] == max)
        h = (src[1] - src[2]) / delta;
    else if (src[1] == max)
        h = 2 + (src[2] - src[0]) / delta;
    else
        h = 4 + (src[0] - src[1]) / delta;

    h *= 60;
    if (h < 0)
        h += 360;

    src[0] = (h / 360.) * 255;
    src[1] = delta * 255 / max2;
    src[2] = max;
}

static void RGBtoHSL(uint8_t * src) {
    uint8_t min, max;
    float max2;
    float delta;
    float h, l;

    min = minf(src[0], src[1], src[2]);
    max = maxf(src[0], src[1], src[2]);

    max2 = max + EPSILON;

    delta = max2 - min;

    if (src[0] == max)
        h = (src[1] - src[2]) / delta;
    else if (src[1] == max)
        h = 2 + (src[2] - src[0]) / delta;
    else
        h = 4 + (src[0] - src[1]) / delta;

    h *= 60;
    if (h < 0)
        h += 360;

    l = (max + min) / 2;
    src[0] = (h / 360.) * 255;
    src[1] = delta / (1 - fabs(2*l - 1));
    src[2] = l;
}

static uint8_t *read_jpeg(char *filename) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    uint8_t *raw_image;
    uint8_t *t;
    FILE *infile = fopen(filename, "rb");

    if (!infile) {
        printf("Error opening jpeg file %s\n!", filename);
        return NULL;
    }

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    img_rows = cinfo.output_height;
    img_cols = cinfo.output_width;
    assert(cinfo.num_components == 3);

    printf("%d %d\n", img_rows, img_cols);
    raw_image = (uint8_t *) malloc(img_rows * img_cols * cinfo.num_components);

    for (int i = 0; i < img_rows; ++i) {
        t = &(raw_image[img_cols * cinfo.num_components * i]);
        jpeg_read_scanlines(&cinfo, &t, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);

    return raw_image;
}


#ifdef PTHREADS_MODE

void *process_some_pixels(void* ptr){
    uint8_t* m1 = (uint8_t*) ptr;
    for (int i = 0; i < THREAD_LOAD; i++) {
        RGBtoHSV(m1 + i * 3);
    }
}

#endif

int main(int argc, char **argv) {
    uint8_t *m1;
    int max;
    clock_t t;

#ifdef MPI_MODE 
    uint8_t* local_buffer;

    int world_size, world_rank;
    int local_buffer_size;
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    if(world_rank == 0){
#endif

        printf("opening file...\n");
        m1 = read_jpeg(argv[1]);
        printf("File read...\n");

        t = clock();

#if defined(MPI_MODE)
        local_buffer_size = img_rows * img_cols / world_size;
    }

    MPI_Bcast(&local_buffer_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("CPU %d of %d processed %d\n", world_rank, world_size, local_buffer_size);
    local_buffer = (uint8_t*)malloc(3 * local_buffer_size);

    MPI_Scatter(m1, 3 * local_buffer_size, MPI_CHAR, local_buffer, 3 * local_buffer_size, MPI_CHAR, 0, MPI_COMM_WORLD);
    for( int i = 0; i < local_buffer_size; i++){
        RGBtoHSV(local_buffer + i * 3);
    }

    MPI_Gather(local_buffer, 3 * local_buffer_size, MPI_CHAR, m1, 3 * local_buffer_size, MPI_CHAR, 0, MPI_COMM_WORLD);

#elif defined(OMP)

    #pragma omp parallel for
    for (int i = 0; i < img_rows * img_cols; i++) {
        RGBtoHSV(m1 + i * 3);
    }

#elif defined(PTHREADS_MODE)

    pthread_t *threads;

    assert(img_rows * img_cols % THREAD_LOAD == 0);
    
    int n_threads = img_rows * img_cols / THREAD_LOAD;
    threads = (pthread_t*)malloc(n_threads * sizeof(pthread_t));

    for (int i = 0; i < img_rows * img_cols; i+=THREAD_LOAD){
        pthread_create( threads + i / THREAD_LOAD, NULL, process_some_pixels, m1 + i * 3);
    }    
    for (int i = 0; i < n_threads; i++){
        pthread_join(threads[i], NULL);
    }

#else /*regular*/

    for (int i = 0; i < img_rows * img_cols; i++) {
        RGBtoHSV(m1 + i * 3);
    }

#endif

#ifdef MPI_MODE
    if(world_rank == 0){
#endif
        t = clock() - t;
        printf("It took me %d clicks (%f seconds).\n", t,
               ((float) t) / CLOCKS_PER_SEC);

        FILE *f2;
        f2 = fopen(argv[2], "wb");

        fwrite(m1, img_rows, img_cols*3, f2);

#ifdef MPI_MODE
    }
    MPI_Finalize();
#endif

    return 0;
}
