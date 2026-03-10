# cShell 🐚
A minimal Unix shell written in C. Supports file and directory management, 
navigation, and file reading — all in a lightweight TUI.

![cShell demo](https://github.com/user-attachments/assets/2892d8ab-7b07-4537-9d57-716f0f7f12a5)

## Building & Running
**Requirements:** GCC (or any C compiler), Unix-based OS (Linux/macOS)
```bash
gcc cshell.c -o cshell
./cshell
```

## Commands
=======================================================================
| cd    <file name> - changes the wd (working directory)              |
| ls                - shows all files and folder in wd                |
| pwd               - shows wd                                        |
| echo  <message>   - prints back whatever message you gave it        |
| clear             - clears up your terminal                         |
| mkdir <dir name>  - makes a new directory in your wd                |
| rmdir <dir name>  - removes listed directory as long as it is empty |
| rm    <file name> - removes listed file                             |
| cat   <file name> - prints content of listed file                   |
| touch <file name> - makes a new file with the listed name           |
| exit              - sends you back to your other terminal           |
=======================================================================

## How It Works
Each command runs in a forked child process (except `cd`, `pwd`, `echo`, 
`clear`, and `help`, which run in the parent to correctly affect shell state).
