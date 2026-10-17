#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int power(int base, int exp)
{
    int result = 1;

    for(int i = 0; i < exp; i++){
        result *= base;
    }

    return result;
}

int digits(int n)
{
    int count = 0;

    while(n > 0){
        count++;
        n /= 10;
    }

    return count;
}

int is_armstrong(int n)
{
    int sum = 0;
    int temp = n;
    int num_digits = digits(n);

    while(temp > 0){
        int digit = temp % 10;
        sum += power(digit, num_digits);
        temp /= 10;
    }

    return sum == n;
}

void count_armstrong(int limit)
{
    int count = 0;

    for(int i = 2; i <= limit; i++){
        if(is_armstrong(i))
            count++;
    }

    printf("PID %d found %d Armstrong numbers\n",
           getpid(),
           count);
}

int
main(int argc, char *argv[])
{
    int limit = 1000000;

    if(argc > 1)
        limit = atoi(argv[1]);

    debug(1);

    int priorities[8] = {
        0, 0,
        5, 5,
        10, 10,
        15, 15
    };

    for(int i = 0; i < 8; i++){
        int pid = priority_fork(priorities[i]);

        if(pid < 0){
            printf("priority_fork failed\n");
            exit(1);
        }

        if(pid == 0){
            count_armstrong(limit);
            exit(0);
        }
    }

    for(int i = 0; i < 8; i++){
        wait(0);
    }

    debug(0);

    exit(0);
}
