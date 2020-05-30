// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <stdio.h>
#include "stack.h"
#include "txttopolish.h"
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <float.h>

static err_t _is_valid_const(double* num, char* thing){
  //there's like 2 consts here, pi and e, so return true if it's one of these
  err_t error = SYNT;
  if (!strcmp(thing, "e")){
    *num = 2.718281828459045235360287471;
    error = FINE;
  } else if (!strcmp(thing, "pi")){
    *num = 3.14159265358979323846;
    error = FINE;
  };
  return error;
};

static int _is_unary(const oper *opr){
  //a bit of hindu code i guess, what it says in the title - returns 1 if opr is unary and 0 otherwise
  int retv = 0;

  if (*opr == UMIN){
    retv = 1;
  } else if (*opr == SQRT){
    retv = 1;
  } else if (*opr == SIN){
    retv = 1;
  } else if (*opr == COS){
    retv = 1;
  } else if (*opr == TAN){
    retv = 1;
  } else if (*opr == CTAN){
    retv = 1;
  } else if (*opr == ASIN){
    retv = 1;
  } else if (*opr == ACOS){
    retv = 1;
  } else if (*opr == ATAN){
    retv = 1;
  } else if (*opr == ACTAN){
    retv = 1;
  } else if (*opr == LN){
    retv = 1;
  } else if (*opr == FLOOR){
    retv = 1;
  } else if (*opr == CEIL){
    retv = 1;
  }
  return retv;
}

static int _is_rightas(const oper *opr){
  //is right assossiated
  return *opr == POW;
}

static err_t _is_valid_oper(char* thing){
  err_t error = SYNT;
  
  if (!strcmp(thing, "+")){
    error = FINE;
  } else if (!strcmp(thing, "-")){
    error = FINE;
  } else if (!strcmp(thing, "*")){
    error = FINE;
  } else if (!strcmp(thing, "/")){
    error = FINE;
  } else if (!strcmp(thing, "^")){
    error = FINE;
  } else if (!strcmp(thing, "sqrt")){
    error = FINE;
  } else if (!strcmp(thing, "sin")){
    error = FINE;
  } else if (!strcmp(thing, "cos")){
    error = FINE;
  } else if (!strcmp(thing, "tg")){
    error = FINE;
  } else if (!strcmp(thing, "ctg")){
    error = FINE;
  } else if (!strcmp(thing, "arcsin")){
    error = FINE;
  } else if (!strcmp(thing, "arccos")){
    error = FINE;
  } else if (!strcmp(thing, "arctg")){
    error = FINE;
  } else if (!strcmp(thing, "arcctg")){
    error = FINE;
  } else if (!strcmp(thing, "ln")){
    error = FINE;
  } else if (!strcmp(thing, "floor")){
    error = FINE;
  } else if (!strcmp(thing, "ceil")){
    error = FINE;
  };

  return error;
}

static err_t _handle_opers(char* thing, queue_t* queue_p, stackO_t* stack_p, oper* opr, int pstate){
  //to much code to just copypaste
  /*algorithm:
	check which oper is it
	if unary -> to the stack
	if binary after just have read an opening bracket -> error
	if binary -> 
	  while oper on top
	   has more or same priority (same priority is same oper),
	   or is unary,
	   or not isn't right-assossiated unless given isn't too (right-assossiated is just power now),
	   i also didn't figure better way to handle -2^2 better than in this condition:
	    push to queue from stack's top
	  push to stack given
    if closing bracket ->
	  push everything until opening brac
	  no opening brac - syntax error
  */
  err_t error = FINE;
  oper temp;
  symb_t symb;
  if (!strcmp(thing, "+")){
    *opr = PLUS;
  } else if (!strcmp(thing, "-")){
    if (pstate == 0){//umin only makes sense for like 5 * -2 and -2 * 3 and -(...), so unless previous read thing is a num - umin
      *opr = MIN;
    } else {
      *opr = UMIN;
    };
  } else if (!strcmp(thing, "*")){
    *opr = PROD;
  } else if (!strcmp(thing, "/")){
    *opr = DIV;
  } else if (!strcmp(thing, ")")){
    *opr = CBRAC;
  } else if (!strcmp(thing, "^")){
    *opr = POW;
  } else if (!strcmp(thing, "sqrt")){
    *opr = SQRT;
  } else if (!strcmp(thing, "sin")){
    *opr = SIN;
  } else if (!strcmp(thing, "cos")){
    *opr = COS;
  } else if (!strcmp(thing, "tg")){
    *opr = TAN;
  } else if (!strcmp(thing, "ctg")){
    *opr = CTAN;
  } else if (!strcmp(thing, "arcsin")){
    *opr = ASIN;
  } else if (!strcmp(thing, "arccos")){
    *opr = ACOS;
  } else if (!strcmp(thing, "arctg")){
    *opr = ATAN;
  } else if (!strcmp(thing, "arcctg")){
    *opr = ACTAN;
  } else if (!strcmp(thing, "ln")){
    *opr = LN;
  } else if (!strcmp(thing, "floor")){
    *opr = FLOOR;
  } else if (!strcmp(thing, "ceil")){
    *opr = CEIL;
  } else {
    *opr = TODO;
  };
  if (_is_unary(opr)){
    stackOPush(stack_p, *opr);
  } else {
	if (pstate == 2){
	  error = SYNT;
	} else {
	  stackOPeek(stack_p, &temp);
  	  while (((!_is_rightas(&temp) && temp == *opr) || (temp > *opr) || (_is_unary(&temp) && (!_is_rightas(opr) || temp != UMIN))) && stackOPop(stack_p, NULL) == FINE){
  	    symb.thing.operd = temp;
  	    symb.type = OPER;
  	    if (queuePush(queue_p, symb) == FINE){
  	      stackOPeek(stack_p, &temp);
  	    } else {
  		  error = MEM;
  	    }
  	  };
  	  if (*opr != CBRAC){
  	    if (stackOPush(stack_p, *opr) != FINE){
  	      error = MEM;
  	    }
  	  } else {
  	    stackOPeek(stack_p, &temp);
  	    if (temp == BRAC){
  		  stackOPop(stack_p, NULL);
  	    } else {
  		  error = SYNT;
  	    };
  	  }
    }
  };
  pstate = 1;
  return error;
}

