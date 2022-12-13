#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{
    char    *str;

    int i = 0;
    int fd1 = open("test", O_RDONLY);
    int fd2 = open("test2", O_RDONLY);
    int fd3 = open("test3", O_RDONLY);
    while (i++ < 3)
    {
        str = get_next_line(fd1);
        printf("%s", str);
        free(str);
        str = get_next_line(fd2);
        printf("%s", str);
        free(str);
        str = get_next_line(fd3);
        printf("%s", str);
        free(str);
    }
    // system("leaks a.out");
    return (0);
}