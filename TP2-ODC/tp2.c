#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "MMU.h"
#include "TAD_Cache.h"
#include "machine.h"

int main() {
    MemoryBlock *RAM = NULL, *cache1 = NULL, *cache2 = NULL, *cache3 = NULL;

    srand(time(NULL));

    RAM = createRAM(RAM);
    cache1 = createCacheWithData(sizeCache1, cache1);
    cache2 = createCacheWithData(sizeCache2, cache2);
    cache3 = createCacheWithData(sizeCache3, cache3);

    randomInstructions(RAM, cache1, cache2, cache3);

    return 0;
}
