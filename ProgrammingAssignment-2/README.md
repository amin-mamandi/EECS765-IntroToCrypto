## Introduction
This assignment explores web server security, focusing on a Windows machine through the weblogic module in the Apache web server. Apache dominates the market share, making it a prime target for analysis [1]. Despite security measures like Address Space Layout Randomization (ASLR), buffer overflow vulnerabilities persist, allowing attackers to gain control of a Windows 7 environment hosting Apache.

## Running the Exploit
To execute the exploit, follow these steps on Ubuntu 20.04:
1. Set up a listener:
   ```bash
   $ nc -l -p 8998 -nvv
In another tab, execute the exploit script:
```bash
Copy code
$ perl ApacheExploitScript.pl | nc 192.168.32.20 80
```
The output of the terminal demonstrates the successful exploit.

Developing the Exploit
Using Metasploit's tools, a custom input pattern is generated to identify the offset responsible for manipulating the EIP register. After crashing Apache's child process, WinGDB reveals critical information about EIP and ESP registers.

WinGDB's output for EIP and ESP registers

Upon sending the pattern_create output to WebLogic, a deliberate crash occurs, and the EIP register's location is pinpointed at 4093. ESP is located at 4097 due to Windows stack randomization.

The 4-byte gap between EIP and ESP is crucial, given Windows' callee convention. Exploiting this gap involves placing the JMP ESP instruction to bypass ASLR. The "narly" tool aids in finding shared libraries with the JMP ESP instruction, overcoming ASLR challenges.

Narly's output and locating the JMP ESP instruction in one of the modules

Later, shellcode is generated using the Metasploit framework, specifying the payload format and using the alpha_mixed encoder.

X86 online assembler’s output for add esp, -200 instruction

Exploit Script Structure
Exploit script - Part 1

Initiate the malicious input with 4093 consecutive 'A's, overflow into the EIP register, and seamlessly bridge the 4-byte gap with a JMP ESP instruction. The redirection specifics are obtained from the Narly tool. Exploit script - Part 2 inserts the "add esp, -200" instruction, preventing unintentional operations on the stack, and concatenates all elements for payload delivery.

Conclusion
The interplay between ASLR, the "narly" tool, and the !nmod command is instrumental in overcoming Windows' security features.
