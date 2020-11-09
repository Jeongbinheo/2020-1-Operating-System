> # Operating-System
2020SS 운영체제 수업 TERM-PROJECT
Multi-Core Computer에 최적화된 다중 Matrix Multiplexing을 위한 Linux System Programming 과제

최근 AI에서의 GPU를 이용한 다중 행렬연산이 증가하면서 가지고 있는 Core를 최대한 활용할 수 있도록 thread 단위로 행렬연산을 수행하는 것이 중요해지고 있습니다. 

또한, 해당 과제는 교수님께서 전체적인 코딩과정을 보여주시면서 수업을 진행하신 내용에서 학생들 개개인의 Virtual Box의 image에 최적화된 코드로 변형하는 과제였습니다.
##
> #  구성 (클릭시 해당 목차로 이동)
1. [Virtual Box Spec](README.md#1.Virtual Box Spec)
2. [Matrix-Multiplexing](README.md#2.Matrix-Multiplexing)
3. [Linux System Programming](README.md#3.Linux System Programming)
  - thread 생성 함수
  - thread 당 multiplex 함수
  - main.c 에 대한 결과
 4. [발표 동영상 링크](README.md#4.발표 동영상 링크)

##
> ## 1. Virtual Box Spec
Virtual Box에 사용한 Linux Image Spec 
: Octa-Core Processor
<br/>

![structure](https://blogfiles.pstatic.net/MjAyMDExMDdfMjc4/MDAxNjA0NzMwOTk0MjQ1.cDh7wtLKLP9dJDAmDWcseTm4z2tg4_PQDqIOw1Ujg1kg.54XIzhxfb5oHTETRa2jTYc6qUdxTYHNdDS2UK75Yv14g.PNG.hdh988/VirtualBoxImage.png?type=w2)
##

> ## 2.Matrix Multiplexing

- mat_init 함수: 3개의 행렬을 생성하고 초기화 하는 함수 (main.c에 정의되어 있음)
 mat_init에는 A,B,C  세 개의 행렬을 이중 포인터 배열을 이용해 생성하고 
 생성된 A,B 행렬은 random number를 행렬의 배열에 채우고 
 C 행렬은 계산 결과가 들어가야 하므로 배열의 내부는 비워둔다.

  간단히 코드를 살펴보면 다음과 같다.
 ``` C
 void mat_init(int **(*p_a),int **(*p_b), int**(*p_c),int len)
 {
		int **a;
		int **b;
		int **c;

		a =(int**) malloc(len * sizeof(int*));
		b =(int**) malloc(len * sizeof(int*));
		c =(int**) malloc(len * sizeof(int*));
	 //len은 main 함수의 agrv로 입력하는 값 (행렬의 n x n에서 n을 의미)
	 //len의 수 만큼 배열 포인터(int*)를 메모리에 할당함 
	 //이후 이중 배열 포인터로 자료형 캐스팅해줌 (malloc은 void type을 반환해서) 
	  
	for(int i = 0; i<len; i++){
		a[i] = (int*)malloc(len * sizeof(int*));
		b[i] = (int*)malloc(len * sizeof(int*));
		c[i] = (int*)malloc(len * sizeof(int*));
	} 
	  //for 문을 통해 이중 배열을 완전하게 만드는 과정
 ```

 <br/>

- mat_mul 함수 : 행렬의 계산 기능을 담당하는 함수

  이중 배열 계산은 많은 코딩 수업에서 기초로 다루기 때문에 간단히 코드만으로 
  이해 하고 넘어갈 것!
 
  ``` c
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
  ```
## 3. Linux System Programming
 
 상위 2개의 함수들은 본인이 만든 mat_mul_thread3 함수를 실행시키면동작하는 함수들로 thread단위로 행렬 연산을 수행하고 thread 단위로 수행한 내용을 한번에 합치는 기능을 수행함.
 
- ### thread 생성 함수
```c     
  pthread_create 의 사용법 (Linux manual 참조) 
      #include <pthread.h>
	     int pthread_create(pthread_t *thread, const pthread_attr_t * attr,
		                   void *(*start_routine) (void *), void * arg);
 ```    
   **→ void(*start_rotine)(void*) : thread를 만들고 실행하는 시점.**
  
   **→ 해당 프로젝트에는 mat_mul_th_kernel3이 들어가고,  thread별로 행렬 계산을 수행함.**
  ```C
    Example)
    res = pthread_create(a_thread+i, NULL, mat_mul_th_kernel3, (void*)arg);
  ```

- ### thread에서 수행한 결과를 합치는 함수 
   pthread_join : thread들이 terminated 될 때까지 기다려주는 함수.
   ```c
  pthread_join 의 사용법 (Linux manual 참조)
      #include <pthread.h>
       int pthread_join(pthread_t *thread, void** retval);
  ```
  
    **→ 프로젝트에서 사용되는 방식**
  ```c
 	for (i = 0; i<num_thread; i++){ //i(row)
			res = pthread_join(a_thread[i], &thread_result);
				if (res!=0){
					perror("Thread creation failed");
					exit(EXIT_FAILURE);
				}
		}
  ```		

 
- ### Octa-core에 최적화 시키기 위한 전략
 기존에는 행의 갯수 만큼 thread를 생성했지만, 바뀐 전략에는  num_thread와 count라는 변수를 추가해서 num_thread 갯수를 직접 args자리에 입력하여 
 내가 원하는 수의 thread 만큼 생성하여 processor 갯수에 최적화된 연산이 가능해짐.

 발표 동영상을 참조하면 수월하게 이해가 가능함.

## 4.  발표 동영상 링크

프로젝트 코드 및 시뮬레이션 과정을 영상으로 남기는 추가과제로 Youtube 링크를 통해 시청가능합니다. (사진 클릭시 시청 가능)


[![Watch the video](https://img.youtube.com/vi/-yNb5eh-dnc/maxresdefault.jpg)](https://www.youtube.com/watch?v=-yNb5eh-dnc&feature=youtu.be)
