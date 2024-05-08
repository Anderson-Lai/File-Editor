#include <stdio.h>
#include <string.h>

void new(char* txt, FILE* file){
	rewind(file);

// moving file pointer to the end
int prev = '\n';
int c;
while ((c = fgetc(file)) != EOF) {
	prev = c;
}

// add a newline character if not 
// present at the end of the file
if ((char)prev != '\n') {
	fputc('\n', file);
}
fputs(txt, file);
}

void read(FILE* file) {
	rewind(file);

	int prev = '\n';
	int c;
	while ((c = fgetc(file)) != EOF) {
		prev = c;
		printf("%c", c);
	}
	if ((char)prev != '\n') {
		fputc('\n', file);
	}
}

void edit() {

}

void delete() {

}