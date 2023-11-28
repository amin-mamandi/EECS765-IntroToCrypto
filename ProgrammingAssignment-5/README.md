## Introduction
In this assignment, we employ the Return Oriented Programming (ROP) technique to exploit a buffer overflow vulnerability in the Java Network Launch Protocol (JNLP) extension on Internet Explorer 8 running on Windows 7. The goal is to gain access to the Windows 7 shell.

## Developing the Exploit
The exploit did not work properly, and the development process involved several steps:

### Generating Shellcode
Generated shellcode for JavaScript with LPORT set to 4444 and LHOST set to 127.0.0.1.

*Generating Shellcode for JavaScript*

### Finding EIP and EBP Offsets
Used pattern_offset and pattern_create tools to find the exact addresses of the EIP and EBP registers. Identified the offset at 392 bytes.

*EIP and EBP Offsets*

### Finding Gadgets
Used skyrack to search for necessary gadgets in the msvcr71.dll library. Identified gadgets like POP EAX; RET, CALL EAX; RET, and more.

*Call EAX; RET Gadget*

### Overflowing the Stack
Designed the exploit by overwriting the value of EBP with the address of the shell code in the heap. The "leave" gadget was found at address 0x7c3411a4.

*Exploit Structure*

### Building Payload
Crafted a payload to be sprayed on the heap using the heaplib.js library. Included gadgets, VirtualProtect function address (0x7c37a140), and reverse shellcode.

*Payload Structure*

### Invoking VirtualProtect
Invoked VirtualProtect to change memory permissions. Located kernel32 function address and used ROP chain to call VirtualProtect with necessary parameters.

*ROP Chain for VirtualProtect Function*

### Stack Flip
Implemented stack flip to redirect execution. Set ESP to point to a heap region and controlled another register pointing to the heap.

### References and Collaborations
No collaborations.

### My Notes From the Lectures
- ROP involves chaining existing code sequences (gadgets) to execute arbitrary code.
- Chaining functions involves manipulating the stack and using gadgets like pop/pop/ret.
- Useful gadgets are identified using tools like msfelfscan (Linux) or msfpescan (Windows).
- Stack frames are described, and stack flipping is used to redirect execution.
- Heap spraying involves placing shellcode to increase vulnerability.
- Invoking VirtualProtect changes memory protection to RWX.
- SkyRack and X are used to find gadget addresses.

*Note: The exploit did not work properly, and the provided details outline the development process.*

