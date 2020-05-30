// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "txttopolish.h"

static int _handle(FILE* file){
  char c = (char)getc(file);
  double retval;
  err_t error = FINE;
  enum what{
	  MYEOF, 
	  COMMENT, 
	  INIT, 
	  PRECOMMENT, 
	  COMMAND, 
	  SPECIAL, 
	  MEMORY, 
	  RU,
  } cond = INIT;
  char* str = (char*)malloc(sizeof(char));
  char* temp;
  int strlen = 0;
  int curlen = 0;

  if (str == NULL){
    printf("ERROR: not enough memory");
  } else {
    str[0] = 0;
    while(cond != MYEOF){
      if (c == EOF){
        if (cond == COMMAND){
        retval = strtonum(str, &error); //нужно чтобы в файлах обрабатывать строки перед eof
          if (error == FINE){
            printf(" == %g", retval);
          } else if (error == SYNT){
            printf(" == ERROR: syntax");
          } else if (error == MEM){
            printf(" == ERROR: memory");
          } else if (error == TODO){
            printf(" == ERROR: function doesn't exist/isn't realized");
          } else if (error == FUNC_ER) {
            printf(" == ERROR: math domain error");
		  } else if (error == OVER){
		    printf(" == ERROR: overflow");
		  } else {
            printf(" == ERROR: idk");
          };
          while (curlen--){
            str[curlen] = 0;
          };
        };
        cond = MYEOF;
      } else {
        if (cond != INIT && cond != PRECOMMENT){
          if (c == '\n'){
            if (cond == COMMAND){    
              retval = strtonum(str, &error); //нужно чтобы в файлах обрабатывать строки перед eof
              if (error == FINE){
                printf(" == %g", retval);
              } else if (error == SYNT){
                printf(" == ERROR: syntax");
              } else if (error == MEM){
                printf(" == ERROR: memory");
              } else if (error == TODO){
                printf(" == ERROR: function doesn't exist/isn't realized");
              } else if (error == FUNC_ER){
                printf(" == ERROR: math domain error");
              } else if (error == OVER){
		        printf(" == ERROR: overflow");
		      } else {
                printf(" == ERROR: idk");
              };
            } else if (cond == MEMORY){
              printf(" == ERROR: memory");
            } else if (cond == RU){
              printf(" == ERROR: illegal symbol found");
            }
            while (curlen--){
              str[curlen] = 0;
            };
            curlen = 0;
            cond = INIT;
          }
        } else {
          if (c == '/'){;
            if (cond == INIT){
              cond = PRECOMMENT;
            } else if (cond == PRECOMMENT){
              cond = COMMENT;
            }
          } else if (c >= 0 && !isspace(c) && cond != RU){
            cond = COMMAND;
          }
        };
        if (c < 0 && cond != COMMENT){
          cond = RU;
        };
        if (c != '\n'){
          if (strlen == curlen){
            temp = str;
            str = realloc(str, (++strlen + 1)*sizeof(char));
            if (str == NULL){
              str = temp;
              cond = MEMORY;
            } else {
              str[strlen] = 0;
              str[curlen++] = c;
            };
          } else {
            str[curlen++] = c;
          };
        }
        if (c != EOF) {
          putchar((int)c);
          c = (char)getc(file);
        };
      };
    };
    free(str);
  };
  return 0;
};

int main(int argc, char* argv[]){
  FILE* file = stdin;

  if (argc > 1){
    if (argc != 2){
      printf("ERROR: too much parameters");
      return 1;
    }
    if (fopen_s(&file, argv[1], "r") != 0){
      printf("ERROR: unable to open file");
      return 1;
    }
  }
  
  _handle(file);
  if (argc > 1) {
    fclose(file);
  };
  return 0;
}