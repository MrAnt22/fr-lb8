#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	pid_t pid;
	pid = fork();

	if(pid == -1){
		perror("fork");
		return 1;
	}

	printf("pid = %d\n", pid);
	
	return 0;
}
