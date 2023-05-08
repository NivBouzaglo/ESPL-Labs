#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME_SIZE 128
#define STDIN 0

int debug = 0;

typedef struct {
  char debug_mode;
  char file_name[128];
  int unit_size;
  unsigned char mem_buf[10000];
  size_t mem_count;
  int displayMode;  //0->decimal  ,  1->hexadecimal 
} state;

typedef struct {
  char *name;
  void (*fun)(state*);
} fun_desc;




//char* unit_to_format_hex(int unit_size ) {
//    static char* formats_hex[] = {"%#hhx\n", "%#hx\n", "No such unit", "%#x\n"};
//    return formats_hex[unit_size-1];
//}
//char* unit_to_format_dec(int unit_size ) {
//    static char* formats_decimal[] = {"%#hhd\n", "%#hd\n", "No such unit", "%#d\n"};
//    return formats_decimal[unit_size-1];
//}

/* Prints the buffer to screen by converting it to text with printf */
void print_units(FILE* output, void* buffer, int count , int unit_size, int hex) {
    void* end = buffer + unit_size*count;
    while (buffer < end) {
        int var = *((int*)(buffer));
        if(hex) {
            static char* formats_hex[] = {"%#hhx\n", "%#hx\n", "No such unit", "%#x\n"};
            fprintf(output, formats_hex[unit_size-1], var);
        }
        else {
            static char* formats_decimal[] = {"%#hhd\n", "%#hd\n", "No such unit", "%#d\n"};
            fprintf(output, formats_decimal[unit_size-1], var);
        }
        buffer += unit_size;
    }
}



void toggle_debug_mode(state* s) {
  if(debug == 0) {
    printf("Debug flag now on\n");
    debug = 1;
  }
  else {
    printf("Debug flag now off\n");
    debug = 0;
  }
}

void set_file_name(state* s) {
  printf("Please enter File Name:\n");
  char newName[FILE_NAME_SIZE];
  if(fgets(newName, FILE_NAME_SIZE, stdin) != NULL) {
      memcpy(s->file_name, strtok(newName, "\n"), sizeof(newName));
      if (debug)
          printf("Debug: file name set to %s\n", s->file_name);
  }
  else
      printf("File name error:\n");
}

int isValid(int n){
  if (n==1 || n==2 || n==4)
     return 1;
  return 0;
}

void set_unit_size(state* s) {
  printf("Please enter new unit size: \n");
  char unitBuffer[10];
  int newUnitSize;
  if(fgets(unitBuffer, sizeof(unitBuffer), stdin) != NULL) 
    sscanf(unitBuffer, "%d", &newUnitSize);
  if (!isValid(newUnitSize)) {
    printf("Invalid number\n");
    return;
  }
  if(debug) {
    if(s->displayMode)
      printf("Debug: set size to %x\n", newUnitSize);
    else
      printf("Debug: set size to %d\n", newUnitSize);
  }
  s->unit_size = newUnitSize;
}

void load_into_memory(state* s) {
  if (strcmp(s->file_name,"") == 0) {
    printf("Error - no file name was set\n");
    return;
  }
  FILE* file = fopen(s-> file_name, "r");  //Open a text file for reading.
  if(file == NULL) {
    printf("Error - can't open file\n");
    return;
  }
  char input[10000];
  int location, length;
  printf("Please enter location (hexadecimal) and length (decimal):\n");
  fgets(input, sizeof(input), stdin);
  sscanf(input, "%x %i", &location, &length);
  if(debug){
    fprintf(stderr,"file name: %s\n",s-> file_name);
    if(s->displayMode) {
        fprintf(stderr, "location: %X\n", location);
        fprintf(stderr, "length: %X\n", length);
    }
    else {
        fprintf(stderr, "location: %d\n", location);
        fprintf(stderr, "length: %d\n", length);
    }
  }
  fseek(file, location, SEEK_SET);
  s->mem_count = length * s->unit_size;
  fread(s->mem_buf, 1, s->mem_count ,file);
  if(s->displayMode)
      printf("Loaded %X units into memory\n", length);
  else
      printf("Loaded %d units into memory\n", length);
  fclose(file);
}

void toggle_display_mode(state* s) {
  if(s->displayMode) {
    s->displayMode = 0;
    printf("Display flag off now, decimal representation.\n");
  }
  else{
    s->displayMode = 1;
    printf("Display flag on now, hexadecimal representation.\n");
  }
}

