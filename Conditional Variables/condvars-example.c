#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//Defining a constant
#define NUMBER_OF_MESSAGES 10

//Global variable
int mailbox = 0;

//Defining a mutex
pthread_mutex_t the_mutex;

//Defining two conditional variables
pthread_cond_t condc,condp;

void* producer(void *ptr) {

    int i;

    //Every cicle represents a message sent
    for(i = 1; i<=NUMBER_OF_MESSAGES; i++) {
        //Synchronizing the messages by locking the resources
        pthread_mutex_lock(&the_mutex);

        //Checking if the mailbox is full
        while (mailbox != 0) {
            //While we wait for our message to be read, we release the mutex
            pthread_cond_wait(&condp, &the_mutex);
        }

        //Sending the mail
        mailbox = i;
        printf("Producer: Sent mail number %d \n", i);

        //Sending a signal that we sent an e- mail
        pthread_cond_signal(&condc);

        //Unlocking the mutex
        pthread_mutex_unlock(&the_mutex);

        //Simulating a pause between the e-mails
        sleep(rand()%10);
    }

}

void* consumer(void *ptr) {
    int i;

    //Every cicle represents a message read
    for(i = 0;i <=NUMBER_OF_MESSAGES;i++) {
        //Synchronizing the messages by locking the resources
        pthread_mutex_lock(&the_mutex);

        //Checking if the mailbox is empty
        while(mailbox == 0) {
            //Waiting for an e-mail to be sent
            pthread_cond_wait(&condc,&the_mutex);
        }

        printf("Consumer: Received mail number %d\n",mailbox);

        //Emptying the mailbox
        mailbox = 0;

        //Sending a signal that we read an e- mail
        pthread_cond_signal(&condp);

        //Unlocking the mutex
        pthread_mutex_unlock(&the_mutex);
        
        //Simulating a pause between the e-mails
        sleep(rand()%10);
    }
}

int main(void){

    pthread_t pro,con;

    //Initializing the resources
    pthread_mutex_init(&the_mutex, NULL);
    pthread_cond_init(&condc,NULL);
    pthread_cond_init(&condp,NULL);

    //Creating the threads
    pthread_create(&con, NULL, consumer, NULL);
    pthread_create(&pro, NULL, producer, NULL);

    //Joining the threads
    pthread_join(con, NULL);
    pthread_join(pro, NULL);

    //Freeing up the memory
    pthread_mutex_destroy(&the_mutex);
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);

}