#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"command(s)\"\n", argv[0]);
        return 1;
    }

    char *commands = argv[1];
    char *command = strtok(commands, ";");

    while (command != NULL) {
        int exit_status = system(command);

        if (WIFEXITED(exit_status)) {
            int status = WEXITSTATUS(exit_status);
            printf("Command '%s' exited with status %d\n", command, status);
        } else {
            printf("Failed to execute command '%s'\n", command);
        }

        command = strtok(NULL, ";");
    }

    return 0;
}