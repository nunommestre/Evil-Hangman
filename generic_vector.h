#include <stdio.h>
#include "generic.h"
#include "status.h"
typedef void* GENERIC_VECTOR;
//NOTE: I know this breaks the rules of opaque object design, but this was the only way I could figure out how to make my function that switches to the largest word group work.
struct generic_vector  //the known type
{
        int size;
        int capacity;
        ITEM* data;
        void (*item_destroy)(ITEM* phItem);
        STATUS (*item_assignment)(ITEM* pLeft, ITEM right);

};
typedef struct generic_vector Generic_vector;

GENERIC_VECTOR generic_vector_init_default(
	STATUS(*item_assignment)(ITEM* pLeft, ITEM right),
	void (*item_destroy)(ITEM* phItem)); 

STATUS generic_vector_assignment(ITEM* pLeft, ITEM* Right);
STATUS generic_vector_push_back(GENERIC_VECTOR hVector, ITEM value);

int generic_vector_get_size(GENERIC_VECTOR hVector);
int generic_vector_get_capacity(GENERIC_VECTOR hVector);

ITEM generic_vector_at(GENERIC_VECTOR hVector, int index);

STATUS generic_vector_pop_back(GENERIC_VECTOR hVector);
Boolean generic_vector_empty(GENERIC_VECTOR hVector);


void generic_vector_destroy(GENERIC_VECTOR* phVector);
