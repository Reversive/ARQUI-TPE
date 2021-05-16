// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "include/buddy.h"

//------------------------DECLARACION DE CONSTANTES----------------------------------------//

#define BASE 2
#define GIGA 30
#define MIN_ALLOC_LOG2 6 //Min size supported = 64 bytes
#define MAX_ALLOC_LOG2 (GIGA - MIN_ALLOC_LOG2) //Max size supported = 1 GB
#define BINARY_POWER(x) (1 << (x))
#define TOTAL_HEAP_SIZE (1024 * 500)


// ------------------------------DECLARACION DE FUNCIONES----------------------------------//

static size_t getBlock(size_t request);
static int getBlockToUse(size_t firstBlock);
static block_t *getBuddy(block_t *block);
static block_t *getPrincipalAdress(block_t *block);
static void addBlockAndMerge(block_t *block);
static void addNewBlock(block_t *block, block_t *lastNode, size_t level);
static bool isPower(int x, long int y); // https://www.geeksforgeeks.org/check-if-a-number-is-power-of-another-number/
static inline uint64_t log2(uint64_t n);
static void pushBlock(block_t *oldBlock, block_t *newNode);
static void deleteBlock(block_t *block);
static block_t *popBlock(block_t *block);
static int isBlockEmpty(block_t *block);
static int myPow(int base, int power);
static int biggestBuddy(size_t heap);

//---------------------------DECLARACION DE VARIABLES--------------------------------------//

static block_t *totalMemory;
static bool began = false;
static size_t heapSize;
static size_t cantBlocks;
static block_t buckets[MAX_ALLOC_LOG2];
static size_t freeBytesRemaining;

typedef struct block_t
{
    bool inUse;
    unsigned short int level;
    struct block_t *prev;
    struct block_t *next;
} block_t;

//-----------------------------------------------------------------------------------------//


int * memInfo()
{
    info[] = {(int)heapSize, (int) freeBytesRemaining}; 
    return info;
}


void initHeap()
{
    static void* totalMemoryAux;    
    heapSize = freeBytesRemaining = biggestBuddy(TOTAL_HEAP_SIZE);
    sbrk_handler(heapSize, &totalMemoryAux);

    totalMemory = (block_t *)totalMemoryAux;
    
    cantBlocks = log2(heapSize) - MIN_ALLOC_LOG2 + 1;

    if (cantBlocks > MAX_ALLOC_LOG2)
        cantBlocks = MAX_ALLOC_LOG2;

    block_t * aux= buckets;

    //inicializo los bloques del arreglo
    for (int i = 0; i < cantBlocks; i++,aux++)
    {
        buckets[i].level = i;
        buckets[i].inUse = true;
        buckets[i].prev = buckets[i].next = aux ;
    }
    //agrego el de mayor tamaño al heap
    addNewBlock(totalMemory, &buckets[cantBlocks - 1], cantBlocks - 1);
}

void *malloc(size_t requestedSize)
{
    if(began == false ){
        initHeap();
        began = true;
    }
    size_t totalBytes = requestedSize + sizeof(block_t);
    if (requestedSize == 0 || totalBytes > freeBytesRemaining)
    {
        return NULL;
    }

    size_t block = getBlock(totalBytes);

    int parentBlock = getBlockToUse(block);
    if (parentBlock == -1)
    {
        return NULL;
    }

    block_t *ptr;
    for (ptr = popBlock(&buckets[parentBlock]); block < parentBlock; parentBlock--)
    {
        ptr->level--;
        addNewBlock(getBuddy(ptr), &buckets[parentBlock - 1], parentBlock - 1);
    }
    ptr->inUse = true;
    ptr++;

    freeBytesRemaining -= BINARY_POWER(block + MIN_ALLOC_LOG2);

    return (void *)ptr;
}

void free(void *ptr)
{

    if (ptr == NULL)
        return;

    block_t *blockNode = (block_t *)ptr - 1;

    blockNode->inUse = false;

    freeBytesRemaining += BINARY_POWER(blockNode->level + MIN_ALLOC_LOG2);

    addBlockAndMerge(blockNode);

    return;
}

static bool isPower(int x, long int y)
{
    // The only power of 1 is 1 itself
    if (x == 1)
        return (y == 1);

    // Repeatedly comput power of x
    long int pow = 1;
    while (pow < y)
        pow *= x;

    // Check if power of x becomes y
    return (pow == y);
}

static uint64_t log2(uint64_t n)
{
    uint64_t val = 0;
    while(n > 1)
    {
        val++;
        n >>= 1;
    }
    return val;
}

static void pushBlock(block_t *oldBlock, block_t *newBlock)
{
    block_t prev = oldBlock->prev;
    newBlock->prev = prev;
    newBlock->next = oldBlock;
    prev->next = newBlock;
    oldBlock->prev = newBlock;
}

static void deleteBlock(block_t *block)
{
    block_t *prev = block->prev;
    block_t *next = block->next;
    prev->next = next;
    next->prev = prev;
}

static block_t *popBlock(block_t *block)
{
    block_t *aux = block->prev;
    if (aux == block)
        return NULL;
    deleteBlock(aux);

    return aux;
}

static int isBlockEmpty(block_t *block)
{
    return block->prev == block;
}

static void addNewBlock(block_t *block, block_t *lastNode, size_t level)
{
    block->inUse = false;
    block->level = level;
    pushBlock(lastNode, block);
}

static void addBlockAndMerge(block_t *block)
{
    block_t *buddy = getBuddy(block);

    while (block->level != cantBlocks - 1 && buddy->inUse == false && buddy->level == block->level)
    {
        deleteBlock(buddy);

        block = getPrincipalAdress(block);
        block->level++;

        buddy = getBuddy(block);
    }
    pushBlock(&buckets[block->level], block);
}

static block_t *getBuddy(block_t *block)
{

    uint64_t currentOffset = (uint64_t)block - (uint64_t)totalMemory;
    uint64_t newOffset = currentOffset ^ BINARY_POWER(MIN_ALLOC_LOG2 + block->level);

    return (block_t *)((uint64_t)totalMemory + newOffset);
}

static block_t *getPrincipalAdress(block_t *block)
{
    uint64_t mask = BINARY_POWER(block->level +MIN_ALLOC_LOG2);
    mask = ~mask;

    uint64_t currentOffset = (uint64_t)block - (uint64_t)totalMemory;
    uint64_t newOffset = currentOffset & mask;

    return (block_t *)((uint64_t)totalMemory + newOffset);
}

static size_t getBlock(size_t request)
{

    size_t aux = log2(request);

    if (aux < MIN_ALLOC_LOG2)
        return 0;

    aux -= MIN_ALLOC_LOG2;

    return isPower(BASE, request) == false ? aux + 1 : aux;
}

static int getBlockToUse(size_t firstBlock)
{

    int currentBlock = firstBlock;

    while (currentBlock < cantBlocks && isBlockEmpty(&buckets[currentBlock]))
        currentBlock++;

    if (currentBlock == cantBlocks)
        return -1;

    return currentBlock;
}

static int myPow(int base, int power) {
    int result = 1;
    int i;
    for(i=0; i<power; i++) {
        result *= base;
    }
    return result;
}

int biggestBuddy(size_t heap) {
    int i = 0;
    size_t totalHeap = 1;
    while(myPow(2,i) < heap){
        totalHeap *=2; 
        i++;
    }
    return totalHeap;
}