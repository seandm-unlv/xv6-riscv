#include "kernel/types.h"
#include "user/user.h"

#define MAX_ALLOCS 1024

int
main(void)
{
    void *ptrs[MAX_ALLOCS];
    int nalloc = 0;

    int initial = trackframes();
    printf("Initial frames: %d\n", initial);

    while(nalloc < MAX_ALLOCS){
        ptrs[nalloc] = block_alloc(28);

        if(ptrs[nalloc] == 0){
            printf("allocation failed\n");
            exit(1);
        }

        nalloc++;

        int current = trackframes();
        printf("Frames after allocation %d: %d\n",
               nalloc, current);

        if(current > initial){
            printf("Frame count increased.\n");

            for(int i = 0; i < nalloc; i++)
                block_free(ptrs[i]);

            exit(0);
        }
    }

    printf("Exceeded allocation limit.\n");

    for(int i = 0; i < nalloc; i++)
        block_free(ptrs[i]);

    exit(1);
}
