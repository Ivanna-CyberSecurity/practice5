#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_help() {
    printf("Simple Command Processor\n");
    printf("Usage: command_processor [-h|--help] [-b|--buffer <buffer_size>]\n");
    printf("Options:\n");
    printf("  -h, --help            Show this help message\n");
    printf("  -b, --buffer <size>   Set the command buffer size (default: 127)\n");
}

int main(int argc, char *argv[]) {
    int buffer_size = 127; 

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--buffer") == 0) {
            if (i + 1 < argc) {
                buffer_size = atoi(argv[i + 1]);
                if (buffer_size <= 0) {
                    printf("Invalid buffer size. Using default size (127).\n");
                    buffer_size = 127;
                }
            }
        }
    }

    char *username = getenv("USER");
    if (username == NULL) {
        printf("Unknown user\n");
        return 1;
    }

    printf("Welcome, %s!\n", username);
    printf("[%s]$", username);

    char command[buffer_size];
    while (1) {
        if (fgets(command, buffer_size, stdin) == NULL) {
            break;
        }

        if (strcmp(command, "stop\n") == 0) {
            printf("Wait 3 seconds...\n");
            sleep(3);
            printf("\033[H\033[J"); 
            break;
        }

        int result = system(command);
        if (result == -1) {
            printf("Error executing the command.\n");
        }
    }

    return 0;
}