#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    fork();
  
    printf("Fork message!\n");
    return 0;
}

//The result? Two messages!