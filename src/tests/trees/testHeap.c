#include "../../trees/headers/heap.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    Heap *h = generateRandomHeap(20);
    drawHeap(h, "tstHeap");
    removeMinHeap(h, NULL);
    drawHeap(h, "removeMinTstHeap");
    removeHeap(h);
    return 0;
}