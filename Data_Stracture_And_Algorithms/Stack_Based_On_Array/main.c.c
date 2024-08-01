#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stack_ds_t stack1 ;   /** create an object from stack_ds_t type **/
stack_ds_t stack2 ;
uint32 stack_pop_value = ZERO_INIT;

int main()
{
    uint32 stack1_top = ZERO_INIT;
    return_status ret = R_NOK;
    ret = stack_init(&stack1);
    if (R_NOK == ret)
    {
        printf("Stack failed to be intialized \n");
    }
    else
    {
        ret = stack_push(&stack1 , 11);
        ret = stack_push(&stack1 , 22);
        ret = stack_push(&stack1 , 33);
        ret = stack_push(&stack1 , 44);
        ret = stack_push(&stack1 , 55);
        printf("=====================================\n");
        ret = stack_display(&stack1);
        printf("=====================================\n");
        ret = stack_top(&stack1 , &stack1_top);
        if(R_OK == ret)
        {
            printf("Stack1 top = %i \n", stack1_top);
        }
        printf("=====================================\n");
        ret = stack_push(&stack1 , 66);  // Fail
        ret = stack_push(&stack1 , 77);  // Fail
        ret = stack_pop(&stack1, &stack_pop_value);
        printf("stack pop value = %i \n",stack_pop_value);
        ret = stack_pop(&stack1, &stack_pop_value);
        printf("stack pop value = %i \n",stack_pop_value);
        ret = stack_pop(&stack1, &stack_pop_value);
        printf("stack pop value = %i \n",stack_pop_value);
        ret = stack_pop(&stack1, &stack_pop_value);
        printf("stack pop value = %i \n",stack_pop_value);
        ret = stack_pop(&stack1, &stack_pop_value);
        printf("stack pop value = %i \n",stack_pop_value);
        ret = stack_pop(&stack1, &stack_pop_value);        // Fail
        if (ret == R_OK)
        {
            printf("stack pop value = %i \n",stack_pop_value);
        }
    }

    ret = stack_init(&stack2);
    if (R_NOK == ret)
    {
        printf("Stack failed to be intialized \n");
    }
    else
    {

    }

    return 0;
}
