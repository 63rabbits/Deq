#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "Deq.h"

//////////////////////////////////////////////////
Deq_t *createDeq() {
    Deq_t *deq = malloc(sizeof(Deq_t));
    if (deq == NULL) return NULL;
    deq->list = createDLList();
    if (deq->list == NULL) {
        free(deq);
    }
    
    return deq;
}

bool destroyDeq(Deq_t *Deq, DEC_OPTION_e option) {
    // Block illegal parameters.
    if (Deq == NULL) return false;
    
    bool result = false;
    
    result = clearDeq(Deq, option);
    if (!result) {
        return false;
    }
    result = destroyDLList(Deq->list, DLL_OPTION_NONE);
    if (!result) {
        return false;
    }
    free(Deq);
    
    return true;
}

bool clearDeq(Deq_t *Deq, DEC_OPTION_e option) {
    // Block illegal parameters.
    if (Deq == NULL) return false;
    
    while (!isEmptyDeq(Deq)) {
        void *element = dequeueDeq(Deq);
        if ((option == DEQ_OPTION_WITH_ELEMENT) &&
            (element != NULL)) {
            free(element);
        }
    }
    
    return true;
}

bool enqueueDeq(Deq_t *Deq, void *element) {
    // Block illegal parameters.
    if (Deq == NULL) return false;
    
    return enqueueTailOnDeq(Deq, element);
}

bool enqueueHeadOnDeq(Deq_t *Deq, void *element) {
    // Block illegal parameters.
    if (Deq == NULL) return false;
    
    return insertAtHeadOnDLList(Deq->list, element);
}

bool enqueueTailOnDeq(Deq_t *Deq, void *element) {
    // Block illegal parameters.
    if (Deq == NULL) return false;
    
    return insertAtTailOnDLList(Deq->list, element);
}

void *dequeueDeq(Deq_t *Deq) {
    return dequeueHeadOnDeq(Deq);
}

void *dequeueHeadOnDeq(Deq_t *Deq) {
    if (isEmptyDeq(Deq)) return NULL;
    return pullHeadOnDLList(Deq->list);
}

void *dequeueTailOnDeq(Deq_t *Deq) {
    if (isEmptyDeq(Deq)) return NULL;
    return pullTailOnDLList(Deq->list);
}

void *findElementOnDeq(Deq_t *Deq, int (*comp)(void*, void*), void *element) {
    return findElementOnDLList(Deq->list, comp, element);
}

void *findMinOnDeq(Deq_t *Deq, int (*comp)(void*, void*)) {
    return findMinOnDLList(Deq->list, comp);
}

void *findMaxOnDeq(Deq_t *Deq, int (*comp)(void*, void*)) {
    return findMaxOnDLList(Deq->list, comp);
}

bool isEmptyDeq(Deq_t *Deq) {
    if (Deq == NULL) return true;
    return isEmptyDLList(Deq->list);
}