static err_t _handle_nums(double* num, symb_t* symb, char* e, int* p, int * num_ap, queue_t* queue_p){
  //too much code to just copypaste it around
  err_t error = FINE;
  *num /= pow(10, *num_ap - *p);
  symb->type = NUM;
  symb->thing.num = *num;
  if (*num > DBL_MAX || *num < -DBL_MAX){
	error = OVER;
  }
  if (queuePush(queue_p, *symb) == FINE){
    *num = 0;
    *e = 0;
    *num_ap = 0;
    *p = 0;
  } else {
    error = MEM;
  };
  return error;
}

static err_t _transform(char* expr, queue_t* queue_p){
  //Turn input string into Polish notation queue
  /*algorithm: 
     if num -> to the queue
	 if oper or brac -> handle by _handle_oper, to the stack
	 else it'll be considered an oper and found invalid
	 in the end push all from opers stack to the queue
  */
  char thing[7] = ""; //declare with the biggest operand possible, everything bigger is just a number, initialize empty
  int j = 0; //use this one as thing's iterator
  double num = 0; //to store a number that i read
  int num_ap = 0; //number of digits in num after point
  char e = 0; //for scientific form
  int p = 0; //also that 
  enum state{
    IDLE,
    READ_NUM,
    READ_AP,
    READ_PREEXP,
	READ_SIGNEXP,
    READ_EXP,
    READ_OPER,
  }state = IDLE;
  enum prevstate{//to differentiate unary minus and catch errors with brackets & point, oper by default because "-6 + 3"
    PREAD_NUM,
    PREAD_OPER,
	PREAD_BRAC,
	PREAD_POINT
  }pstate = PREAD_OPER;
  int i;
  symb_t symb;
  err_t error = FINE;
  oper opr;
  stackO_t* stack_p;

  //Read string
  stack_p = stackOCreate();
  if (stack_p != NULL){
    for (i = 0; expr[i] && error == FINE; i++){
      //Check character
      if (isspace(expr[i]) || expr[i] == '(' || expr[i] == ')'){
        //Unless previous chars were spaces and state is idle, have to handle read number/operand
        if (state == READ_NUM || state == READ_EXP || (state == READ_AP && pstate != PREAD_POINT)){
          pstate = PREAD_NUM;
          error = _handle_nums(&num, &symb, &e, &p, &num_ap, queue_p);
        } else if (state == READ_OPER){
			if (_is_valid_oper(thing) == FINE){
			  error = _handle_opers(thing, queue_p, stack_p, &opr, pstate);
			  pstate = PREAD_OPER;
			} else {
			  error = SYNT;
			};
		    while(j > 0){
            thing[--j] = 0;
          };
		} else if (state == READ_AP && pstate == PREAD_POINT || state == READ_PREEXP || state == READ_SIGNEXP){
		  error = SYNT;
		};
        if (expr[i] == '(' && error == FINE){
          if (state == READ_NUM || state == READ_AP || state == READ_EXP){//actually this shouldn't happen, it's like 5(...)
            pstate = PREAD_BRAC;//well it'll be caught in _comp, just too much numbers
			error = _handle_nums(&num, &symb, &e, &p, &num_ap, queue_p);
          } else if (state == READ_OPER){//neither should this, all opers are handled just when confirmed valid so si(...)
			if (_is_valid_oper(thing) == FINE){
              error = _handle_opers(thing, queue_p, stack_p, &opr, pstate);
			} else {
			  error = SYNT;
			}
			while(j > 0){
              thing[--j] = 0;
            };
          }
          pstate = PREAD_BRAC;
          opr = BRAC;//well, opening brac doesn't really fit _handle_opers
          if (stackOPush(stack_p, opr) != FINE){
            error = MEM;
          };
        } else if (expr[i] == ')' && error == FINE){
          error = _handle_opers(")", queue_p, stack_p, &opr, pstate);
          pstate = PREAD_NUM;
		}
		state = IDLE;
      } else if (isdigit(expr[i])){
        if (state == IDLE){
          state = READ_NUM;
          num = expr[i] - '0';
        } else if (state == READ_OPER){
		  if (_is_valid_oper(thing) == FINE){
            error = _handle_opers(thing, queue_p, stack_p, &opr, pstate);
		  } else {
		    error = SYNT;
		  }
		  state = IDLE;
          while(j > 0){
            thing[--j] = 0;
          };
          state = READ_NUM;
          pstate = PREAD_OPER;
          num = expr[i] - '0';
        } else if (state == READ_NUM){
          num *= 10;
          num += expr[i] - '0';
        } else if (state == READ_AP) {
		  if (pstate == PREAD_POINT){
		    pstate = PREAD_NUM;
		  }
          num *= 10;
          num += expr[i] - '0';
          num_ap += 1;
        } else if (state == READ_EXP || state == READ_SIGNEXP){
          p *= 10;
          p += e * (expr[i] - '0');
		  if (state == READ_SIGNEXP){
			state = READ_EXP;
		  }
        } else if (state == READ_PREEXP){
		  if (e == 0){
		    e = 1;
		  };
          state = READ_EXP;
          p = (expr[i] - '0') * e;
        } else {
          error = TODO;
        };
      } else if (expr[i] == '.'){
        if (state == READ_NUM){
          state = READ_AP;
		  pstate = PREAD_POINT;
        } else {
          error = SYNT;
        };
      } else if ((expr[i] == 'e' || expr[i] == 'E') && (state == READ_NUM || state == READ_AP)){
        state = READ_PREEXP;
      } else if ((expr[i] == '+' || expr[i] == '-') && state == READ_PREEXP){
        if (expr[i] == '+'){
          e = 1;
        } else {
          e = -1;
        };
		state = READ_SIGNEXP;
	  } else if ((expr[i] == '+' || expr[i] == '-') && state == READ_SIGNEXP){
		error = SYNT;
	  } else {
        if (state == READ_NUM || state == READ_EXP || state == READ_AP){
          pstate = PREAD_NUM;
          error = _handle_nums(&num, &symb, &e, &p, &num_ap, queue_p);
		  state = IDLE;
        }
        if (j < 6){
          state = READ_OPER;
          thing[j++] = expr[i];
          if (_is_valid_oper(thing) == FINE){
            error = _handle_opers(thing, queue_p, stack_p, &opr, pstate);
            pstate = PREAD_OPER;
			state = IDLE;
            while(j > 0){
              thing[--j] = 0;
            };
            state = IDLE;
		  } else if(_is_valid_const(&num, thing) == FINE){
		    error = _handle_nums(&num, &symb, &e, &p, &num_ap, queue_p);
            pstate = PREAD_NUM;
			state = IDLE;
            while(j > 0){
              thing[--j] = 0;
			};
		  };
        } else {
          error = SYNT;
        };
      };
    };
    if ((state == READ_NUM || (state == READ_AP && pstate != PREAD_POINT) || state == READ_EXP) && error == FINE){
      error = _handle_nums(&num, &symb, &e, &p, &num_ap, queue_p);
	  state = IDLE;
	} else if (state == READ_AP && pstate == PREAD_POINT || state == READ_PREEXP){
	  error = SYNT;
	} else if (thing[0]){
		if (_is_valid_oper(thing) == FINE){
		  error = _handle_opers(thing, queue_p, stack_p, &opr, pstate);
		  state = IDLE;
		} else {
			error = SYNT;
		};
    };
    symb.type = OPER;
    while (stackOPop(stack_p, &opr) == FINE && error == FINE){
      symb.thing.operd = opr;
      if (queuePush(queue_p, symb) != FINE){
        error = MEM;
      }
    }
  stackODestroy(stack_p);
  } else {
    error = MEM;
  }
  return error;
};

