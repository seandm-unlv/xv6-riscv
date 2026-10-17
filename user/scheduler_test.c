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

int count_armstrong(int limit)
{
    int count = 0;

    for(int i = 2; i <= limit; i++){
        if(is_armstrong(i))
            count++;
    }

    return count;
}

int
main(int argc, char *argv[])
{
    
    int debug_val;
    char debug_char[2];
    int priorities[8] = {0, 0, 5, 5, 10, 10, 15, 15};

    printf("Enter a Debug Value (Must be either 0 or 1):\n");
    read(0, debug_char, 2);
    debug_char[1] = '\0';

    debug_val = atoi(debug_char);
    debug(debug_val);

    for(int i = 0; i < 8; i++){
        int pid = priorityfork(priorities[i]);

        if(pid == 0){

            int start = uptime();

            int count = count_armstrong(1000000);

            int end = uptime();

            printf("\nProcess %d:\n", getpid());
            printf("Number of Armstrong Numbers between 2 and 1000000: %d\n",
                   count);
            printf("Time for process to complete:%dticks\n",
                   end - start);

            exit(0);
        }

        printf("\nForking a process with PID: %d and Priority: %d\n",
               pid,
               priorities[i]);
    }

    for(int i = 0; i < 8; i++){
        wait(0);
    }

    debug(0);

    exit(0);
}
