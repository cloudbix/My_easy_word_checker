#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]){
	
	int show_lines = 0;
	int show_words = 0;
	int show_chars = 0;

	if (argc != 3) {
        	fprintf(stderr, "Usage of: %s -lwc file\n", argv[0]);
        	return 1;
    	}
 
	FILE *inputFile = fopen(argv[2], "r");
	
	if(inputFile == NULL){ // check if file was open
    		fprintf(stderr, "Failed to open input file\n");
   		return 1;
	}

	/* argv[1] to np. "-lwc" */
    	if (argv[1][0] != '-') {
        	fprintf(stderr, "First argument needs to start by '-'\n");
        	return 1;
    	}

	for (const char *flags = argv[1] + 1; *flags != '\0'; flags++) {
		switch(*flags) {
			case 'l': show_lines = 1; break;
			case 'w': show_words = 1; break;	
			case 'c': show_chars = 1; break;	
			default:
				fprintf(stderr, "Unknown option: -%c\n", *flags);
				return 1;
		}
	}

	long lines = 0;
	long words = 0;
	long chars = 0;

	int ch;
	int in_word = 0;

	while((ch = fgetc(inputFile)) != EOF){
		chars++;

		if(ch == '\n') lines++;

		if(isspace(ch)){
			in_word = 0;
		}
		else if (!in_word){
			in_word = 1; 
			words++;
		}
	}

	fclose(inputFile);

	if (show_lines) printf("Number of lines: %ld \n", lines);
	if (show_words) printf("Number of words: %ld \n", words);
	if (show_chars) printf("Number of chars: %ld \n", chars);

	printf("%s\n", argv[2]);
	return 0;
}
