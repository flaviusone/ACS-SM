#!/bin/bash
SIMPLE_OUTPUT="build/simple"

echo -e "# Running test 1 - Simple on all files..."
./$SIMPLE_OUTPUT inputs/1.jpg out/1_HSV.jpg
./$SIMPLE_OUTPUT inputs/2.jpg out/2_HSV.jpg
./$SIMPLE_OUTPUT inputs/3.jpg out/3_HSV.jpg
./$SIMPLE_OUTPUT inputs/4.jpg out/4_HSV.jpg