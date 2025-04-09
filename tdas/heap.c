#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
    if(pq->size==0) return NULL;
    return pq->heapArray[0].data;
}

void heap_push(Heap* pq, void* data, int priority){

    if(pq->size+1>pq->capac){
        //printf("se expande de %i a ", pq->capac);
        pq->capac=(pq->capac)*2+1;
        //printf("%i * %lu", pq->capac, sizeof(heapElem));
        pq->heapArray=realloc(pq->heapArray, (pq->capac)*sizeof(heapElem));
    }

    /*FlotaciÃ³n*/
    int now = pq->size;
    while(now>0 && pq->heapArray[(now-1)/2].priority < priority)
        {
                pq->heapArray[now] = pq->heapArray[(now-1)/2];
                now = (now -1)/2;
        }
    pq->heapArray[now].priority = priority;
    pq->heapArray[now].data = data;
    pq->size++;
}


void heap_pop(Heap* pq){

        pq->size--;
        pq->heapArray[0] = pq->heapArray[pq->size];
        int priority=pq->heapArray[0].priority;


        int now = 1;

        while((now<=pq->size && pq->heapArray[now].priority > priority) || (now+1<=pq->size && pq->heapArray[now+1].priority > priority)){
          heapElem tmp=pq->heapArray[(now-1)/2];
          if(now+1<=pq->size && pq->heapArray[now].priority < pq->heapArray[now+1].priority) now++;

          pq->heapArray[(now-1)/2]=pq->heapArray[now];
          pq->heapArray[now]=tmp;

          now = now * 2 + 1;
        }
        //printf("size = %i, top = %i\n", pq->size, pq->heapArray[0].data );
}

Heap* heap_create(){
   Heap *pq=(Heap*) malloc(sizeof(Heap));
   pq->heapArray=(heapElem*) malloc(3*sizeof(heapElem));
   pq->size=0;
   pq->capac=3; //capacidad inicial
   return pq;
}
