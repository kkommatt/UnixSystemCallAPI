#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pid> <address>\n", argv[0]);
        return -1;
    }

    // Extract command-line arguments
    char *pid_str = argv[1];
    unsigned long long address = strtoull(argv[2], NULL, 16);
    int size = 1000;

    // Construct the filename for memory access
    char filename[256];
    sprintf(filename, "/proc/%s/mem", pid_str);

    // Print information about the file, memory address, and size
    printf("File: %s\nAddress: %p\n", filename, (void *)address);

    // Open the file for reading
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        return -1;
    }

    // Seek to the specified memory address
    off_t res = lseek(fd, (off_t)address, SEEK_SET);
    if (res == (off_t)-1) {
        perror("Failed to seek to address");
        close(fd);
        return -1;
    }

    // Allocate memory for storing the read data
    char *data = (char *)malloc(size + 1);
    if (data == NULL) {
        perror("Memory allocation failed");
        close(fd);
        return -1;
    }
    // Initialize the memory to zero
    memset(data, 0, size + 1);

    // Read data from the memory address
    ssize_t bytes_read = read(fd, data, size);
    if (bytes_read == -1) {
        perror("Failed to read memory");
        free(data);
        close(fd);
        return -1;
    }

    // Print the read data
    printf("Value: \"%s\"\n", data);

    // Clean up and close the file descriptor
    free(data);
    close(fd);

    return 0;
}

