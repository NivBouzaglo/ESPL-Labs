#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 




typedef struct fun_desc {
  char *name;
  char (*fun)(char);
}fun_desc;


char encrypt(char c); /* Gets a char c and returns its encrypted form by adding 2 to its value. 
          If c is not between 0x41 and 0x7a it is returned unchanged */

char decrypt(char c); /* Gets a char c and returns its decrypted form by reducing 2 to its value. 
            If c is not between 0x41 and 0x7a it is returned unchanged */

char dprt(char c); /* dprt prints the value of c in a decimal representation followed by a 
           new line, and returns c unchanged. */

char cprt(char c); /* If c is a number between 0x41 and 0x7a, cprt prints the character of ASCII value c followed 
                    by a new line. Otherwise, cprt prints the dot ('*') character. After printing, cprt returns 
                    the value of c unchanged. */
    
char my_get(char c); /* Ignores c, reads and returns a character from stdin using fgetc. */
       
char quit(char c); /* Gets a char c,  and if the char is 'q' , ends the program with exit code 0. Otherwise returns c. */





char censor(char c) {
  if(c == '!')
    return '*';
  else
    return c;
}

char* map(char *array, int array_length, char (*f) (char)){
  char* map = (char*)(malloc(array_length*sizeof(char)));
  /* TODO: Complete during task 2.a */
  char ch;
  int end = 0;
  for( int i = 0;  (i< array_length) ; i++){
        if(end == 0){
            ch = (*f)(array[i]);
            if (ch != '\n'){
                map[i] = ch;
            }
            else{
               end = 1;
               map[i] = '\0';
            }
        }
        else{
            map[i] = '\0';
        }
  }
  return map;
}

char encrypt(char c){
     if((c >= 'A') && (c<= 'z')){
            return c + 2;
        }
        else{
            return c;
        }
}

char decrypt(char c){
     if((c >= 'A') & (c<= 'z')){
            return c - 2;
        }
        else{
            return c;
        }
}

char dprt(char c){
        printf("%i\n", c);
        return c;
}

char cprt(char c){
    if((c >= 'A') & (c<= 'z')){
        printf("%c\n", c);
    }
    else{
            printf("*\n");
    }

    return c;
}

char my_get(char c){
    char ch = fgetc(stdin);
    return ch;
}

char quit(char c){
    if ( c == 'q'){
        exit(0);
    }
  
    return c;
}

int main(int argc, char **argv){
    char* cur = calloc(5,sizeof(char));

    fun_desc menu[] = { { "Censor", censor }, { "Encrypt", encrypt },  { "Decrypt", decrypt },
                        { "Print dec", dprt },  { "Print string", cprt },  { "Get string", my_get },  
                        { "Quit", quit }, { NULL, NULL } }; 

    while(1){
        int option;
        char buf[10];
        char* f;
        printf("Please choose a function:\n");
        int i = 0;
        while(menu[i].name != NULL){
            printf("%d) ", i);
            printf("%s\n", menu[i].name);
            i++;
        }
        printf("Option: ");
        fgets(buf, 10, stdin);
        sscanf(buf, "%d", &option);
        if((option >= 0) && (option < i-1)){
            printf("Within bounds\n");
            f = map(cur, 5, menu[option].fun);
            printf("DONE.\n");
            free(cur);
            cur = f;
        }
        else if(option == i-1){
            printf("Within bounds\n");
            exit(0);
        }
        else{
            printf("\nNot Within bounds\n");
            exit(0);
        }
    }
      free(cur);
}
