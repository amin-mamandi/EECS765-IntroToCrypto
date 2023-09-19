## Introduction
This report documents the process of exploiting a buffer overflow vulnerability in the "nweb" web server as part of Programming Assignment 1 for EECS 765 - Introduction to Cryptography and Computer Security. The objective of this assignment was to gain unauthorized access to a system by carefully manipulating the input to the web server, leading to control over the $eip register and ultimately executing a shell with elevated privileges.

### Running the Exploit
The exploit developed for this assignment is designed to work on both Redhat8 and Redhat9 operating systems. The following IP addresses were used as outlined in the PA1 description:
```
192.168.32.40 - victim machine 1, referred to as Redhat8
192.168.32.50 - victim machine 2, referred to as Redhat9
192.168.32.10 - attacking machine running Ubuntu20
```
To successfully execute the exploit, follow these steps:

Open one terminal tab and set up a listener on the attacking machine:

```
$ nc -l -p 8998 -nvv
```
In a separate terminal tab, execute the exploit script corresponding to the target machine:

```
$ ./Redhat8exploit.sh
or
$ ./Redhat9exploit.sh
```

Hint: Ensure the script is executable by running the following command if needed: 
```
sudo chmod +x someScript.sh
```

## Developing the Exploit

### Pattern Generation
To determine the exact offset required to manipulate the $eip register, we used the pattern_create.rb tool from the Metasploit framework to generate a custom-sized input pattern. This pattern helps us locate the offset in the core dump responsible for modifying the $eip register.

### Payload Generation
The payload for this exploit was generated using the Metasploit framework, specifying the desired payload format as '/linux/x86/shell_reverse_tcp.' The generated shell code occupies 205 bytes and is configured for compatibility with the Bash environment.

### NOP Sleds
To ensure safe execution, we used two sets of NOP sleds, consisting of 'No Operation' instructions, as boundaries for our shell code. The first set contains 805 bytes of NOP sleds, followed by the 205-byte shell code, and an additional 22 bytes of NOP sleds as padding. The memory address pointed to falls within the first set of NOP sleds (0xbffff72a), ensuring that the program's flow eventually lands on our shell code.

### Address Formatting
Due to the system's little-endian byte order, we formatted the address as '\x2a\xf7\xff\xbf' to ensure correct interpretation by the system.

### RedHat9 Specifics
In the case of Redhat9, stack randomization posed an additional challenge in locating the $esp address. To find the $esp address effectively, we identified the processes on which nweb depends and searched for the "JMP ESP (0xffe4)" instruction.

To redirect the $eip to the JMP ESP instruction, the following steps were followed:

Started with a sequence of NOP sleds at the beginning of the input.
Inserted the address retrieved from the searchJmpCode script into the $eip register.
Added the shell code after the $eip register.
Introduced more NOP sleds to ensure the shell code execution.
Address formatting in little-endian byte order was employed to achieve the desired results.

### Conclusion
This assignment provided valuable hands-on experience in exploiting buffer overflow vulnerabilities, understanding memory layout, and crafting precise payloads to gain unauthorized access to systems. The knowledge gained through this assignment is essential for understanding and defending against such security threats.
