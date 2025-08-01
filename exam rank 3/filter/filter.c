#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFERSIZE
# define BUFFERSIZE 20
#endif


char *ft_memmem(char *source, size_t len_src, char *key, size_t len_key)
{
	if (!key || !source)
		return NULL;
	for(size_t s = 0; s < len_src; s++)
	{
		for(size_t k = 0; k < len_key + 1 ; k++)
		{
			if(!key[k])
				return (&source[s]);
			if(!source[s + k] || source[s + k] != key[k])
				break;
		}
	}
	return NULL;
}


void	filter(char *str, char *key)
{
	char *found = str;
	while ((found = ft_memmem(found, strlen(str), key, strlen(key))) > 0)
	{
		for(int i = 0; i < (int)strlen(key); i++)
			found[i] = '*';
		found += strlen(key);
	}
}



int main(int argc, char *argv[])
{
	char	temp[BUFFERSIZE+1];
	char *buffer;
	char *str = NULL;
	size_t bytes_read = 0;
	size_t total_read = 0;

	if (argc != 2)
		return 1;
	while ((bytes_read = read(0, temp, BUFFERSIZE)) > 0)
	{
		buffer = realloc(str, (total_read + bytes_read + 1));
		if (!buffer)
		{
			perror("realloc");
			free(str);
			return 1;
		}
		str = buffer;
		memmove((str + total_read), temp, bytes_read);
		total_read += bytes_read;
		str[total_read] = '\0';
	}
	if(bytes_read < 0)
	{
		perror("bytes");
		free(str);
		return 1;
	}
	if (!str)
		return 1;
	filter(str, argv[1]);
	write(1, str, total_read);
	free(str);
	return 0;
}