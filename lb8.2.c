#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd = open("test.bin", O_RDONLY);
	if (fd == -1){
		perror("open");
		return 1;
	}
	
	unsigned char buffer[4];

	if (lseek(fd,3,SEEK_SET) == -1){
		perror("lseek");
		close(fd);
		return 1;
	}

	ssize_t bytes_read = read(fd, buffer, 4);
	if (bytes_read == -1){
		perror("read");
		close(fd);
		return 1;
	}

	printf("Read bytes:\n");
	for (int i = 0; i < bytes_read; i++){
		printf("buffer[%d] = %d\n", i, buffer[i]);
	}

	close(fd);
	return 0;
}





	




