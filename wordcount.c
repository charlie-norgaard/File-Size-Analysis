/*
  Developer: Charlie Norgaard

  Description : this program emulates the wc unix command (i.e. wordcount
                receives one or more input files and returns the line, word,
                and/or character count of each given file.

  Compile program: gcc -Wall -o wordcount wordcount.c
*/

// Import libraries
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>


// This function checks if any command options were provided.
// Returns an int indiciating command option type (0,1,2,3).
int optionCheck(char* arg) {
    int cmdOption = 0;
    if (strcmp("-l", arg) == 0) {
       cmdOption = 1;
    } else if (strcmp("-w", arg) == 0) {
       cmdOption = 2;
    } else if (strcmp("-c", arg) == 0) {
       cmdOption = 3;
    }
       return cmdOption;
}

// This function checks if the given argument is a valid file.
// Returns 0 (false) if the file cannot be opened.
// Returns 1 (true) if the file can be opened.
int checkFileValid(char* file) {
    if (access(file, F_OK) == -1) {
        printf("%s cannot be opened. Skipping file...\n", file);
        fprintf(stderr, "%s cannot be opened. Skipping file...\n", file);
        return 0;
    } else {
        return 1;
    }
}

// This function processes a given file, calculates, and stores file stats.
void processFile(char* file, int* lineCount, int* wordCount, int*charCount) {
    // open the file
    FILE *openFile = fopen(file, "r");

    // bool to indicate if we are reading whitespace or not
    bool space = true;

    // loop through each char in file
    for (char c = getc(openFile); c != EOF; c = getc(openFile)) {
        // increment character count for each character found
        *charCount = *charCount + 1;
        // incremement line count if end of line byte is found
        if (c == '\n') {
            *lineCount = *lineCount + 1;
        }
        // incremement word count if char is not whitespace
        if (space && !isspace(c)) {
            *wordCount = *wordCount + 1;
            space = false;
        // inidicate that char is whitespace
        } else if (!space && isspace(c)) {
            space = true;
        }
    }
    // close file
    fclose(openFile);
}


// This function processes the given file according to any given command
// options.
void fileStats(char* file, int cmdOption, int* totalLineCount,
                     int* totalWordCount, int* totalCharCount) {
    // initialize single file counters
    int lineCount = 0;
    int wordCount = 0;
    int charCount = 0;
    // get single file stats
    processFile(file, &lineCount, &wordCount, &charCount);
    // update total counters
    *totalLineCount = *totalLineCount + lineCount;
    *totalWordCount = *totalWordCount + wordCount;
    *totalCharCount = *totalCharCount + charCount;
    // print results according to command option
    if (cmdOption == 1) {
        printf("%d\n", lineCount);
    } else if (cmdOption == 2) {
        printf("%d\n", wordCount);
    } else if (cmdOption == 3) {
        printf("%d\n", charCount);
    } else {
        printf("%d %d %d %s\n", lineCount, wordCount, charCount, file);
    }
}


int main(int argc, char **argv) {
    // checks if at least one input file has been provided
    if (argc < 2) {
        printf("Usage: ./wordcount requires an input file.\n");
        return 1;
    }

    // stores command option type in variable
    int cmdOption = optionCheck(argv[1]);

    // if a command option was provided,
    // need to start processing files at argv[2]
    int startIndex = 1;
    // if a command option is provided
    if (cmdOption != 0) {
        // checks if any file arguments are given
        if (argc < 3) {
            printf("Usage: ./wordcount requires an input file.\n");
            return 1;
        }
        // changes starting index to 2, so we can start checking arguments
        // after any given command options
        startIndex = 2;
    }

    // initialize total counters
    int totalLineCount = 0;
    int totalWordCount = 0;
    int totalCharCount = 0;
    // iterates through files in argv starting from file 1
    for (int i = startIndex; i < argc; i++) {
        // checks if given file is valid
        int fileValid = checkFileValid(argv[i]);
        // if file can be opened, calculates stats of file according
        // to cmd option
        if (fileValid == 1) {
            fileStats(argv[i], cmdOption, &totalLineCount,
                        &totalWordCount, &totalCharCount);
        }
    }

    // print total counters (if applicable)
    if (cmdOption == 0) {
        printf("%d total\n", totalLineCount);
    }

    // exit program with exit code 0
    return 0;
}
