#include <unistd.h>
//#define checkMemoryLeak

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "Deq.h"

//////////////////////////////////////////////////
typedef struct Element {
    int value;
} Element_t;

//////////////////////////////////////////////////
void test(void);
Element_t *createElement(int value);
bool destroyElement(Element_t *element);
int comp(void *elementA, void *elementB);

//////////////////////////////////////////////////
int main(int argc, const char * argv[]) {

#ifdef checkMemoryLeak
    while (true) {
        test();
        sleep(1);
    }
#else
    test();
#endif
    
    return EXIT_SUCCESS;
}

void test() {
    int testCount = 10;
    int numOfValues = 15;
    
    Deq_t *Deq = createDeq();
    
    for (int retry=0; retry<testCount; retry++) {
        printf("*** [Test #%d] ***\n", retry+1);
        
        Element_t *element = NULL;
        bool check = false;
        switch (retry) {
            case 0:
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(i);
                    check = enqueueDeq(Deq, element);
                    if (check) {
                        printf("enqueue : %10d\n", element->value);
                    }
                    else {
                        printf("error [%s] : could not enqueue value %d.\n", __func__, i);
                        destroyElement(element);
                    }
                }
                printf("\n");
                while (!isEmptyDeq(Deq)) {
                    element = dequeueDeq(Deq);
                    printf("dequeue : %10d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 1:
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(i);
                    check = enqueueHeadOnDeq(Deq, element);
                    if (check) {
                        printf("enqueue head : %10d\n", element->value);
                    }
                    else {
                        printf("error [%s] : could not enqueue value %d.\n", __func__, element->value);
                        destroyElement(element);
                    }
                }
                printf("\n");
                while (!isEmptyDeq(Deq)) {
                    element = dequeueHeadOnDeq(Deq);
                    printf("dequeue head : %10d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 2:
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(i);
                    check = enqueueHeadOnDeq(Deq, element);
                    if (check) {
                        printf("enqueue head : %10d\n", element->value);
                    }
                    else {
                        printf("error [%s] : could not enqueue value %d.\n", __func__, element->value);
                        destroyElement(element);
                    }
                }
                printf("\n");
                while (!isEmptyDeq(Deq)) {
                    element = dequeueTailOnDeq(Deq);
                    printf("dequeue tail : %10d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 3:
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(i);
                    check = enqueueTailOnDeq(Deq, element);
                    if (check) {
                        printf("enqueue tail : %10d\n", element->value);
                    }
                    else {
                        printf("error [%s] : could not enqueue value %d.\n", __func__, element->value);
                        destroyElement(element);
                    }
                }
                printf("\n");
                while (!isEmptyDeq(Deq)) {
                    element = dequeueHeadOnDeq(Deq);
                    printf("dequeue head : %10d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 4:
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(i);
                    check = enqueueTailOnDeq(Deq, element);
                    if (check) {
                        printf("enqueue tail : %10d\n", element->value);
                    }
                    else {
                        printf("error [%s] : could not enqueue value %d.\n", __func__, element->value);
                        destroyElement(element);
                    }
                }
                printf("\n");
                while (!isEmptyDeq(Deq)) {
                    element = dequeueTailOnDeq(Deq);
                    printf("dequeue tail : %10d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 5:
                srand((unsigned) time(NULL));
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(rand());
                    check = enqueueTailOnDeq(Deq, element);
                    if (check) {
                        printf("enqueue tail : %10d\n", element->value);
                    }
                    else {
                        printf("error [%s] : could not enqueue value %d.\n", __func__, element->value);
                        destroyElement(element);
                    }
                }
                printf("\n");

                Element_t *min = findMinOnDeq(Deq, comp);
                printf("min value : %d\n", min->value);
                Element_t *max = findMaxOnDeq(Deq, comp);
                printf("max value : %d\n", max->value);

                int s1 = max->value;
                Element_t *e1 = createElement(s1);
                element = findElementOnDeq(Deq, comp, e1);
                if (element != NULL) {
                    printf("found value %d.\n", element->value);
                }
                else {
                    printf("cound not found value %d. (T^T)\n", s1);
                }
                destroyElement(e1);
                
                int s2 = INT_MAX;
                Element_t *e2 = createElement(s2);
                element = findElementOnDeq(Deq, comp, e2);
                if (element != NULL) {
                    printf("found value %d.\n", element->value);
                }
                else {
                    printf("cound not found value %d. (T^T)\n", s2);
                }
                destroyElement(e2);
                printf("\n");

                // *************************************
                retry = INT_MAX - 1;        // stop loop.
                // *************************************
                break;
            default:
                break;
        }
    }
    
    destroyDeq(Deq, DEQ_OPTION_WITH_ELEMENT);
}

Element_t *createElement(int value) {
    Element_t *e = malloc(sizeof(Element_t));
    if (e == NULL) return NULL;
    e->value = value;
    return e;
}

bool destroyElement(Element_t *element) {
    // Block illegal parameters.
    if (element == NULL) return false;
    free(element);
    return true;
}

int comp(void *elementA, void *elementB) {
    int valueA = ((Element_t *)elementA)->value;
    int valueB = ((Element_t *)elementB)->value;
    return valueA - valueB;
}
