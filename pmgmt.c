#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<fcntl.h>
#include <errno.h>
int main() {
    int fd1, fd2;
    ssize_t bytes_read, bytes_written;
    char buffer[1024];


    // Open input file "input.txt" for reading
    fd1 = open("input.txt", O_RDONLY);
    if (fd1 == -1) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }


    // Open output file "output.txt" for writing (create if not exists, truncate if exists)
    fd2 = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd2 == -1) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }


    // Read from input file and write to output file
    while ((bytes_read = read(fd1, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(fd2, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Write error");
            exit(EXIT_FAILURE);
        }
    }


    if (bytes_read == -1) {
        perror("Read error");
        exit(EXIT_FAILURE);
    }


    // Close input and output files
    if (close(fd1) == -1) {
        perror("Failed to close input file");
        exit(EXIT_FAILURE);
    }
    if (close(fd2) == -1) {
        perror("Failed to close output file");
        exit(EXIT_FAILURE);
    }


    printf("File copied successfully.\n");


    return 0;
}
