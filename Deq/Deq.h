#ifndef Deq_h
#define Deq_h

#include <stdbool.h>
#include "DualyLinkedList.h"

//////////////////////////////////////////////////
typedef enum DeqOption {
    DEQ_OPTION_NONE,
    DEQ_OPTION_WITH_ELEMENT
} DEC_OPTION_e;

typedef struct Deq {
    DLL_t *list;
} Deq_t;

//////////////////////////////////////////////////
Deq_t *createDeq(void);
bool destroyDeq(Deq_t *Deq, DEC_OPTION_e option);
bool clearDeq(Deq_t *Deq, DEC_OPTION_e option);
bool enqueueDeq(Deq_t *Deq, void *element);
bool enqueueHeadOnDeq(Deq_t *Deq, void *element);
bool enqueueTailOnDeq(Deq_t *Deq, void *element);
void *dequeueDeq(Deq_t *Deq);
void *dequeueHeadOnDeq(Deq_t *Deq);
void *dequeueTailOnDeq(Deq_t *Deq);
void *findElementOnDeq(Deq_t *Deq, int (*comp)(void*, void*), void *element);
void *findMinOnDeq(Deq_t *Deq, int (*comp)(void*, void*));
void *findMaxOnDeq(Deq_t *Deq, int (*comp)(void*, void*));
bool isEmptyDeq(Deq_t *Deq);

#endif
