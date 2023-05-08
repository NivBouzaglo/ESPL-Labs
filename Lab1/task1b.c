#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    FILE * in= stdin;
    int debugmod=0;
    char ch;
    for(size_t i=1;i<argc;i++){
        if(strcmp(argv[i], "-D")==0)//in use of function strcmp
            debugmod=1;
    }
    ch=fgetc(in);
    while(ch!=EOF){
        if(ch != '\n'){
            if(debugmod) fprintf(stderr, "%X\t", ch);
            if((ch>=97)&&(ch<=122)){
                ch = ch - 32;
            }
            printf("%c",ch);
            if(debugmod) fprintf(stderr, "%X\n", ch);        }
        ch=fgetc(in);
    }
    fclose(in);
    return 0;
}
