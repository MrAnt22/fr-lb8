#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(){
	char buffer[] = "AAAAAAAAAaaaaaaaa aaaaAAAA bbbbBBbbBBbbBbBBBBbbBBbb";
	int fd[2];

	if (pipe(fd) == -1){
		perror("pipe");
		return 1;
	}

	fcntl(fd[1], F_SETFL, O_NONBLOCK);

	for (int i = 0; i < 10000; ++i){
		write(fd[1], "a", 1);
	}

	ssize_t count = write(fd[1], buffer, strlen(buffer));

	if (count == -1){
		perror("write");
	}
	else{
		printf("requested %ld bytes|wroted %ld bytes\n", strlen(buffer), count);
	}

	close(fd[0]);
	close(fd[1]);
	return 0;
}





