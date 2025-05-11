#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

    char buffer[4096];
    memset(buffer, 'A', sizeof(buffer));

    ssize_t total_written = 0;
    while (1) {
        ssize_t count = write(pipefd[1], buffer, sizeof(buffer));
        if (count == -1) {
            perror("write");
            break;
        } else if (count < sizeof(buffer)) {
            printf("Written: %zd with %zu bytes\n", count, sizeof(buffer));
            break;
        } else {
            total_written += count;
            printf("Writen %zd bytes: %zd\n", count, total_written);
        }
    }

    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
