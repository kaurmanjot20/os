#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<semaphore.h>
using namespace std;
//sem_t s;
int main()
{
	//sem_init(&s,1,1);
	// ftok to generate unique key
	key_t key = ftok("sema.c", 65);
	key_t keys = ftok("s", 65);
	// shmget returns an identifier in shmid
	int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
	int shmid2 = shmget(keys, 1024, 0666 | IPC_CREAT);

	// shmat to attach to shared memory
	int* str = (int*)shmat(shmid, (void*)0, 0);
	sem_t* s = (sem_t*)shmat(shmid2, (void*)0, 0);
	sem_init(s,1,1);
	sem_wait(s);
	*str= 4;
	(*str)++;
	sem_post(s);

	cout << "Data written in memory: " << *str << endl;

	// detach from shared memory
	shmdt(str);

	return 0;
}

