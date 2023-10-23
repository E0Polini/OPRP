#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mpi.h>
#include <crypt.h>
#include <omp.h>


#define MAX 4

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

void testaSenhas(int i, char* entrada, int rank);

int flag=0;
