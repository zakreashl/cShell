#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>

char wd[100] = ".";


void cd(char* args) {
    chdir(args); // change the dir with the unistd lib
    getcwd(wd, sizeof(wd)); // change the working dir
}

void ls() {
    // DIR is struct that represents a directory (folder). you can acsess files and stuff with it
    DIR* dir = opendir(wd); // make a dir

    struct dirent *entry; // ptr to sub directory or file
    while((entry = readdir(dir)) != NULL) { // while it is not null
        printf("%s\n", entry->d_name); // read the dir and print the file name
    }

    closedir(dir); // close it
}

void pwd() {
    printf("\n%s\n", wd);
}

void echo(char* args) {
    printf("\n%s\n", args);
}

void cat(char* args) {
    // FILE is the same thing as a DIR but a file
    FILE* file = fopen(args, "r"); // get the file
    int c; // current character being printed

    while((c = fgetc(file)) != EOF) { // get next char as long as it is EOF (End of File)
        putchar(c);
    }

    fclose(file); // close it
}

void touch(char* args) {
    FILE* file = fopen(args, "a"); // "a" is the mode_t which says Controls read/write/append access and whether the file is created or truncated.
    fclose(file); // close it 
}

void clear() {
    printf("\033[H\033[J"); // this clears it ig
}

void help() {
    printf("=======================================================================\n");
    printf("| This is a shell that I made and I am calling it cShell.             |\n");
    printf("| Here are all of the commands.                                       |\n");
    printf("|                                                                     |\n");
    printf("|                                                                     |\n");
    printf("| cd    <file name> - changes the wd (working directory)              |\n");
    printf("| ls                - shows all files and folder in wd                |\n");
    printf("| pwd               - shows wd                                        |\n");
    printf("| echo  <message>   - prints back whatever message you gave it        |\n");
    printf("| clear             - clears up your terminal                         |\n");
    printf("| mkdir <dir name>  - makes a new directory in your wd                |\n");
    printf("| rmdir <dir name>  - removes listed directory as long as it is empty |\n");
    printf("| rm    <file name> - removes listed file                             |\n");
    printf("| cat   <file name> - prints content of listed file                   |\n");
    printf("| touch <file name> - makes a new file with the listed name           |\n");
    printf("| exit              - sends you back to your other terminal           |\n");
    printf("|                                                                     |\n");
    printf("=======================================================================\n");
}

int main() {
    char input[100]; // the full string the user inputed

    char command[20]; // the command cd, ls, touch
    char args[80]; // the arguments <file name>

    const char* delims = " "; // delimiters are the characters telling us how we will split the input

    char* token; // the current token we are looking at
    
    getcwd(wd, sizeof(wd)); // change the working dir

    help(); // show all of the possible commands
    
    while (1) {
        printf("%s > ", wd); // print the working dir 

        fgets(input, sizeof(input), stdin); // get input
        input[strcspn(input, "\n")] = '\0'; // remove the "\n" at the end

        if (strcmp(input, "exit") == 0) break; // if the input is exit we break from the loop

        // Get command and args
        token = strtok(input, delims); // get the command
        if(token != NULL) strcpy(command, token); // cpy the command to the command buffer
        //printf("Command: %s\n", command);

        token = strtok(NULL, ""); // get the next token
        if(token != NULL) strcpy(args, token); // cpy it to the arges buffer
        //printf("Args: %s\n", args);

        pid_t id = fork(); // create a child and parent program
        
        
        if(id == -1) {
            // error
            fprintf(stderr, "Error during forking");
        } else if (id == 0) {
            // child
         
            if(strcmp(command, "ls") == 0) {
                ls();
            } else if(strcmp(command, "mkdir") == 0) {
                mkdir(args, 0755); // 0755 is the mode_t which says owner can read/write/execute, group/others can read/execute
            } else if(strcmp(command, "rmdir") == 0) {
                rmdir(args);
            } else if(strcmp(command, "rm") == 0) {
                remove(args);
            } else if(strcmp(command, "cat") == 0) {
                cat(args);
            } else if(strcmp(command, "touch") == 0) {
                touch(args);
            }

            _exit(0);
            
        } else {
            // parent

            if(strcmp(command, "cd") == 0) {
                cd(args);
            } else if(strcmp(command, "pwd") == 0) {
                pwd();
            } else if(strcmp(command, "echo") == 0) {
                echo(args);
            } else if (strcmp(command, "clear") == 0) {
                clear();
            } else if (strcmp(command, "help") == 0) {
                help();
            }

            waitpid(id, NULL, 0); // for the child to wait
        }

        memset(command, 0, sizeof(command)); // reset command and args buffer
        memset(args, 0, sizeof(args));

        printf("\n");
    }

    return 0;
}
