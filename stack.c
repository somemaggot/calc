// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stack_t* stackCreate(){
  //Creating stack
  stack_t* stack_p;
  stack_p = (stack_t*)malloc(sizeof(stack_t));
  //Checking whether the memory was allocated
  if (stack_p != NULL){
    stack_p->top = NULL;
  }
  return stack_p;
}

err_t stackPush(stack_t* stack_p, double symb){
  //Adds element to the top of the stack
  stackNode_t* temp_node_p;
  err_t error;

  temp_node_p = stack_p->top;
  stack_p->top = (stackNode_t*)malloc(sizeof(stackNode_t));
  //Checking whether the memory was allocated
  if (stack_p->top != NULL){
    //Assigning given value to the top
    stack_p->top->thing = symb;
    stack_p->top->next = temp_node_p;
    error = FINE;
  } else {
    //Returning previous value to the top
    error = MEM;
    stack_p->top = temp_node_p;
  }
  return error;
}

err_t stackPop(stack_t* stack_p, double* symb){
  //Takes the top element from a stack
  stackNode_t* temp_node_p;
  err_t error;

  //Checking if the stack is empty - no top element
  if (stack_p->top != NULL){
    temp_node_p = stack_p->top;
    stack_p->top = stack_p->top->next;
    if (symb != NULL){
      *symb = temp_node_p->thing;
    }
    free(temp_node_p);
    error = FINE;
  }else{
    error = S_EMPTY;
  }
  return error;
}

void stackDestroy(stack_t* stack_p){
  //Destroys a stack and frees memory
  err_t error = FINE;
  
  //Freeing memory from nodes by popping all of them
  while (error == FINE){
    error = stackPop(stack_p, NULL);
  }
  free(stack_p);
}

queue_t* queueCreate(){
  //Creating queue
  queue_t* queue_p;
  queue_p = (queue_t*)malloc(sizeof(queue_t));
  //Checking whether memory was allocated
  if (queue_p != NULL){
    queue_p->rear = NULL;
  };
  return queue_p;
}

err_t queuePush(queue_t* queue_p, symb_t symb){
  //Adds an element to the back of a queue
  queueNode_t* temp_node_p;
  err_t error;

  temp_node_p = (queueNode_t*)malloc(sizeof(queueNode_t));
  //Checking whether memory was allocated
  if(temp_node_p != NULL){
    //Making temporary node the rear node
    error = FINE;
    temp_node_p->next = queue_p->rear;
    queue_p->rear = temp_node_p;
    temp_node_p->thing = symb;
  }else{
    //Queue wasn't altered and memory wasn't given, just pass an error and nothing else to do here
    error = MEM;
  }
  return error;
}

err_t queuePop(queue_t* queue_p, symb_t* symb){
  //Takes the front element from the queue
  queueNode_t* temp_node_p = queue_p->rear;
  queueNode_t* prev_node_p = NULL;
  err_t error;

  if (temp_node_p != NULL){//if queue isn't empty
    //Need to get through the queue
    while (temp_node_p->next != NULL){
      prev_node_p = temp_node_p;
      temp_node_p = temp_node_p->next;
    };
    //Check whether a node before front existed 
    if(prev_node_p != NULL){
      //Null its next pointer, it's a front node now
      prev_node_p->next = NULL;
    }else{
      //If prev_node_p remains NULL then rear node is a front node, queue is empty now
      queue_p->rear = NULL;
    };
    if (symb != NULL){
      *symb = temp_node_p->thing;
    }
    free(temp_node_p);
    error = FINE;
  }else{
    error = S_EMPTY;
  };
  return error;
};

void queueDestroy(queue_t* queue_p){
  //Destroys queue and frees memory
  err_t error = FINE;

  while(error == FINE){
    error = queuePop(queue_p, NULL);
  };
  free(queue_p);
};

//Copied from doubles stack
stackO_t* stackOCreate(){
  //Creating stack
  stackO_t* stack_p;
  stack_p = (stackO_t*)malloc(sizeof(stackO_t));
  //Checking whether the memory was allocated
  if (stack_p != NULL){
    stack_p->top = NULL;
  }
  return stack_p;
}

err_t stackOPush(stackO_t* stack_p, oper symb){
  //Adds element to the top of the stack
  stackONode_t* temp_node_p;
  err_t error;

  temp_node_p = stack_p->top;
  stack_p->top = (stackONode_t*)malloc(sizeof(stackONode_t));
  //Checking whether the memory was allocated
  if (stack_p->top != NULL){
    //Assigning given value to the top
    stack_p->top->thing = symb;
    stack_p->top->next = temp_node_p;
    error = FINE;
  } else {
    //Returning previous value to the top
    error = MEM;
    stack_p->top = temp_node_p;
  }
  return error;
}

err_t stackOPop(stackO_t* stack_p, oper* symb){
  //Takes the top element from a stack
  stackONode_t* temp_node_p;
  err_t error = FINE;

  //Checking if the stack is empty - no top element
  if (stack_p->top != NULL){
    temp_node_p = stack_p->top;
    stack_p->top = stack_p->top->next;
    if (symb != NULL){
      *symb = temp_node_p->thing;
    }
    free(temp_node_p);
  }else{
    error = S_EMPTY;
  }
  return error;
}

void stackODestroy(stackO_t* stack_p){
  //Destroys a stack and frees memory
  err_t error = FINE;
  
  //Freeing memory from nodes by popping all of them
  while (error == FINE){
    error = stackOPop(stack_p, NULL);
  }
  free(stack_p);
}

err_t stackOPeek(stackO_t* stackO_p, oper* symb_p){
  err_t error = FINE;
  if (stackO_p->top != NULL){
    *symb_p = stackO_p->top->thing;
  } else {
    error = S_EMPTY;
  }
  return error;
}