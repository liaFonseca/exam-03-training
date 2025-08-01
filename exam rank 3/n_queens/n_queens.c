#include "n_queens.h"

void print_sol(int n, int *sol)
{
	printf("%d", sol[0]);
	for(int i = 1; i < n; i++)
		printf(" %d", sol[i]);
	printf("\n");
}

int ft_abs(int n)
{
	if (n < 0)
		return (n * - 1);
	return (n);
}

int	is_valid(int i, int it, int *sol)
{
	for (int num = 0; num < it; num++)
	{
		if (sol[num] == i || ft_abs(sol[num] - i) == ft_abs(num - it))
			return (0);
	}
	return (1);
}

void	n_queens(int it, int n, int *sol)
{
	if (it == n)
		print_sol(n, sol);
	
	for(int i = 0; i < n; i++)
	{
		if (is_valid(i, it, sol))
		{
			sol[it] = i;
			n_queens(it + 1, n, sol);
		}
	}
}

int	main(int argc, char *argv[])
{
	int n;
	int *sol;

	if (argc == 2)
	{
		n = atoi(argv[1]);
		sol = malloc(sizeof(int) * n);
		if (!sol)
			return (1);
		n_queens(0, n, sol);
		free(sol);
	}
	return (0);
}