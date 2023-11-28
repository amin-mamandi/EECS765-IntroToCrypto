## Introduction
This assignment explores heap memory management in the context of the updated get_score program. The program dynamically allocates memory on the heap, presenting heap overflow vulnerabilities. The goal is to manipulate heap memory and develop an exploit.

## Running the Exploit
The exploit works on a RedHat8 machine using the specified command:
```bash
./getscore_heap $name $ssn
```
Proof of concept that the exploit works

## Background
Dynamic memory allocation occurs in the heap memory segment, managed by functions like malloc() and free(). Key components of the heap include heap_info, malloc_state, and malloc_chunk structures. malloc_chunk structures store information about allocated memory chunks, essential for memory management.

## Developing the Exploit
The assignment aims to overflow the heap buffer, overwrite metadata, and gain control over the program. Key steps include heap memory overwrite, creating a fake heap structure, and controlling memory overwrite.

## Controlling the "Where":
We aim to control where the program's execution jumps after the attack, pointing to our injected malicious code and shellcode.

## Controlling the "What":
This involves the address of the injected malicious code and ensuring the shellcode can navigate potential obstacles in memory.

The getscore_heap.c file reveals dynamically allocated buffers and input argument manipulation. The size of the name buffer is chosen as 127 bytes. The structure of the name argument is carefully crafted to accommodate forward and backward links, NOP sleds, a JMP instruction, and the shellcode.

## Structure of the Malicious Input:
[Diagram illustrating the structure of the malicious input]

The SSN input argument is also crafted with a fake heap structure. The overall input is constructed for potential exploitation.

## References and Collaborations
Watched the lecture’s video multiple times and consulted online sources to better understand heap memory management.

No other references.
