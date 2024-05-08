#include <stdio.h>
#include <string.h>

#include "actions.h"

void handleCommand(char* fullCommand, FILE* file) {

	// splitting the command
	char* nextToken = nullptr;
	char* pos = strtok_s(fullCommand, " ", &nextToken);

	// check if a command has been entered
	if (!pos) {
		perror("Enter a valid command");
		return;
	}

	// control flow
	if (!strcmp(pos, "new")) {
		// text
		pos = strtok_s(nullptr, "", &nextToken);

		new(pos, file);
	}
	// add '\n' as pos will read the entire string
	else if (!strcmp(pos, "read\n")) {
		read(file);
	}
	else if (!strcmp(pos, "edit")) {
		// line number; text
		pos = strtok_s(NULL, " ", &nextToken);

	}
	else if (!strcmp(pos, "delete")) {
		// line number

	}
	else if (!strcmp(pos, "help\n")) {
		printf("$ new [text]:  write the text of file\n");
		printf("$ read:  read entire file\n");
		printf("$ edit [line number] [text]:  edit the line number's text to inputted text\n");
		printf("$ delete [line number]:  delete the line number's text\n");
	}
	// command not found
	else {
		printf("Error: command not found\n");
	}
}