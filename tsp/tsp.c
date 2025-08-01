#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

typedef struct tsp
{
	float x;
	float y;
} city;

float	euclidean_dist(city *a, city *b)
{
	float dx = b->x - a->x;
	float dy = b->y - a->y;
	return(sqrtf(dx*dx + dy*dy));
}

float calc_total_distance(city *cities, int *path, int n_cities)
{
	float total = 0;
	for (int i = 0; i < n_cities - 1; i++)
		total += euclidean_dist(&cities[path[i]], &cities[path[i+1]]);
	total += euclidean_dist(&cities[path[n_cities - 1]], &cities[path[0]]);
	return(total);
}
void	ft_swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void	find_shortest_path(city *cities, int n_city, int index, float *min_distance, int *path)
{
	if(index == n_city)
	{
		float curr_distance = calc_total_distance(cities, path, n_city);
		if(curr_distance < *min_distance)
			*min_distance = curr_distance;
		return;
	}
	for (int i = index; i < n_city; i++)
	{
		ft_swap(&path[index], &path[i]);
		find_shortest_path(cities, n_city, index + 1,min_distance, path);
		ft_swap(&path[index], &path[i]);
	}
}

int main()
{
	city cities[11];
	int n_city = 0;

	while(n_city < 11 && (scanf("%f, %f", &cities[n_city].x, &cities[n_city].y)) == 2)
		n_city++;
	for (int i = 0; i < n_city; i++)
		printf("%f, %f\n", cities[i].x, cities[i].y);
	if(n_city < 2)
	{
		printf("0.00\n");
		return 0;
	}
	int path[11];
	for (int i= 0; i < n_city; i++)
		path[i] = i;
	float min_distance = FLT_MAX;
	find_shortest_path(cities, n_city, 1, &min_distance, path);
	printf("%.2f\n", min_distance);
	return 0;
}