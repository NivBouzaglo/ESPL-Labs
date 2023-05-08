#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int addr6;
int addr7;
int addr5;

char *string_blablabla = "blablabla";
int integer = 10;

int foo();
void point_at(void *p);
void foo1();
void foo2();



int main (int argc, char** argv){
    int addr2;
    int addr3;
    char* yos="ree";
    int * addr4 = (int*)(malloc(50));

    int x = 3;

    char xx[x];

    void *voidPtr;

    float farray[3];
    double darray[3];
    int* iptrarray[3];
    char* cptrarray[3];

    int iarray[] = {1,2,3};
    char carray[] = {'a','b','c'};
    int* iarrayPtr = iarray;
    char* carrayPtr = carray;

    printf("voidPtr = %p\n", voidPtr);

    printf("iarray[] = {%d,%d,%d}\n", *iarrayPtr, *(iarrayPtr + 1), *(iarrayPtr + 2));
    printf("carray[] = {%c,%c,%c}\n", *carrayPtr, *(carrayPtr + 1), *(carrayPtr + 2));

    printf("%p, %p, %p, %p, %p, %p, %p, %p, %p, %p, %p, %p\n", 
        iarray, iarray+1, farray, farray+1, darray, darray+1, carray, carray+1, iptrarray, iptrarray+1, cptrarray, cptrarray+1);

    printf("- &addr2: %p\n",&addr2);
    printf("- &addr3: %p\n",&addr3);
    printf("- foo: %p\n",foo);

    printf("- &addr7: %p\n",&addr7);
    printf("- &addr6: %p\n",&addr6);
    printf("- &addr5: %p\n",&addr5);
    
	point_at(&addr5);
	
    printf("- &addr6: %p\n",&addr6);
    printf("- yos: %p\n",yos);
    printf("- addr4: %p\n",addr4);
    printf("- &addr4: %p\n",&addr4);
    
    printf("- &foo1: %p\n" ,&foo1);
    printf("- &foo1: %p\n" ,&foo2);
    printf("- &foo2 - &foo1: %ld\n" ,&foo2 - &foo1);
    return 0;
}


int foo(){
    return -1;
}

void point_at(void *p){
    int local;
	static int addr0 = 2;
    static int addr1;

    printf("main: %p\n", main);
    printf("string_blablabla: %p\n", string_blablabla);
    printf("foo: %p\n", foo);

    printf("address of string_blablabla: %p\n", &string_blablabla);
    printf("address of integer: %p\n", &integer);

    printf("local: %p\n", &local);
    printf("p: %p\n", p);

    long dist1 = (size_t)&addr6 - (size_t)p;
    long dist2 = (size_t)&local - (size_t)p;
    long dist3 = (size_t)&foo - (size_t)p;

    // printf("p: %p\n", &p);

    printf("dist1: (size_t)&addr6 - (size_t)p: %ld\n",dist1);
    printf("dist2: (size_t)&local - (size_t)p: %lu\n",dist2);
    printf("dist3: (size_t)&foo - (size_t)p:  %ld\n",dist3);
	
	printf("- addr0: %p\n", & addr0);
    printf("- addr1: %p\n",&addr1);
}

void foo1 (){    
    printf("foo1\n"); 
}

void foo2 (){    
    printf("foo2\n");    
}