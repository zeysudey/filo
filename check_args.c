#include "philo.h"

void	error_message(int i)
{
	if (i == 1)
		write(2, "Invalid number_of_philosophers\n", 32);
	else if (i == 2)
		write(2, "Invalid time_to_die\n", 21);
	else if (i == 3)
		write(2, "Invalid time_to_eat\n", 21);
	else if (i == 4)
		write(2, "Invalid time_to_sleep\n", 23);
	else if (i == 5)
		write(2, "Invalid number_of_times_each_philosopher_must_eat\n", 51);
}

void check_args(char **argv)
{
    int i;
    int value;
    int j;

    i = 1;
    if (argv[5])
        j = 5;
    else
        j=4;
    while (i <= j)
    {
        value = ft_atoi(argv[i]);
        if (value <= 0)
        {
            error_message(i);
            exit(1);
        }
        i++;
    }
    if (ft_atoi(argv[1]) > 200)
    {
        write(2, "Error: Maximum 200 philosophers allowed\n", 41);
        exit(1);
    }
}

