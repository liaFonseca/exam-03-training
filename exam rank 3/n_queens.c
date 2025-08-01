#include <stdio.h>
#include <stdlib.h>

void print_sol(int *sol, int n)
{
	int i = 0;

	printf("%d", sol[i++]);
	while (i<n)
		printf(" %d", sol[i++]);	
	printf("\n");
}

int is_safe(int *sol, int col, int row)
{
	for (int i = 0; i< col; i++)
	{
		if ( sol[i] == row || abs(sol[i] - row) == abs(i - col))
			return 0;
	}
	return 1;
}

void solve(int *sol, int col, int n)
{
	if (col == n)
		print_sol(sol, n);
	for (int row = 0; row < n; row++)
	{
		if (is_safe(sol, col, row))
		{
			sol[col] = row;
			solve(sol, col+1, n);
		}
	}
}


void	n_queens(int n)
{
	int *sol = malloc(n*(sizeof (int)));

	solve(sol, 0, n);
	free(sol);
}

int main(int argc, char *argv[])
{
	if(argc >1 )
		n_queens(atoi(argv[1]));
	return 0;
}