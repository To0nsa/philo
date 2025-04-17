/**
 * @file set_rules.c
 * @author 
 * @date 2025/01/25
 * @brief Initialize mutexes used for philosopher synchronization.
 *
 * @details
 * This file sets up all necessary pthread mutexes for forks and
 * shared resources like printing, eating, and simulation termination.
 * It also provides rollback and cleanup on partial initialization failures.
 *
 * @ingroup philosopher_core
 */

 #include "../include/philo.h"

 /**
  * @internal
  * @brief Recursively destroy previously initialized fork mutexes.
  *
  * @details
  * Used as a rollback mechanism if a fork mutex fails to initialize mid-loop.
  *
  * @param table Pointer to the shared simulation table.
  * @param count Index of the last successfully initialized mutex.
  *
  * @ingroup philosopher_core
  */
 static void	unset_previous_forks_rules(t_table *table, int count)
 {
	 if (count < 0)
		 return ;
	 pthread_mutex_destroy(&table->fork_padlock[count]);
	 unset_previous_forks_rules(table, count - 1);
 }
 
 /**
  * @internal
  * @brief Initialize all fork mutexes in the simulation.
  *
  * @details
  * If any initialization fails, all prior mutexes are destroyed,
  * and global mutexes are cleaned up before exiting the program.
  *
  * @param table Pointer to the simulation table.
  *
  * @ingroup philosopher_core
  */
 static void	set_forks_rules(t_table *table)
 {
	 int	i;
 
	 i = -1;
	 while (++i < table->philosopher_count)
	 {
		 if (pthread_mutex_init(&table->fork_padlock[i], NULL))
		 {
			 ft_putstr_fd(2, "Error initializing fork mutex\n");
			 unset_previous_forks_rules(table, i - 1);
			 pthread_mutex_destroy(&table->print_padlock);
			 pthread_mutex_destroy(&table->eat_padlock);
			 pthread_mutex_destroy(&table->end_padlock);
			 exit(EXIT_FAILURE);
		 }
	 }
 }
 
 /**
  * @brief Set all mutexes required for simulation control.
  *
  * @details
  * Initializes:
  * - `print_padlock`: for synchronized output
  * - `eat_padlock`: to protect meal tracking
  * - `end_padlock`: to guard simulation state
  * - All fork mutexes
  *
  * @note If any mutex fails to initialize, previously created ones are cleaned up.
  *
  * @param table Pointer to the simulation table.
  *
  * @ingroup philosopher_core
  */
 void	set_rules(t_table *table)
 {
	 if (pthread_mutex_init(&table->print_padlock, NULL) != 0)
	 {
		 ft_putstr_fd(2, "Error initializing print_padlock\n");
		 exit(EXIT_FAILURE);
	 }
	 if (pthread_mutex_init(&table->eat_padlock, NULL) != 0)
	 {
		 ft_putstr_fd(2, "Error initializing print_padlock\n");
		 pthread_mutex_destroy(&table->print_padlock);
		 exit(EXIT_FAILURE);
	 }
	 if (pthread_mutex_init(&table->end_padlock, NULL) != 0)
	 {
		 ft_putstr_fd(2, "Error initializing end_padlock\n");
		 pthread_mutex_destroy(&table->print_padlock);
		 pthread_mutex_destroy(&table->eat_padlock);
		 exit(EXIT_FAILURE);
	 }
	 set_forks_rules(table);
 }
 