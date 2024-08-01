#include "stack.h"

/**
  * @brief check stack is full
  * @param my_stack pointer to the stack
  * @retval status of the stack
  */
static stack_status stack_full (stack_ds_t *my_stack)    /** TO check if stack is full or not **/
{
    if(my_stack->stack_pointer == (STACK_MAX_SIZE-1))
    {
        return STACK_FULL;
    }
    else
    {
        return STACK_NOT_FULL;
    }
}

/**
  * @brief check stack is empty
  * @param my_stack pointer to the stack
  * @retval status of the stack
  */
static stack_status stack_empty(stack_ds_t *my_stack)    /** TO check if stack is empty or not **/
{
    if(my_stack->stack_pointer == (-1))
    {
        return STACK_EMPTY;
    }
    else
    {
        return STACK_NOT_FULL;
    }
}

/**
  * @brief initialize the stack pointer
  * @param my_stack pointer to the stack
  * @retval status of the initialization process
  */
return_status stack_init(stack_ds_t *my_stack)
{
    return_status ret = R_NOK;
    if(NULL == my_stack)
    {
        ret = R_NOK ;
    }
    else
    {
        my_stack->stack_pointer = -1 ;  /** to intialize stack_pointer equal to -1 **/
        ret = R_OK;
    }
    return ret;
}

return_status stack_push(stack_ds_t *my_stack , uint32 value)
{
    return_status ret = R_NOK ;
    if((my_stack == NULL) || (stack_full(my_stack) == STACK_FULL))     /** two problems will cause an error **/
    {
        #ifdef STACK_DEBUG
        printf("Error.. stack is full!! Can't push this value (%i) \n",value);
        #endif // STACK_DEBUG
        ret = R_NOK ;
    }
    else
    {
        my_stack->stack_pointer++;      /** to look at a first index to push an element **/
        my_stack->data[my_stack->stack_pointer] = value;
        #ifdef STACK_DEBUG
        printf("%i pushed to stack!! \n" , value);
        #endif // STACK_DEBUG
        ret = R_OK ;
    }
    return ret ;
}

return_status stack_pop (stack_ds_t *my_stack , uint32 *value)
{
    return_status ret = R_NOK ;
    if((my_stack == NULL) || (value == NULL) || (stack_empty(my_stack) == STACK_EMPTY))
    {
        #ifdef STACK_DEBUG
        printf("Error.. stack is empty!! Can't pop any value \n");
        #endif // STACK_DEBUG
    }
    else
    {
        *value = my_stack->data[my_stack->stack_pointer];
        my_stack->stack_pointer--;
        #ifdef STACK_DEBUG
        printf("value (%i) popped from stack.. \n",*value);  // if you write ( value without * )only will print the address
        #endif // STACK_DEBUG
        ret = R_OK ;
    }
    return ret ;
}

return_status stack_top (stack_ds_t *my_stack , uint32 *value)  // to return status and return the value of the top on array
{
    return_status ret = R_NOK ;
    if((my_stack == NULL) || (value == NULL) || (stack_empty(my_stack) == STACK_EMPTY))
    {
        #ifdef STACK_DEBUG
        printf("Error.. stack is empty!! Can't pop any value \n");
        #endif // STACK_DEBUG
    }
    else
    {
        *value = my_stack->data[my_stack->stack_pointer];
        #ifdef STACK_DEBUG
        printf("stack top value = %i \n",*value);
        #endif // STACK_DEBUG
        ret = R_OK ;
    }
    return ret ;
}

return_status stack_size(stack_ds_t *my_stack , uint32 *stack_size)
{
    return_status ret = R_NOK ;
    if((my_stack == NULL) || (stack_size == NULL))
    {
        #ifdef STACK_DEBUG
        printf("Error.. stack is empty!! Can't pop any value \n");
        #endif // STACK_DEBUG
    }
    else
    {
        *stack_size = (my_stack->stack_pointer+1);
        ret = R_OK ;
    }
    return ret ;
}

return_status stack_display(stack_ds_t *my_stack)
{
    return_status ret = R_NOK ;
    sint32 l_counter = ZERO_INIT ;
    if((my_stack == NULL) || (stack_empty(my_stack) == STACK_EMPTY))
    {
        #ifdef STACK_DEBUG
        printf("Error.. stack is empty!! Can't pop any value \n");
        #endif // STACK_DEBUG
    }
    else
    {
        printf("Stack data : ");
        for(l_counter = (my_stack->stack_pointer) ; l_counter >=0 ; l_counter --)
        {
            printf("%i\t",my_stack->data[l_counter]);
        }
        printf("\n");
        ret = R_OK ;
    }
}
