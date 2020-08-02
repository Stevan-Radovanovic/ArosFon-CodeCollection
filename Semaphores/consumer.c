#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>

//Defining the necessary constants
#define buffer 1024
#define elements 10

//Defining names for the POSIX semaphores
char SEM_NAME1[]="sem1";
char SEM_NAME2[]="sem2";

int main() {

	int i;
    //Shared memory
	int *shm;

    //Key - an integer - used for shared memory requests
	key_t key = 1000;

    //Allocating memory for the POSIX semaphores 
	sem_t* semaphore1; 
	sem_t* semaphore2;
	
	//Initializing the semaphores, returns the address o the newly created semaphore
	semaphore1 = sem_open(SEM_NAME1,O_CREAT,0644,0);
	semaphore2 = sem_open(SEM_NAME2,O_CREAT,0644,0);
    //O_CREAT - create only if it doesn't already exists
    //0644 - READ/WRITE/EXECUTE permissions
    //0 - Initial value of the semaphore
	
    //Returns a pointer to the shared memory chunk
    //Buffer - the size of the segment
	int shmid = shmget(key,buffer,IPC_CREAT | 0666);

    //Returns the memory location of the shared memory segment
	shm = shmat(shmid, (void *) 0,0);

	for(i=1;i<=elementi;i++){

        //Increments the semaphore value, signaling the producer to send an e-mail
		sem_post(semaphore1);

        //Decrementing the value and locks the semaphore until it's incremented again
		sem_wait(semaphore2);
		printf("Consumer read e-mail: %d\n",*shm);

	}
	
    //Freeing up the memory
	sem_close(semaphore1);
	sem_unlink(SEM_NAME1);
	sem_close(semaphore2);
	sem_unlink(SEM_NAME2);
	shmctl(shmid,IPC_RMID,0);
}