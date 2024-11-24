//sender
#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;

int main()
{
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    char* str = (char*)shmat(shmid, (void*)0, 0);

    cout << "Write Data : ";
    cin.getline(str, 1024);

    cout << "Data written in memory: " << str << endl;

    // detach from shared memory
    shmdt(str);


    return 0;
}
