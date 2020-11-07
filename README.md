# Operating-System
2020SS 운영체제 수업 TERM-PROJECT
Multi-Core Computer에 최적화된 다중 Matrix Multiplexing을 위한 Linux System Programming 과제

최근 AI에서의 GPU를 이용한 다중 행렬연산이 증가하면서 가지고 있는 Core를 최대한 활용할 수 있도록 thread 단위로 행렬연산을 수행하는 것이 중요해지고 있습니다. 

또한, 해당 과제는 교수님께서 전체적인 코딩과정을 보여주시면서 수업을 진행하신 내용에서 학생들 개개인의 Virtual Box의 image에 최적화된 코드로 변형하는 과제였습니다.

#  구성 (클릭시 해당 목차로 이동)
1. [Virtual_Box_Spec](README.md#Virtual_Box_Spec)
2. [Matrix-Multiplexing](README.md#Matrix-Multiplexing)
3. [Linux_System_Programming](README.md#Linux_System_Programming)
  - thread 생성 함수
  - thread 당 multiplex 함수
  - main.c 에 대한 결과
 4. [발표_동영상_링크](README.md#발표_동영상_링크)

## 1.  Virtual_Box_Spec
Virtual Box에 사용한 Linux Image Spec 
: Octa-Core Processor
