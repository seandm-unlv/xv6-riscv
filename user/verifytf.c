#include "kernel/types.h"
#include "user/user.h"

#define MAXBLOCKS 256
#define PGSIZE 4096

int
main(void)
{
    void *ptrs[MAXBLOCKS];
    int nalloc = 0;

    int initial = trackframes();

    
    printf("First Allocation:\n");

    while(nalloc < MAXBLOCKS) {
        ptrs[nalloc] = block_alloc(28);

        if(ptrs[nalloc] == 0) {
            printf("allocation failed\n");
            exit(1);
        }

        uint64 addr = (uint64)ptrs[nalloc];
        uint64 page = addr & ~(PGSIZE - 1);

        printf("Allocated 32-byte chunk at %p (page %p)\n",
               ptrs[nalloc], (void*)page);

        int current = trackframes();
        if(nalloc == 0)
        {
            printf("Process page table has %d frames.\n",current);
        }
            
        else
        {
            printf("Current page count: %d\n", current);
        }

        nalloc++;

        if(current > initial) {
            printf("Frames allocated: %d\n", nalloc);
            break;
        }
    }

    printf("=================================================\n");
    printf("Beginning block_free\n");
    printf("=================================================\n");

    for(int i = 0; i < nalloc; i++) {
        uint64 addr = (uint64)ptrs[i];
        uint64 page = addr & ~(PGSIZE - 1);

        printf("Freed 32-byte chunk at 0x%p (page 0x%p)\n",
               ptrs[i], (void*)page);

        block_free(ptrs[i]);
    }

    printf("All blocks freed.\n");

    exit(0);
}
