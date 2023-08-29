#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
//int fib[17]={0};

int factorial(int n) {
    int res=1;
    if (n<0) {
        printf("errro");
        return 1;
    } else {
       while(n>=1){
        res=res*n;
        n--;
       }
    }
    return res;
}

int fibonacci(int n) {
    int fib[17]={0};
    if(n<0){
        //error
        return -1;
    }
    if(n==0){
      fib[0]=0;
      return 0;
    }
    else if(n==1){
        fib[1]=1;
        return 1;
    }
    else{
        if(fib[n-1]==0){
            fib[n-1]=fibonacci(n-1);
        }
        if(fib[n-2]==0){
            fib[n-2]=fibonacci(n-2);
        }
        fib[n]=fib[n-1]+fib[n-2];
        return fib[n];
    }
        
}

int main() {
    int pid;

    pid = vfork();

    if (pid == 0) {
        // Child process
        printf("Factorial of 4 is: %d\n", factorial(4));
    } else {
        // Parent process
        printf("Fibonacci series up to 16:\n");
        for (int i = 0; i <= 16; i++) {
            printf("%d ", fibonacci(i));
        }
        printf("\n");
        // Wait for child to terminate
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}