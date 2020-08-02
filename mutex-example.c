#include <stdio.h>
#include <pthread.h>

//The copy of the function declaration
void *changeValue(void *ptr);

//Global variable - value
int value;

//Mutex - a structure used to ensure there is no entaglement between the threads
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void){

    value = 0;

  //Allocating the memory for the necessary threads
    pthread_t firstThread, secondThread;

    //pthread_create returns a status code, which we'll save into two variables
    int statusCode1, statusCode2;

       //the status code should be 0, otherwise, an error occured
    statusCode1 = pthread_create(&firstThread, NULL, writeMessage,(void*)messageFirstThread);

    /*
    Parameters:
    1) A pointer to the memory chunk where the thread will allocate
    2) Extra options
    3) A pointer to the function that executes with each instance of the thread
    4) The parameters of the function from parameter number 3
    */
    statusCode2 = pthread_create(&secondThread, NULL, writeMessage,(void*)messageSecondThread);

       //Printing the status codes to see if the threads are executed correctly
    printf("Status code - First Thread: %d\n",statusCode1);
    printf("Status code - Second Thread: %d\n",statusCode2);

    //Returning to the main thread
    pthread_join(firstThread, NULL);
    pthread_join(secondThread, NULL);
    /*
    Parameters:
    1) The thread which is being redirected back to the main thread
    2) The pointer to the location where the status code of the pthread_join function will be stored
    */

    printf("Value is: %d\n", value);
    return 0;
}

// (void *ptr) ensures we can add any argument, no matter what the type of the argument is
void *changeValue(void *ptr){

    int i;

    //Locking the resources before the incrementation
    pthread_mutex_lock(&mutex);

    for(i = 0; i < 100000000; i++){
        value++;
    }

    //Unlocking the resources after the incrementation
    pthread_mutex_unlock(&amutex); 
}