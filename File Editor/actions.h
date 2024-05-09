

void add(char* txt, FILE* file) {
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

	long long counter = 1;
	char buffer[1024];

	while (fgets(buffer, sizeof(buffer), file)) {
		printf("%lld. %s", counter, buffer);
		counter++;

		memset(buffer, '\0', strlen(buffer));
	}
}

void edit(int line, char* txt, FILE* file, char* fileName) {
	rewind(file);

	FILE* temp = tmpfile();

	// copy contents to a temp file
	for (int i = 1; i < line; i++) {
		char buffer[1024];

		if (!fgets(buffer, sizeof(buffer), file) && !feof(file)) {
				printf("Error reading line\n");
				exit(EXIT_FAILURE);
		}
		fputs(buffer, temp);

	}
	
	// skip the line that is being edited
	char buffer[1024];
	if (!fgets(buffer, sizeof(buffer), file) && !feof(file)) {
		printf("Error reading line\n");
		exit(EXIT_FAILURE);
	}

	// write the edited text
	fputs(txt, temp);

	// get remaining text
	int c;
	while ((c = fgetc(file)) != EOF) {
		fputc(c, temp);
	}

	// truncate the file 
	fclose(file);
	errno_t err = fopen_s(&file, fileName, "w");
	if (err) {
		perror("Could not truncate file\n");
		exit(EXIT_FAILURE);
	}

	fclose(file);
	
	// reopen file
	err = fopen_s(&file, fileName, "r+");
	if (err) {
		perror("Could not re-open file\n");
		exit(EXIT_FAILURE);
	}

	// bring temp to beginning after
	// being written to 
	rewind(temp);

	// copy temp to now truncated 'file' file
	while ((c = fgetc(temp)) != EOF) {
		fputc(c, file);
	}

	// cleanup
	fclose(temp);
}

void delete(int line, FILE* file, char* fileName) {
	
	edit(line, "", file, fileName);
}