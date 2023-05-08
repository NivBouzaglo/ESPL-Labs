#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct link link;
typedef struct virus
{
    unsigned short SigSize;
    char* sig;
    char virusName[16];
}virus;

struct link {
    link *next;
    virus* vir;
};

void printHexa(FILE *output , char *signa ,int length);

/*this function receives a pointer to a virus struct and a file 
pointer and overwrites the given virus struct so that it represents the next virus in the file.*/
void readVirus(virus* vir, FILE* input){
    unsigned char s1[2];
    fread(s1,sizeof(char),2 ,input);
    short size = s1[0];
    size += (s1[1] << 8);
    vir->SigSize = size;
    char* sig = (char*)malloc((size)*sizeof(char));
    fread(sig ,sizeof(char),size , input);
    fread(vir->virusName,sizeof(char),16,input);
    vir->sig = sig;
    vir->SigSize = size;
}
/* this function receives a virus and a pointer to an output file. The function prints the virus to the given output. It prints the virus name (in ASCII), 
the virus signature length (in decimal), and the virus signature (in hexadecimal representation).*/
void printVirus(virus* vir ,FILE* output,int counter){
    fprintf(output ,"Virus Name: ");
    fprintf(output ,"%s\n" ,vir->virusName);
    fprintf(output ,"Virus size: %d\n",vir->SigSize);
    fprintf(output ,"signature: \n");
    printHexa(output , vir->sig , vir->SigSize);
}
void printHexa(FILE *output , char *signa ,int length){
    for(size_t i=0 ; i < length ; i++){
        unsigned char temp =signa[i];
        fprintf(output,"%02X", temp);
        fprintf(output," ");
        if (i !=0 && i % 19 == 0)
        {
            fprintf(output,"\n");
        }
        
    }
    fprintf(output,"\n\n");
}

 
 /* Print the data of every link in list to the given stream. Each item followed by a newline character. */
void list_print(link *next , FILE* output){
    int counter =0;
    while (next != NULL)
    {
        counter++;
        printVirus(next->vir , output , counter);
        next = next->next;
    } 
}
/* Add the given link to the list 
        (either at the end or the beginning, depending on what your TA tells you),
        and return a pointer to the list (i.e., the first link in the list).
        If the list is null - return the given entry. */
link* list_appnd(link* next , link* to_add){
    link* ans = to_add;
    ans->next = next;
    return ans;
}
/* Free the memory allocated by the list. */
void list_free(link* list){
    while (list != NULL)
    {
        link *temp = list;
        list = list->next;
        free(temp->vir->sig);
        free(temp->vir);
        free(temp);
    }
}
/*The detect_virus function compares the content of the buffer byte-by-byte with the virus signatures stored
in the virus_list linked list. size should be the minimum between the size of the buffer and the size of 
the suspected file in bytes. If a virus is detected, 
for each detected virus the detect_virus function prints the following details to the standard output :
**The starting byte location in the suspected file
**The virus name
**The size of the virus signature*/
void detect_virus(char *buffer, unsigned int size, link *virus_list){
    link *t = virus_list;
    while(t != NULL && t -> vir !=NULL && t->vir->virusName[0] != 0)
    {
        int idx =0;
        while (idx + t->vir->SigSize < size)
        {
            char *temp = t->vir->sig;
            int tempsize = t->vir->SigSize;
            int check = memcmp(&buffer[idx],temp,tempsize);
            if(check == 0){
                printf("the starting byte location : %x\n ",idx);
                printf("the virus name : %s\n",t->vir->virusName);
                printf("The size of the virus signature : %d\n", t->vir->SigSize);
            }
            idx++;
        }    
        t =t->next;
    }
}

int main(int argc , char** argv){
    link *listOfVirus =NULL;
    
    while (1)
    {
        puts("1) Load signatures");
        puts("2) Print signatures");
        puts("3) Detect viruses");
        puts("4) quit");
        int option = (int)fgetc(stdin) - 48;
        fgetc(stdin);
        int numOfvirus=0;
        FILE* input = fopen("signatures" , "r");
        if(option == 1){
            puts("Enter the file: ");
            char name[200];
            fgets(name ,200,stdin);
            name[strcspn(name,"\n")]=0;
            FILE* input =fopen(name ,"r");
           while (!feof(input))
           {
               virus* vir =(virus*)malloc(sizeof(virus));
               readVirus(vir ,input);
               if(vir->SigSize != 0)
                {
                    numOfvirus++;
                    link *add =(link *)malloc(sizeof(link));
                
                    add->vir =vir;
                    add->next=NULL;
                  
                    listOfVirus = list_appnd(listOfVirus ,add);
                  
                }
                else{
                    free(vir->sig);
                    free(vir);
                }
           }
           fclose(input);
        }
        else if(option == 2){
            list_print(listOfVirus ,stdout);
        }
        else if(option == 3){
            char buff[100000];
            fread(buff ,10000 , sizeof(char) ,input);
            fseek(input ,0,SEEK_END);
            int size = ftell(input);
            fseek(input,0,SEEK_SET);
            detect_virus(buff , size , listOfVirus);
        }
        else if(option == 4){
            list_free(listOfVirus);
            exit(0);
        }
        else
            puts("out of bounds");

    }
    return 0;
}