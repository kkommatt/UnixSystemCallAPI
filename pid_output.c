#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_DATA_SIZE 1000 // Maximum size of data array

int main() {
    char data[MAX_DATA_SIZE];
    char input[MAX_DATA_SIZE];
    int continue_flag = 1;

    while (continue_flag) {
        // Prompt user to enter a string
        printf("Enter a string (-1 to finish): ");
        fgets(input, sizeof(input), stdin);

        // Check if user wants to terminate
        if (strcmp(input, "-1\n") == 0) {
            continue_flag = 0;
            break;
        }

        // Copy the entered string to the data array
        strncpy(data, input, sizeof(data) - 1);
        data[sizeof(data) - 1] = '\0'; // Ensure null-termination

        // Print process ID, data address, and data size
        printf("PID: %d\nAddress: %p\n", getpid(), (void *)data);
    }

    return 0;
}

