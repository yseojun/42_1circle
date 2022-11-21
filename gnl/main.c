#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	char	buffer[10];
	buffer[0] = '\0';

	int	fd = open("text.txt", O_RDWR);
	int size = read(fd, buffer, 10);
	write(1, buffer, 2);
}

123^@1234\n

123345