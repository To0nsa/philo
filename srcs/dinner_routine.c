/**
 * @file dinner_routine.c
 * @author 
 * @date 2025/01/25
 * @brief Implements the behavior of each philosopher thread.
 *
 * @details
 * This file defines the main routine that each philosopher thread executes.
 * Handles eating, sleeping, and thinking in a loop, using mutexes to
 * synchronize access to forks. Also covers the edge case of a single philosopher.
 *
 * @ingroup philosopher_core
 */

 #include "../include/philo.h"

 /**
  * @internal
  * @brief Execute the eating phase of a philosopher's routine.
  *
  * @details
  * Locks both forks (with deadlock avoidance ordering), prints actions,
  * updates last meal time, increments meal count, and then unlocks the forks.
  *
  * @param philo Pointer to the philosopher executing this phase.
  *
  * @ingroup philosopher_core
  */
 static void	dinner_time(t_philo *philo)
 {
	 if (philo->id % 2 == 0)
	 {
		 pthread_mutex_lock(&philo->table->fork_padlock[philo->left_fork]);
		 pthread_mutex_lock(&philo->table->fork_padlock[philo->right_fork]);
	 }
	 else
	 {
		 pthread_mutex_lock(&philo->table->fork_padlock[philo->right_fork]);
		 pthread_mutex_lock(&philo->table->fork_padlock[philo->left_fork]);
	 }
	 print_action(philo, TAKE);
	 print_action(philo, TAKE);
	 print_action(philo, EAT);
	 advance_time(philo, philo->table->time_to_eat);
	 pthread_mutex_lock(&philo->table->eat_padlock);
	 philo->meal_count++;
	 philo->last_meal = get_current_time();
	 pthread_mutex_unlock(&philo->table->eat_padlock);
	 pthread_mutex_unlock(&philo->table->fork_padlock[philo->right_fork]);
	 pthread_mutex_unlock(&philo->table->fork_padlock[philo->left_fork]);
 }
 
 /**
  * @internal
  * @brief Handles the edge case where there's only one philosopher.
  *
  * @details
  * The lone philosopher picks up a fork, waits until `time_to_die`,
  * and is then declared dead.
  *
  * @param table Pointer to the table structure.
  *
  * @ingroup philosopher_core
  */
 static void	lone_philosopher(t_table *table)
 {
	 print_action(&table->philo[0], TAKE);
	 advance_time(&table->philo[0], table->time_to_die);
	 print_action(&table->philo[0], DIE);
	 is_dinner_over(&table->philo[0], true);
 }
 
 /**
  * @brief Entry point for each philosopher thread.
  *
  * @details
  * Simulates the life of a philosopher through an infinite loop of:
  * thinking, picking up forks, eating, sleeping. Handles the case
  * of even/odd IDs and philosopher count for timing offset.
  *
  * @note Terminates early if only one philosopher exists, or
  * if the dinner has ended (`is_dinner_over` returns true).
  *
  * @param arg A pointer to the philosopher's `t_philo` struct.
  * @return Always returns NULL.
  *
  * @ingroup philosopher_core
  */
 void	*dinner_routine(void *arg)
 {
	 t_philo	*philo;
 
	 philo = (t_philo *)arg;
	 if (philo->id % 2 == 0)
		 advance_time(philo, philo->table->time_to_eat / 2);
	 while (true)
	 {
		 if (philo->table->philosopher_count == 1)
		 {
			 lone_philosopher(philo->table);
			 return (0);
		 }
		 if (is_dinner_over(philo, false))
			 return (0);
		 print_action(philo, THINK);
		 dinner_time(philo);
		 print_action(philo, SLEEP);
		 advance_time(philo, philo->table->time_to_sleep);
		 if (philo->table->philosopher_count % 2 != 0)
			 advance_time(philo, philo->table->time_to_eat);
	 }
	 return (0);
 }
 