#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int mat_mul(int** src1, int** src2, int** dst, int len)
{
	int i,j,k;
	int result;

	for (i = 0; i<len; i++){ //i(row)
		for(j = 0; j<len; j++){ //j(column)
		result = 0;
			for(k = 0; k<len; k++){
			
			result += src1[i][k] * src2[k][j];
		
			}
		}
		dst[i][j] = result;

	}
}


typedef struct{
	int i;
	int** src1;
	int** src2;
	int** dst;
	int len;
}matmul_arg_t;

// int mat_mul_th_kernel(int i, int** src1, int** src2, int** dst, int len)
void* mat_mul_th_kernel(void *arg)
{

	int 		j,k,result;
	matmul_arg_t* 	parg = (matmul_arg_t*)arg;
	int 		i = parg->i;
	int 		**src1 = parg -> src1;
	int 		**src2 = parg -> src2;
	int 		**dst = parg -> dst;
	int 		len = parg -> len;
	
	for(j = 0; j<len; j++){ //j(column)
		result = 0;
			for(k = 0; k<len; k++){
				result += src1[i][k] * src2[k][j];
			}
		dst[i][j] = result;
	}
}

int mat_mul_thread(int** src1, int** src2, int** dst, int len)
{
	int 		i,j,k,res;
	matmul_arg_t 	*arg;
	pthread_t 	*a_thread;
	void 		*thread_result;

	a_thread = (pthread_t*)malloc(sizeof(pthread_t) * len);


	for (i = 0; i<len; i++){ //i(row)
		arg = (matmul_arg_t*)malloc(sizeof(matmul_arg_t));
		
		arg->i = i;
		arg->src1 = src1;	
		arg->src2 = src2;	
		arg->dst = dst;
		arg->len = len;
		
		//mat_mul_th_kernel((void*)&arg);
		res = pthread_create(a_thread+i, NULL, mat_mul_th_kernel, (void*)arg);
		if (res!=0){
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	
	for (i = 0; i<len; i++){ //i(row)
		res = pthread_join(a_thread[i], &thread_result);
		if (res!=0){
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}		

	return 0;	
}


int mat_inv(int** src, int** dst, int len)
{




}

int mat_add(int** src1, int** src2, int** dst, int len)
{

	int i,j,k;

	for (i = 0; i<len; i++){ //i(row)
		for(j = 0; j<len; j++){ //j(column)
		dst[i][j] = 0;
			for(k = 0; k<len; k++){
			
			dst[i][j] += src1[i][k] * src2[k][j];
		
			}
		}

	}

}
int mat_sub(int** src1, int** src2, int** dst, int len)
{

	int i,j,k;

	for (i = 0; i<len; i++){ //i(row)
		for(j = 0; j<len; j++){ //j(column)
		dst[i][j] = 0;
			for(k = 0; k<len; k++){
			
			dst[i][j] += src1[i][k] * src2[k][j];
		
			}
		}

	}

}



