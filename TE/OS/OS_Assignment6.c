#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
 
#define LEFT (ph_num+4)%5
#define RIGHT (ph_num+1)%5
 
sem_t mutex,S[5];
int state[5],phil_num[5]={0,1,2,3,4};
 
void *philospher(void *num)
{   
 while(1)
 {   
  int *i=num;
  sleep(1);
  take_fork(*i);
  sleep(0);
  put_fork(*i);
 }
}
 
void take_fork(int ph_num)
{   
 sem_wait(&mutex);
 state[ph_num]=1;
 printf("Philosopher %d is Hungry \n",ph_num+1);
 test(ph_num);
 sem_post(&mutex);
 sem_wait(&S[ph_num]);
 sleep(1);
}
 
void test(int ph_num)
{   
 if(state[ph_num]==1 && state[LEFT]!=2 && state[RIGHT]!=2)
 {   
  state[ph_num] = 2;
  sleep(2);
  printf("Philosopher %d Takes Fork %d and %d \n",ph_num+1,LEFT+1,ph_num+1);
  printf("Philosopher %d is Eating \n",ph_num+1);
  sem_post(&S[ph_num]);
 }
}
 
void put_fork(int ph_num)
{   
 sem_wait(&mutex);
 state[ph_num]=0;
 printf("Philosopher %d Putting Fork %d and %d Down \n",ph_num+1,LEFT+1,ph_num+1);
 printf("Philosopher %d is Thinking \n",ph_num+1);
 test(LEFT);
 test(RIGHT);
 sem_post(&mutex);
}

int main()
{   
 pthread_t thread_id[5];
 sem_init(&mutex,0,1);

 for(int i=0;i<5;i++)
 sem_init(&S[i],0,0);

 for(int i=0;i<5;i++)
 {
  pthread_create(&thread_id[i],NULL,philospher,&phil_num[i]);
  printf("Philosopher %d is Thinking \n",i+1);
 }
 for(int i=0;i<5;i++)
 pthread_join(thread_id[i],NULL);
}