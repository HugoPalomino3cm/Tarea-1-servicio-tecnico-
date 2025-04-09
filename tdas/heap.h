#ifndef HEAP_H
#define HEAP_H

typedef struct Heap Heap;

void* heap_top(Heap* pq);

void heap_push(Heap* pq, void* data, int priority);

void heap_pop(Heap* pq);

Heap* heap_create();

#endif