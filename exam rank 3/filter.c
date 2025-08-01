#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif


void ft_filter(char *text, char *pattern) {
    int plen = strlen(pattern);
    int tlen = strlen(text);

    for (int i = 0; i <= tlen - plen; i++) {
        if (strncmp(&text[i], pattern, plen) == 0) {
            for (int j = 0; j < plen; j++) {
                text[i + j] = '*';  // replace matched substring with '*'
            }
            i += plen - 1;  // jump past replaced part
        }
    }
}

int main(int argc, char **argv)
{
	free(NULL);
    char temp[BUFFER_SIZE];
    char *buffer;
    char *res = NULL;
    int total_read = 0;
    ssize_t bytes;

    if(argc != 2)
        return 1;
    while((bytes = read(0, temp, BUFFER_SIZE)) > 0)
    {
        buffer = realloc(res, (total_read + bytes + 1));
        if(!buffer)
        {
            perror("realloc");
            free(res);
            return 1;
        }
        res = buffer;
        memmove((res + total_read), temp, bytes);
        total_read = total_read + bytes;
        res[total_read] = '\0';
    }
    if(bytes < 0)
    {
        free(res);
        perror("bytes");
        return 1;
    }
    if(!res)
        return 1;
    ft_filter(res, argv[1]); // function where u find and replace 
    write(1, res, total_read);  // print the filtered result
	free(res);
    return 0;
}
