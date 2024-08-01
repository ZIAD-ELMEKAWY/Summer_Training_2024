#ifndef _STACK_H
#define _STACK_H

#include "platform.h"
#include <stdio.h>

#define STACK_MAX_SIZE 5         /** size of stack based on array **/
#define STACK_DEBUG

typedef enum stack_status{
    STACK_EMPTY,
    STACK_FULL,
    STACK_NOT_FULL
}stack_status;

typedef struct stack_ds
{
    uint32 stack_pointer;
    uint32 data[STACK_MAX_SIZE];
}stack_ds_t;

/**
  * @brief initialize the stack pointer
  * @param my_stack pointer to the stack
  * @retval status of the initialization process
  */
return_status stack_init(stack_ds_t *my_stack);  /** we pass an address of structure to minimize the size **/
return_status stack_push(stack_ds_t *my_stack , uint32 value);
return_status stack_pop (stack_ds_t *my_stack , uint32 *value);
return_status stack_top (stack_ds_t *my_stack , uint32 *value);
return_status stack_size(stack_ds_t *my_stack , uint32 *stack_size);
return_status stack_display(stack_ds_t *my_stack );




#endif // _STACK_H
