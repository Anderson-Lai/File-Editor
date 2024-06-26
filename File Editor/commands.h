#include "actions.h"

void handleCommand(char* fullCommand, FILE* file, char* fileName) {

	// splitting the command
	char* nextToken = nullptr;
	char* pos = strtok_s(fullCommand, " ", &nextToken);

	// check if a command has been entered
	if (!pos) {
		perror("Enter a valid command");
		return;
	}

	// control flow
	if (!strcmp(pos, "add")) {
		// get the text
		pos = strtok_s(nullptr, "", &nextToken);

		add(pos, file);
	}
	// add '\n' as pos will read the entire string
	else if (!strcmp(pos, "read\n")) {

		read(file);
	}
	else if (!strcmp(pos, "edit")) {

		// get the line number and text
		pos = strtok_s(nullptr, " ", &nextToken);
		int line = atoi(pos);

		pos = strtok_s(nullptr, "", &nextToken);

		edit(line, pos, file, fileName);
	}
	else if (!strcmp(pos, "delete")) {
		
		// get the line number
		pos = strtok_s(nullptr, " ", &nextToken);
		int line = atoi(pos);

		delete(line, file, fileName);
	}
	else if (!strcmp(pos, "help\n")) {
		printf("$ add [text]:  add the text to the end of the file\n");
		printf("$ read:  read entire file\n");
		printf("$ edit [line number] [text]:  edit the line number's text to inputted text\n");
		printf("$ delete [line number]:  delete the line number's text\n");
		printf("$ exit:  exit the text editor\n");
	}
	// command not found
	else {
		printf("Error: command not found\n");
	}
}