/**
 * @file set_dinner.c
 * @author 
 * @date 2025/01/25
 * @brief Functions for initializing philosophers and simulation parameters.
 *
 * @details
 * This file is responsible for:
 * - Allocating memory for philosophers and forks
 * - Initializing philosopher IDs, forks, and timing values
 * - Launching philosopher threads
 * - Setting simulation parameters from command-line input
 *
 * @ingroup philosopher_core
 */

 #include "../include/philo.h"

 /**
  * @brief Create and launch all philosopher threads.
  *
  * @details
  * Iterates over all philosophers and creates one thread per entity.
  * If any thread creation fails, the simulation is terminated.
  *
  * @param table Pointer to the table structure.
  * @return Always returns 0.
  *
  * @note Exits the program on failure to spawn a thread.
  *
  * @ingroup philosopher_core
  */
 int	seat_philosophers_at_the_table(t_table *table)
 {
	 int	i;
 
	 i = -1;
	 while (++i < table->philosopher_count)
	 {
		 if (pthread_create(&table->philo[i].thread, NULL,
				 dinner_routine, &table->philo[i]))
		 {
			 ft_putstr_fd(2, "Couldn't seat the philosophers\n");
			 end_dinner(table);
			 exit(EXIT_FAILURE);
		 }
	 }
	 return (0);
 }
 
 /**
  * @brief Allocate and initialize philosophers and fork mutexes.
  *
  * @details
  * Allocates memory for philosopher structures and fork mutexes.
  * Initializes each philosopher's ID, fork indexes, last meal time,
  * and references to the shared table.
  *
  * @param table Pointer to the table structure.
  *
  * @note Exits the program if allocation fails.
  *
  * @ingroup philosopher_core
  */
 void	welcome_philosophers(t_table *table)
 {
	 int	i;
 
	 i = -1;
	 table->philo = malloc(sizeof(t_philo) * table->philosopher_count);
	 table->fork_padlock = malloc(sizeof(pthread_mutex_t)
			 * table->philosopher_count);
	 if (!table->philo || !table->fork_padlock)
	 {
		 ft_putstr_fd(2, "Couldn't get the philosophers or forks\n");
		 clean_table(table);
		 exit(EXIT_FAILURE);
	 }
	 table->start_time = get_current_time();
	 while (++i < table->philosopher_count)
	 {
		 table->philo[i].id = i + 1;
		 table->philo[i].left_fork = i;
		 table->philo[i].right_fork = (i + 1) % table->philosopher_count;
		 table->philo[i].meal_count = 0;
		 table->philo[i].last_meal = table->start_time;
		 table->philo[i].table = table;
	 }
 }
 
 /**
  * @brief Parse command-line arguments and set simulation parameters.
  *
  * @details
  * Converts string arguments into integers and assigns them to the
  * corresponding fields of the `t_table` structure.
  * If the optional 6th argument is provided, sets a meal quota.
  *
  * @param table Pointer to the table structure.
  * @param argc Argument count.
  * @param argv Argument vector from command-line.
  *
  * @ingroup philosopher_core
  */
 void	set_table(t_table *table, int argc, char **argv)
 {
	 table->philosopher_count = ft_atoi(argv[1]);
	 table->time_to_die = ft_atoi(argv[2]);
	 table->time_to_eat = ft_atoi(argv[3]);
	 table->time_to_sleep = ft_atoi(argv[4]);
	 if (argc == 6)
		 table->must_eat_count = ft_atoi(argv[5]);
	 else
		 table->must_eat_count = -1;
	 table->end_flag = 0;
 }
 