#include <stdio.h>;
#include <pthread.h>;

//The copy of the function declaration
void *writeMessage(void *ptr);

int main(void) {

    //Allocating the memory for the necessary threads
    pthread_t firstThread, secondThread; 

    const char *messageFirstThread = "First thread";
    const char *messageSecondThread = "Second thread";

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

    return 0;
}

// (void *ptr) ensures we can add any argument, no matter what the type of the argument is
void *writeMessage(void *ptr) {

    char *message;
    message = (char *)ptr; //Casting - void to string
    printf("%s \n", message);

}