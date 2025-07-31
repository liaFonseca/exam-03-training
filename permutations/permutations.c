#include "permutations.h"

int ft_strlen(char *str)
{
	int i = 0;
	while (str && str[i])
		i++;
	return i;
}


int	is_valid(char c, int index, char *sol)
{
	for (int i = 0; i < index; i++)
	{
		if (c == sol[i])
			return 0;
	}
	return 1;
}

void	permutations(int index, int max, char *options, char *sol)
{
	if (index == max)
		puts(sol);
	for (int i = 0; i < max; i++)
	{
		if(is_valid(options[i], index, sol))
		{
			sol[index] = options[i];
			permutations(index + 1, max, options, sol);
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		int max = ft_strlen(argv[1]);
		char *sol = malloc(sizeof(char) * (max + 1));
		if (!sol)
			return (1);
		sol[max] = '\0';
		permutations(0, max, argv[1], sol);
		free(sol);
	}
	return 0;
}