void memory_display(state* s) {  //This displays u units of size unit_size starting at address addr in memory
  int u;
  int addr;
  fprintf(stdout, "Enter num of units and address:\n");
  char input[10000];
  fgets(input, sizeof(input), stdin);    
  sscanf(input, "%i %x", &u, &addr);
  printf("%d",u)  ;
  void* ptr;
  if(addr == 0)
      ptr = &(s->mem_buf);
  else
      ptr = &addr;

  if(s->displayMode) {
      printf("Hexadecimal\n===========\n");
      print_units(stdout, ptr, u, s->unit_size, 1);
  }
  else {
      printf("Decimal\n===========\n");
      print_units(stdout, ptr, u, s->unit_size, 0);
  }
}

void save_into_file(state* s) {
    char buffer[10000];
    int source_address, target_location;
    int length;
    printf("Please enter source-address, target-location and length\n");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%x %x %d", &source_address, &target_location, &length);
    if(debug) {
        if(s->displayMode)
            printf("length = %X, units= %X from memory, starting at address %X to the file %s, starting from offset %X\n",
             length, s->unit_size, source_address, s->file_name, target_location);
        else
            printf("length = %d, units = %d from memory, starting at address %d to the file %s, starting from offset %d\n",
             length, s->unit_size, source_address, s->file_name, target_location);
    }
    void* ptr;
    if(!source_address)
        ptr = &(s->mem_buf);
    else
        ptr = &source_address;

    FILE* file = fopen(s->file_name, "r+");
    if(file != NULL) {
        fseek(file, target_location, SEEK_SET);
        if(ftell(file) == target_location)
            fwrite(ptr, 1, s->unit_size * length, file);
        else
            printf("ERROR: target location: %X is out of bound for file: %s", target_location, s->file_name);
        fclose(file);
    }
    else
        printf("ERROR - file %s not open", s->file_name);
}

void memory_modify(state* s) {
    printf("Please Enter location and val\n");
    char buffer[10000];
    fgets(buffer, sizeof(buffer), stdin);
    int location, val;
    sscanf(buffer, "%x %x", &location, &val);
    if(debug){
        fprintf(stderr, "location: %X\n", location);
        if(s->displayMode)
            fprintf(stderr, "Val: %X\n", val);
        else
            fprintf(stderr, "Val: %i\n", val);
    }
    if(location < sizeof(s->mem_buf))
        memcpy(&s->mem_buf[location], &val, s->unit_size);
}

void quit(state* s) {
    if (debug)
      printf("quitting..\n");
    exit(0);
}


void printData(state* s) {
    printf("file_name : %s\n", s->file_name);
    if(s->displayMode) {
        printf("unit_size : %X\n", s->unit_size);
        printf("mem_count : %X\n", s->mem_count);
    }
    else {
        printf("unit_size : %d\n", s->unit_size);
        printf("mem_count : %d\n", s->mem_count);
    }
}

int getUserInput() {
  char buffer[2048];
  int op;
  if(fgets(buffer,  sizeof (buffer), stdin) != NULL){
      sscanf(buffer ,"%d", &op);
      if (op<0 || op>=9) {  //not in valid range
        fprintf(stdout, "Not in the range - not valid option\n" );
        return -1;
      }
  }
  return op;
}


int main(int argc, char **argv) {
  state* s = calloc(1, sizeof(state));
  fun_desc menu[9] = { {"Toggle Debug Mode", &toggle_debug_mode}, {"Set File Name", &set_file_name}, {"Set Unit Size", &set_unit_size},
            {"Load Into Memory", &load_into_memory}, {"Toggle Display Mode", &toggle_display_mode} ,{"Memory Display", &memory_display},
            {"Save Into File", &save_into_file}, {"Memory Modify", &memory_modify}, {"Quit", &quit} };

  while(1) {
    if (debug) {
      printData(s);
    }
    fprintf(stdout, "Please choose a function:\n");
    for(int i = 0;  i < 9 ; i++)
      fprintf(stdout,"%d) %s\n",i,menu[i].name);
    fprintf(stdout, "Chosen option: ");
    int option = getUserInput();
    if (option != -1) {
      menu[option].fun(s); }
    printf("\n");
  }
}
