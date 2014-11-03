from sys import stdin
from math import *

print "No entrys:",
entry = int(stdin.readline())
print "No connections:",
connections = int(stdin.readline())

inputs = [];
outputs = [];

for i in xrange(0 , connections):
	print "Input %d:" % (i),
	inputs.append(int(stdin.readline()));
	print "Output %d:" % (i),
	outputs.append(int(stdin.readline()));

stages = int(log(entry,2));
mat = [[0 for y in range(stages+1)] for x in range(entry)];

print "Computing...";

for i in xrange(0, connections):

	xor_tag = inputs[i] ^ outputs[i];

	print"Input %d to output %d" % (inputs[i], outputs[i])

	if(inputs[i] < 4):
		inputs[i] <<= 1
	else:
		inputs[i] <<= 1;
		inputs[i] +=  1;
		inputs[i] &=  7;
	if(mat[inputs[i]][0]):
		print "Conflict";
	else:
		# print "Mat[%d][%d] = %d" % (inputs[i],0,mat[inputs[i]][0])
		mat[inputs[i]][0] = 1;
		for j in xrange(0, stages):
			comut = xor_tag & (1 << (stages-j-1))

			print "Switch on stage %d - " % (stages-j-1),

			# Direct
			if (comut == 0):
				# Unde trebuie sa rutez
				if(inputs[i] < 4):
					inputs[i] <<= 1
				else:
					inputs[i] <<= 1;
					inputs[i] +=  1;
					inputs[i] &=  7;
				if(mat[inputs[i]][j+1]):
					print "Conflict";
					break;
				else:
					# print "Mat[%d][%d] = %d" % (inputs[i],j+1,mat[inputs[i]][j+1])
					mat[inputs[i]][j+1] = 1;
					print "Direct (C0 = 0; C1 = 0)"
			# Cross
			else:
				# Verific daca fac cross in sus sau in jos
				if (inputs[i] % 2 == 0):
					inputs[i]+=1;
				else:
					inputs[i]-=1;

				#  Unde trebuie sa rutez
				if(inputs[i] < 4):
					inputs[i] <<= 1
				else:
					inputs[i] <<= 1;
					inputs[i] +=  1;
					inputs[i] &=  7;

				if(mat[inputs[i]][j+1]):
					print "Conflict";
					break;
				else:
					# print "Mat[%d][%d] = %d" % (inputs[i],j+1,mat[inputs[i]][j+1])
					mat[inputs[i]][j+1] = 1;
					print "Invers (C0 = 1; C1 = 1)"
