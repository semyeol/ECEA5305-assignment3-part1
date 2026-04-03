// Accepts the following arguments: the first argument is a full path to a file (including filename) on the filesystem, 
// referred to below as writefile; the second argument is a text string which will be written within this file, referred to below as writestr

// Exits with value 1 error and print statements if any of the arguments above were not specified

// Creates a new file with name and path writefile with content writestr, overwriting any existing file and creating the path if it doesn’t exist. 
// Exits with value 1 and error print statement if the file could not be created.

// One difference from the write.sh instructions in Assignment 1:  You do not need to make your "writer" utility create directories which do not exist.  
// You can assume the directory is created by the caller.

// Setup syslog logging for your utility using the LOG_USER facility.

// Use the syslog capability to write a message “Writing <string> to <file>” where <string> is the text string written to file (second argument) and <file> 
// is the file created by the script.  This should be written with LOG_DEBUG level.

// Use the syslog capability to log any unexpected errors with LOG_ERR level.

#include<stdio.h>
#include<stdlib.h>
#include<syslog.h>

int main(int argc, char *argv[]) {
    openlog("main", LOG_PID, LOG_USER); // open connection

    if (argc < 3) {
        fprintf(stderr, "One or more arguments were not specified.\n");
        syslog(LOG_ERR, "One or more args were not specified.");
        return 1;
    }

    FILE *fp = fopen(argv[1], "w");

    if (fp == NULL) {
        fprintf(stderr, "File could not be created.\n");
        syslog(LOG_ERR, "File could not be created.");
        return 1;
    }

    fprintf(fp, "%s", argv[2]);

    syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);

    fclose(fp);
    closelog();

    return 0;
}