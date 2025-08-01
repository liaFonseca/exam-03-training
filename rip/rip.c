#include <stdio.h>

int is_valid(char *str)
{
	int balance = 0;

	for (int i = 0; str[i]; i++)
	{
		if(str[i] == '(')
			balance++;
		else if (str[i] == ')')
			balance--;
		if (balance < 0)
			return 0;
	}
	return (balance == 0);
}

int count(char *str, char c)
{
	int count = 0;

	for(int i = 0; str[i]; i++)
	{
		if(str[i] == c)
			count++;
	}
	return count;
}
void rip (char *str, int i_str, int min_removals, int curr_removals)
{
	if (curr_removals == min_removals && is_valid(str))
	{
		puts(str);
		return;
	}
	for (int i = i_str; str[i]; i++)
	{
		char saved = str[i];
		str[i] = ' ';
		rip(str, i + 1, min_removals, curr_removals + 1);
		str[i] = saved;
	}
}

void get_min_removals(char *str, int i_str, int *min_removals,int curr_removals)
{
	if (curr_removals > *min_removals)
		return;
	if (is_valid(str))
	{
		*min_removals = curr_removals;
		return;
	}
	for(int index = i_str; str[index]; index++)
	{
		char saved = str[index];
		str[index] = ' ';
		get_min_removals(str, index + 1, min_removals, curr_removals + 1);
		str[index] = saved;
	}
}


int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		int i = 0;
		while (argv[1][i])
		{
			if (argv[1][i] != '(' && argv[1][i] != ')')
				return 1;
			i++;
		}
		
		if (is_valid(argv[1]))
			puts(argv[1]);

		else
		{
			int min_removals = i;
			get_min_removals(argv[1], 0, &min_removals, 0);
			rip(argv[1], 0, min_removals, 0);
		}
	}
	return 0;
}