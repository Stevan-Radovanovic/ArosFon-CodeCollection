#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void func()
{
    if (fork() == 0)
        printf("Child!\n");
    else
        printf("Parent!\n");
}

int main()
{
    func();
    return 0;
}

//The order is not defined, because the processes are concurrent