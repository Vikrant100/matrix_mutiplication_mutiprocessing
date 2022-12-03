#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <omp.h>
#include <math.h>

typedef double NEW_TYPE;
#define maximum_dimension 2000*2000 // define maximum dimesion for the matrix
#define maximum_value 10		// these two just specifyy that element in a matrix is between 1 to 10
#define minimum_value 1


NEW_TYPE** random_square_matrix(int dimension)  //generate a random sqaure matrix using this function
{
    NEW_TYPE** matrix = malloc(dimension * sizeof(NEW_TYPE*));
    for(int i=0; i<dimension; i++)
    {
		matrix[i] = malloc(dimension * sizeof(NEW_TYPE));
	}
    #pragma omp parallel for
	for(int i=0; i<dimension; i++)
    {
		for(int j=0; j<dimension; j++)
        {
			matrix[i][j] = rand() % maximum_value + minimum_value;
		}
	}

	return matrix;
}

NEW_TYPE** zero_square_matrix(int dimension)  // generate an empty square matrix for storing for result
{
    NEW_TYPE** matrix = malloc(dimension * sizeof(NEW_TYPE*));
    for(int i=0; i<dimension; i++)
    {
		matrix[i] = malloc(dimension * sizeof(NEW_TYPE));
	}
    #pragma omp parallel for
	for(int i=0; i<dimension; i++)
    {
		for(int j=0; j<dimension; j++)
        {
			matrix[i][j] = 0;
		}
	}

	return matrix;
}

double ParallelWithPragma(NEW_TYPE** matrix_A, NEW_TYPE** matrix_B, NEW_TYPE** matrix_C, int size) // function handles open Mp pragama and logic for matrix mutiplication
{
	int i = 0, j = 0, k = 0, jj = 0, kk = 0;
	float tmp;
	int chunk = 2;
	int thread_no;
	int block_size = 16;
	struct timeval t0, t1;
	//printf ("%d",size);
	gettimeofday(&t0, 0);
    #pragma omp parallel shared(matrix_A, matrix_B, matrix_C, size, chunk) private(i, j, k, jj, kk, thread_no, tmp)
	{
		thread_no = omp_get_thread_num();
		if (thread_no == 0)
		{
			printf ("Number of pragma threads             |      %d",omp_get_num_threads()); 
			printf ("\n");
		}
		#pragma omp for schedule (static, chunk)
        for (jj = 0; jj < size; jj += block_size)
		{
			
			for (kk = 0; kk < size; kk += block_size)
			{
				for (i = 0; i < size; i++)
				{
					for (j = jj; j < ((jj + block_size) > size ? size : (jj + block_size)); j++)
					{
						tmp = 0.0f;
						for (k = kk; k < ((kk + block_size) > size ? size : (kk + block_size)); k++)
						{
							tmp += matrix_A[i][k] * matrix_B[k][j];
						}
						matrix_C[i][j] += tmp;
					}
				}
			}
		}
    }
    gettimeofday(&t1, 0); 
	double elapsed = (t1.tv_sec-t0.tv_sec) * 1.0f +  (t1.tv_usec - t0.tv_usec)/ 1000000.0f; // create time of task compeletion in seconds

	return elapsed;
}

void matrix_dimension(int dimension) // Print data on the screen by calling and getting results from the functions as per requirement
{
    printf("-------------------------------------------------------\n");
    printf("Dimension = %d x %d\n", dimension,dimension);
    printf("-------------------------------------------------------\n");
    double* latency = malloc(4 * sizeof(double));
	NEW_TYPE** matrix_A = random_square_matrix(dimension);
	NEW_TYPE** matrix_B = random_square_matrix(dimension);

    NEW_TYPE** Result = zero_square_matrix(dimension);
	latency[0] = ParallelWithPragma(matrix_A, matrix_B, Result, dimension);
	free(Result);
    printf("Matrix Multiplication with pragma    |\t%f\n", latency[0]);
		
	free(latency);
	free(matrix_A);
	free(matrix_B);
}

int main(int argc, char* argv[])  // Generate dimension for the matrix with the incremment of 200 on each run 
{
	
	for(int dimension=200; dimension<=2000; dimension+=200)
    {
		matrix_dimension(dimension);
	}

	return 0;
}

