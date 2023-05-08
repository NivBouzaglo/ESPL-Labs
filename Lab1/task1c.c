#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    FILE * in= stdin;
    int debugmod=0;
    char ch;
    int sign=0;
    int change = 32 , index = 2;
    char *add;

    for(size_t i=1;i<argc;i++){
        if(strcmp(argv[i], "-D")==0)//in use of function strcmp
            debugmod=1;
        if(strncmp(argv[i],"+e",2)==0){
            sign=1;
            add =argv[i];
        }    
        else if(strncmp(argv[i],"-e",2)==0){
            sign= -1;
            add=argv[i];  
       }
    }
    ch=fgetc(in);
    while(ch!=EOF){
        if(ch != '\n'){
            if(debugmod) fprintf(stderr, "%X\t", ch);
            if (sign != 0){
                if(add[index] == NULL)
                    change=1;
                else{
                    change = add[index] - '0';
                    index++;
                }
                
            }
            if((ch>=97)&&(ch<=122) || sign != 0){
                if (sign == 0)
                {
                    ch = ch - change;

                }
                else
                    ch = ch + sign * change;
            }
            printf("%c",ch);
            if(debugmod) fprintf(stderr, "%X\n", ch);        }
        ch=fgetc(in);
    }
    fclose(in);
    return 0;
}
