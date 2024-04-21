#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>


// Array representing the different states of key events
static const char *const key_states[3] = {
        "ВІДПУЩЕНО",
        "НАТИСНУТО",
        "ЗАТИСНУТО"
};

int main() {

    // Path to the keyboard device
    const char *keyboard_device = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    struct input_event event;
    ssize_t bytes_read;
    int device_fd;

    // Open the keyboard device for reading
    device_fd = open(keyboard_device, O_RDONLY);
    
    // Continuously read keyboard events
    while (1) {
        bytes_read = read(device_fd, &event, sizeof event);
        if (bytes_read == (ssize_t) -1) {
        
            // Check for interrupted system call
            if (errno == EINTR)
                continue;
            else
                break;
        } else if (bytes_read != sizeof event) {
            errno = EIO;
            break;
        }
        
        // Process only key events
        if (event.type == EV_KEY && event.value >= 0 && event.value <= 2)
        
            // Print the character value of the pressed key
            printf("%s %d\n", key_states[event.value], (int) event.code);

    }
    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));
    return EXIT_FAILURE;
}
