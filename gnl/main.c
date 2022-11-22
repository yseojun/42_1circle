#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd1;
	int fd2;

	fd1 = open("text.txt", O_RDONLY);
	fd2 = open("text2.txt", O_RDONLY);

	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd1));
}