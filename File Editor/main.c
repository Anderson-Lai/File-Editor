#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define nullptr NULL

#include "commands.h"

int main(int argc, char** argv)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    FILE* file = nullptr;

    if (argc != 2) {
        printf("No file argument provided\n");
        exit(EXIT_FAILURE);
    }

    // try to open the file
    errno_t err = fopen_s(&file, argv[1], "r+");

    // check if the file opened
    if (err) {
        perror("Error opening file");
        printf("Creating the file\n");

        // create the file if does not exist
        err = fopen_s(&file, argv[1], "w");
        if (err) {
            perror("Error creating file\n");
            exit(EXIT_FAILURE);
        }
        fclose(file);

        // open the created file
        err = fopen_s(&file, argv[1], "r+");
        if (err) {
            perror("Error opening the new file\n");
            exit(EXIT_FAILURE);
        }

    }

    printf("\nText editor CLI\n");
    while (true) {
        // get the command 
        char buffer[1024];
        printf("$ ");

        // fgets ensures null-termination and memory safety
        fgets(buffer, sizeof(buffer), stdin);

        // clear any extra characters in case of buffer overflow
        if (buffer[strlen(buffer) - 1] != '\n') {
            int c;
            while ((c = getchar()) != '\n');
        }

        // break if 'exit'
        // notice the '\n' because of fgets
        if (!strcmp(buffer, "exit\n")) {
            fclose(file);
            break;
        }

        handleCommand(buffer, file);
    }

    return 0;
}