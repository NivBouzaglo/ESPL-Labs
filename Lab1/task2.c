#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    FILE * in= stdin;
    FILE* out = stdout;
    int debugmod=0;
    char ch;
    int sign=0;
    int change = 32 , index = 2;
    char *add;

    for(size_t i=1;i<argc;i++){
        if(strncmp("-i",argv[i],2)==0)
            in = fopen(argv[i]+2 , "r+");
        if(strncmp("-o",argv[i],2) == 0)
            out=fopen(argv[i]+2,"w+");
        if(strcmp(argv[i], "-d")==0)//in use of function strcmp
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
            if(debugmod) fprintf(out, "%X\t", ch);
            if (sign != 0){
                if(add[index] == '\0')
                    change=1;
                else{
                    change = add[index] - '0';
                    index++;
                }
                
            }
            if( (ch>=97 && ch<=122) || sign != 0){
                if (sign == 0)
                {
                    ch = ch - change;

                }
                else
                    ch = ch + sign * change;
            }
            fprintf(out,"%c",ch);
            if(debugmod) fprintf(out, "%X\n", ch);        
            }
            else
                fprintf(out,"\n");
        ch=fgetc(in);
    }
    fclose(out);
    fclose(in);
    return 0;
}