double _comp(queue_t* queue_p, err_t* error){
  //takes a reverse polish notation queue made with _transform and computes it
  stack_t* stack_p;
  symb_t symb;
  double a = 0, b = 0;
  //algorithm: if node is a number then push it to a stack, else if it is an operand then pop one or two numbers 
  //depending on whether or not it is a unary or binary operand, compute and push the result.
  //if stack doesn't have enough numbers for operation or if after queue is emptied stack doesn't contain only one number,
  //then syntax error it is.
  *error = FINE;
  stack_p = stackCreate();
  if (stack_p != NULL){
    while (queuePop(queue_p, &symb) == FINE && *error == FINE){
      if (symb.type == NUM){
        *error = stackPush(stack_p, symb.thing.num);
      } else {
        if (_is_unary(&(symb.thing.operd))){
          *error = stackPop(stack_p, &a);
          if (*error == S_EMPTY){
            *error = SYNT;
		  } else {
			  switch (symb.thing.operd){
			  case UMIN:
				  *error = stackPush(stack_p, -a);
				  break;
			  case SQRT:
                if (a >= 0){ //d(sqrt) = [0, +inf)
				  *error = stackPush(stack_p, sqrt(a));
				} else {
				  *error = FUNC_ER;
				}
				break;
			  case SIN:
			    *error = stackPush(stack_p, sin(a));
				break;
			  case COS:
			    *error = stackPush(stack_p, cos(a));
				break;
			  case TAN: //supposedly i should check for pi/2 + n*pi, but it can't really take argument precise enough to break it
			    *error = stackPush(stack_p, tan(a));
				break;
			  case CTAN:
				  if (a != 0){//now zero may be an issue
					*error = stackPush(stack_p, 1/tan(a));
				  } else {
				    *error = FUNC_ER;
				  }
				break;
			  case ASIN:
				if (-1 <= a && a <= 1){//d(asin) = [-1, 1]
			      *error = stackPush(stack_p, asin(a));
				} else {
					*error = FUNC_ER;
				};
				break;
			  case ACOS:
				if (-1 <= a && a <= 1){
			      *error = stackPush(stack_p, acos(a));
				} else {
					*error = FUNC_ER;
				};
				break;
			  case ATAN:
			    *error = stackPush(stack_p, atan(a));
				break;
			  case ACTAN:
			    *error = stackPush(stack_p, 3.141592653589793238462643383/2 - atan(a));
				break;
			  case LN:
				if (a > 0){//d(ln) = (0, +inf)
				  *error = stackPush(stack_p, log(a));
				} else {
				  *error = FUNC_ER;
				}
				break;
			  case FLOOR:
			    *error = stackPush(stack_p, floor(a));
				break;
			  case CEIL:
			    *error = stackPush(stack_p, ceil(a));
				break;
			  default://there's nothing really that could be there, but whatever
			   *error = TODO;
			   break;
			  }
          }
        } else {//b got to the stack earlier then a, thus b was in the queue earlier then a. all opers are f(b, a)
          *error = stackPop(stack_p, &a);
          *error = stackPop(stack_p, &b);
          if (*error == S_EMPTY){
            *error = SYNT;
          } else {
            switch (symb.thing.operd){
              case PLUS:
                *error = stackPush(stack_p, a + b);
                break;
              case MIN:
                *error = stackPush(stack_p, b - a);
                break;
              case PROD:
                *error = stackPush(stack_p, a * b);
                break;
              case DIV:
                if (a != 0){
                  *error = stackPush(stack_p, b / a);
                } else {
                  *error = FUNC_ER;
                }
                break;
              case POW:
                if ((b != 0 || a != 0) && (b > 0 || fmod(a, 1) == 0)){//0^0 and a^r where a<0 & r isn't integer are undefined
                  *error = stackPush(stack_p, pow(b, a));
                } else {
                  *error = FUNC_ER;
                }
                break;
              default:
                *error = TODO;
                break;
            }
          }
        }
      }
    }
    if (*error == FINE){
	  *error = stackPop(stack_p, &a);
	  if (*error == FINE){
        *error = stackPop(stack_p, &b);
        if (*error == FINE){
          *error = SYNT;
        } else {
          *error = FINE;
        };
	  } else {
	    *error = SYNT;
	  };
    };
    stackDestroy(stack_p);
    if (a > DBL_MAX || a < -DBL_MAX){
      *error = OVER;
    }
  } else {
    *error = MEM;
  };
  return a;
}

double strtonum(char* expr, err_t* error){
  double retval = 0;
  queue_t* queue_p;
  queue_p = queueCreate();
  if (queue_p != NULL){
    *error = _transform(expr, queue_p);
    if (*error == FINE){
      retval = _comp(queue_p, error);
    };
  queueDestroy(queue_p);
  } else {
    *error = MEM;
  }
  return retval;
};
