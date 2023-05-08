#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    char ch;
    ch=getc(stdin);
    while(ch!=EOF){
        if(ch != '\n'){
            if((ch>=97)&&(ch<=122)){
                ch = ch - 32;
            }
            printf("%c",ch);
        }
        ch=getc(stdin);
    }
    return 0;
}
