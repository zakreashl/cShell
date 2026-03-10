# cShell 🐚
A minimal Unix shell written in C. Supports file and directory management, 
navigation, and file reading — all in a lightweight TUI.

## Building & Running
**Requirements:** GCC (or any C compiler), Unix-based OS (Linux/macOS)
```bash
gcc cshell.c -o cshell
./cshell
```

## Commands
![cShell commands](https://github.com/user-attachments/assets/2892d8ab-7b07-4537-9d57-716f0f7f12a5)

## How It Works
Each command runs in a forked child process (except `cd`, `pwd`, `echo`, 
`clear`, and `help`, which run in the parent to correctly affect shell state).
