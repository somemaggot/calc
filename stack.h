#pragma once
#ifndef MYBEAUTIFULLISTTYPES
#define MYBEAUTIFULLISTTYPES

typedef enum operand{//List of binary operands goes in order of precedence
  BRAC,
  CBRAC,
  PLUS,
  MIN,
  UMIN,
  PROD,
  DIV,
  SIN,
  SQRT,
  COS,
  TAN,
  CTAN,
  ASIN,
  ACOS,
  ATAN,
  ACTAN,
  EXP,
  LN,
  FLOOR,
  CEIL,
  POW,
}oper;

typedef union Symb_u{
  oper operd;
  double num;
}symb_u;

typedef struct symb_t{
  symb_u thing;
  enum symbType{
    NUM,
    OPER,
  }type;
}symb_t;

typedef enum err{
  FINE,
  MEM,
  S_EMPTY,
  SYNT,
  TODO,
  FUNC_ER,
  RU,
  OVER,
}err_t;

typedef struct sNode{
  struct sNode* next;
  double thing;
}stackNode_t;

typedef struct{
  stackNode_t* top;
}stack_t;

err_t stackPush(stack_t* stack_p, double symb);
err_t stackPop(stack_t* stack_p, double* symb_p);
stack_t* stackCreate();
void stackDestroy(stack_t* stack_p);

// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
typedef struct qNode{
  struct qNode* next;
  symb_t thing;
}queueNode_t;

typedef struct queue{
  queueNode_t* rear;
}queue_t;

err_t queuePush(queue_t* queue_p, symb_t symb);
err_t queuePop(queue_t* queue_p, symb_t* symb);
queue_t* queueCreate();
void queueDestroy(queue_t* queue_p);

typedef struct soNode{
  struct soNode* next;
  oper thing;
}stackONode_t;

typedef struct{
  stackONode_t* top;
}stackO_t;

err_t stackOPush(stackO_t* stackO_p, oper symb);
err_t stackOPop(stackO_t* stackO_p, oper* symb_p);
stackO_t* stackOCreate();
err_t stackOPeek(stackO_t* stackO_p, oper* symb_p);
void stackODestroy(stackO_t* stackO_p);

#endif