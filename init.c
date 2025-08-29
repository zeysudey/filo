#include "philo.h"

int init_table(t_table *table, char **argv)
{
    static  t_fork forks[200];
    static  t_philo philos[200];
    
    table->philo_count = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);
    
    if (argv[5])
        table->meal_limit = ft_atoi(argv[5]);
    else
        table->meal_limit = -1;
    
    table->simulation_stop = 0;
    table->start_time = get_time();
    table->forks = forks;
    table->philos = philos;
    if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
        return (1);
    return (0);
}

int init_forks(t_table *table)
{
    int i;
    
    i = 0;
    while (i < table->philo_count)
    {
        
        if (pthread_mutex_init(&table->forks[i].mutex, NULL) != 0)
        {
            while (i > 0)
            {
                i--;
                pthread_mutex_destroy(&table->forks[i].mutex);
            }
            return (1);
        }
        i++;
    }
    return (0);
}

int init_philos(t_table *table)
{
    int i;
    
    i = 0;
    while (i < table->philo_count)
    {
        table->philos[i].id = i + 1;
        table->philos[i].meal_count = 0;
        table->philos[i].last_meal_time = table->start_time;
        table->philos[i].table = table;
        
        table->philos[i].first_fork = &table->forks[i].mutex;
        
        if (i == table->philo_count - 1)
            table->philos[i].second_fork = &table->forks[0].mutex;
        else
            table->philos[i].second_fork = &table->forks[i + 1].mutex;
        
        i++;
    }
    return (0);
}

int check_init(char **argv, t_table *table)
{
    if (init_table(table, argv) != 0) 
    {
        write(2, "Error: Failed to initialize table\n", 35);
        return (1);
    }
    if (init_forks(table) != 0)
    {
        write(2, "Error: Failed to initialize forks\n", 35);
        cleanup(table);
        return (1);
    }
    if (init_philos(table) != 0)
    {
        write(2, "Error: Failed to initialize philosophers\n", 42);
        cleanup(table);
        return (1);
    }
    return (0);
}