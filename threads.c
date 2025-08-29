#include "philo.h"

int create_philosopher_threads(t_table *table)
{
    int i;

    i = 0;
    while (i < table->philo_count)
    {
        if (pthread_create(&table->philos[i].thread_id,
                           NULL,
                           philosopher_routine,
                           &table->philos[i]) != 0)
        {
            write(2, "Error: Failed to create thread\n", 32);
            table->simulation_stop = 1;
            while (i > 0)
            {
                i--;
                pthread_join(table->philos[i].thread_id, NULL);
            }
            return (1);
        }
        i++;
    }
    return (0);
}

int create_monitor_thread(t_table *table, pthread_t *monitor_thread)
{
    if (pthread_create(monitor_thread, NULL, monitor_routine, table) != 0)
    {
        write(2, "Error: Failed to create monitor thread\n", 40);
        table->simulation_stop = 1;
        return (1);
    }
    return (0);
}

void join_all_threads(t_table *table, pthread_t monitor_thread)
{
    int i;

    pthread_join(monitor_thread, NULL);
    
    i = 0;
    while (i < table->philo_count)
    {
        pthread_join(table->philos[i].thread_id, NULL);
        i++;
    }
}

void join_philosopher_threads(t_table *table)
{
    int i;

    i = 0;
    while (i < table->philo_count)
    {
        pthread_join(table->philos[i].thread_id, NULL);
        i++;
    }
}
