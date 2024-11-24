
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <pthread.h> 
  
// A normal C function that is executed as a thread  
// when its name is specified in pthread_create() 
void *myThread(void *vargp) 
{ 
int i;
   // sleep(1); 
    for(i=0;i<10;i++)
	{if( i%2==0)
		printf("%d is even\n",i);}
    return NULL; 
} 


int main() 
{ 
    int i;
    pthread_t thread_id ; //declared the thread identifier
    printf("Before Thread\n"); 
    pthread_create(&thread_id, NULL, myThread, NULL); //create the threads
    //pthread_create(&thread_id2, NULL, myThread, NULL); //create the threads
    for(i=0;i<100;i=i+10){
	printf("Multiples of 10 are %d\n",i);
    printf("hello\n");}
    pthread_join(thread_id, NULL); // ensures that the main() thread waits for the created thread to finish before exiting.
//pthread_join(thread_id2, NULL); 
    printf("After Thread\n"); 
    exit(0); 
}

