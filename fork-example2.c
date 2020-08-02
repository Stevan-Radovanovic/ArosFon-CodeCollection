#include <stdio.h>
#include <sys/types.h>

int main()
{
    fork(); //Fork - P1
    fork(); //Fork - P2
    fork(); //Fork - P3

    printf("Fork message\n");

    return 0;
}

//The result? Eight messages!

/* 
             P0
         /   |   \
       P1    P3   P2
      /  \          \
    P2    P3         P3
   /
 P3
 */
