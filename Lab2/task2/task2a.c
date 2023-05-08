#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 

char censor(char c) {
  if(c == '!')
    return '*';
  else
    return c;
}

char* map(char *array, int array_length, char (*f) (char)){
  char* map= (char*)(malloc(array_length*sizeof(char)));
  /* TODO: Complete during task 2.a */
  for( int i = 0;  i< array_length; i++){
      map[i] = f(array[i]);
  }
  return map;
}

int main(int argc,char **argv){
    return 1;
}