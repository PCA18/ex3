#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "utils.h"


double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double** initMat(int size, double init_val){

	int i, j; 
  
  	// Allocation of Matrix
    double **mat = (double **)malloc(size * sizeof(double *)); 
    for (i=0; i<size; i++)
    	mat[i] = (double *)malloc(size * sizeof(double)); 
  
    // Note that arr[i][j] is same as *(*(arr+i)+j) 
    
    for (i = 0; i <  size; i++)
    {
		for (j = 0; j < size; j++)
		{
			if(j+1==size || i+1 == size || j== 0 || i == 0)		mat[i][j] = 0;
			else	mat[i][j] = init_val;
		}
	}  // OR *(*(mat+i)+j) = ++count 
  
  /*
    for (i = 0; i <  size; i++) 
      for (j = 0; j < size; j++) 
         printf("%lf ", mat[i][j]); */
  
   return mat; 
}

double** init_temp_mat(int size){

	int i, j; 
  
    double **mat = (double **)malloc(size * sizeof(double *)); 
    for (i=0; i<size; i++)
    	mat[i] = (double *)malloc(size * sizeof(double)); 
    
    for (i = 0; i <  size; i++)
    {
		for (j = 0; j < size; j++)
		{
			mat[i][j] = 0;
		}
	}
  
  /*
    for (i = 0; i <  size; i++) 
      for (j = 0; j < size; j++) 
         printf("%lf ", mat[i][j]); */

   return mat; 
}

void init_circle(double** mat, int param_grid_size, int diameter_m, double H)
{
	// int grid_size = param_grid_size;
	double center = float(param_grid_size-1)/2;
	int z,s;
	for (z=1; z<param_grid_size-1; ++z)
	{
		for (s=1; s<param_grid_size-1; ++s)
		{
			if (pow(float(z-center),2) + pow(float(s-center),2) <= pow(float(diameter_m)/2,2))	mat[z][s] = H;
		}
	}
}

void copyMatrix(double** mat, double** temp_mat , int size)
{	
	for(int z=0; z<size; ++z)
	{
		for(int s=0; s<size; ++s)
			temp_mat[z][s] = mat[z][s];
	}
}	

void relax(double** mat, double** temp_mat , int size)
{		
	copyMatrix(mat, temp_mat, size);

	for (int z = 1; z < size-1; ++z)
	{
		for(int s = 1; s < size-1; ++s)
		{
		mat[z][s] = temp_mat[z][s] + 0.24*((-4)*temp_mat[z][s]  + temp_mat[z+1][s] + temp_mat[z-1][s] + temp_mat[z][s+1] + temp_mat[z][s-1]);
		//printf("%f \n", mat[z][s]);
		}
	}
}




int main(int argc, char* argv[])
{
	//terminal parameter
	int grid_size_N = strtol(argv[1], NULL, 10)+2;		// index abfrage für 0!!!!	
	int diameter_m = strtol(argv[2], NULL, 10);
	double H = strtof(argv[3], NULL);
	int iter = strtol(argv[4], NULL, 10);
	double init_val_H = strtof(argv[5], NULL);
	double** mat = initMat(grid_size_N, init_val_H );
	double** temp_mat = init_temp_mat(grid_size_N);
	init_circle(mat,grid_size_N, diameter_m, H);
	
	

    // Note that arr[i][j] is same as *(*(mat+i)+j)
 //    printf("\nmat\n"); 

	// int i,j;
 //    for (i = 0; i <  grid_size_N; i++)
 //    { 
	// 	for (j = 0; j < grid_size_N; j++)
	// 	{ 
	// 		if (j+1 == grid_size_N)
	// 		{
	// 			printf("%.2f\n", mat[i][j]);
	// 		}
	// 		else
	// 		{
	// 			printf("%.2f    ", mat[i][j]);
	// 		}
	// 	}
	// }
	// printf("\n");

	time_t now;
	time_t not_now;
	time_t cylces = 0;
	time_t cylces_ave;

	for (int itr=0; itr<iter; itr++)
	{
		rdtsc(now);
		// time_t now_1;
		// now_1 = time(NULL);

		relax(mat, temp_mat, grid_size_N);

		// for (i = 0; i <  grid_size_N ; i++)
		// { 
		// 	for (j = 0; j < grid_size_N ; j++)
		// 	{ 
		// 		if (j+1 == grid_size_N && i+1 <grid_size_N)
		// 		{
		// 			printf("%.2f\n", mat[i][j]);
		// 		}
		// 		else
		// 			if (j+1 == grid_size_N && i+1 == grid_size_N)
		// 			{
		// 				printf("%.2f\n\n\n", mat[i][j]); 
		// 			}         
		// 			else
		// 			{
		// 				printf("%.2f    ", mat[i][j]);
		// 			}
		// 	}
		// }

		rdtsc(not_now);
		time_t cycles_new = not_now - now;
		cylces += cycles_new;
		cylces_ave = cylces/(itr + 1);
		printf ("Cylcles fuer diese Iteration  = %ld\n", cycles_new);
		printf ("Cycles Durchschnitt  = %ld\n", cylces_ave);
		// time_t not_now_1;
		// not_now_1 = time(NULL);
	}
	
	// printf ("Zeit mit utils.h  = %ld\n", (not_now - now));
	// printf ("Zeit mit time.h = %ld\n",   (not_now_1 - now_1));

	return(0);
}

