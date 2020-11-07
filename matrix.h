
int mat_add(int**, int**, int**, int);
int mat_sub(int**, int**, int**, int);
int mat_mul(int**, int**, int**, int);
int mat_inv(int**, int**, int len);
int mat_mul_thread3(int**, int**, int**, int, int);
int mat_mul_th_kernel3(int, int**, int**, int**, int);
int mat_mul_ready(void*);

