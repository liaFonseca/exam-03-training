#include "powerset.h"

void print_sol(int index, int *sol)
{
	if(index > 0)
		printf("%d", sol[0]);
	for (int i = 1; i < index; i++)
		printf(" %d", sol[i]);
	printf("\n");
}

void powerset(int index, int result, int *nums, int n_nums, int *sol)
{
	if (!result)
		print_sol(index, sol);
	for(int i = 0; i < n_nums; i++)
	{
		sol[index] = nums[i];
		powerset(index + 1, result - nums[i], nums + i + 1, n_nums - i - 1, sol);
	}
}


int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		int result = atoi(argv[1]);
		int n_nums = argc - 2;
		int *sol = calloc(n_nums, sizeof(int));
		int *nums = calloc(n_nums, sizeof(int));
		if(!sol || !nums)
		{
			free(sol);
			free(nums);
			return 1;
		}
		argv += 2;
		for(int i = 0; i < n_nums; i++)
			nums[i] = atoi(argv[i]);
		powerset(0, result, nums, n_nums, sol);
		free(sol);
	}
	return 0;
}