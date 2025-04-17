/**
 * @file philo.h
 * @author Toonsa
 * @date 2025/01/25
 * @brief Core declarations for the Dining Philosophers project.
 * 
 * @details
 * This header contains the main data structures and function prototypes
 * used in the philosopher simulation, including philosopher state,
 * table settings, synchronization primitives, and lifecycle routines.
 * 
 * @ingroup philosopher_core
 */

 #ifndef PHILO_H
 # define PHILO_H
 
 # include <pthread.h>
 # include <unistd.h>
 # include <stdio.h>
 # include <stdlib.h>
 # include <stdbool.h>
 # include <limits.h>
 # include <errno.h>
 # include <sys/time.h>
 
 /**
  * @defgroup philosopher_core Philosopher Core
  * @brief Core types and functions for the Dining Philosophers simulation.
  * 
  * @details
  * Defines philosopher entities, table configuration, and all essential
  * synchronization and lifecycle routines.
  * 
  * @{
  */
 
 /**
  * @typedef t_philo
  * @brief Represents a single philosopher in the simulation.
  *
  * @details
  * Contains:
  * - `id`: Unique identifier of the philosopher (0-based index).
  * - `meal_count`: Number of meals eaten.
  * - `left_fork`: Index of the left fork.
  * - `right_fork`: Index of the right fork.
  * - `last_meal`: Timestamp of the last meal in milliseconds.
  * - `table`: Pointer to the shared table structure.
  * - `thread`: Thread handle running this philosopher's routine.
  */
 typedef struct s_philo
 {
	 int				id;              ///< Unique philosopher ID
	 int				meal_count;      ///< How many meals have been eaten
	 int				left_fork;       ///< Index of the left fork
	 int				right_fork;      ///< Index of the right fork
	 long long		last_meal;       ///< Last meal timestamp
	 struct s_table	*table;          ///< Pointer to shared table
	 pthread_t		thread;          ///< Associated thread
 }					t_philo;
 
 /**
  * @typedef t_table
  * @brief Configuration and global state shared by all philosophers.
  *
  * @details
  * Contains:
  * - Simulation parameters like timeouts and counts.
  * - Philosopher list and synchronization primitives.
  * - Flags for termination, meal tracking, and start time.
  */
 typedef struct s_table
 {
	 int				philosopher_count;  ///< Total number of philosophers
	 int				time_to_die;        ///< Time until a philosopher dies without eating
	 int				time_to_eat;        ///< Time spent eating
	 int				time_to_sleep;      ///< Time spent sleeping
	 long long		start_time;         ///< Timestamp when simulation started
	 int				must_eat_count;     ///< Minimum meals required per philosopher
 
	 int				meal_count;         ///< Shared count of meals eaten
	 int				is_full;            ///< Flag indicating all philosophers are full
	 int				end_flag;           ///< Flag to terminate simulation
 
	 t_philo			*philo;             ///< Array of philosopher entities
	 pthread_mutex_t	*fork_padlock;      ///< Array of mutexes representing forks
	 pthread_mutex_t	print_padlock;      ///< Mutex for printing messages
	 pthread_mutex_t	eat_padlock;        ///< Mutex for updating meal stats
	 pthread_mutex_t	end_padlock;        ///< Mutex for accessing end flag
 }					t_table;
 
 /* === Status Macros === */
 # define MAX_PHILO 200
 
 # define TAKE		"has taken a fork"
 # define EAT		"is eating"
 # define SLEEP		"is sleeping"
 # define THINK		"is thinking"
 # define DIE		"died"
 # define END		"e"
 # define END_MSG	"All philosophers ate enough!"
 
 /* === Initialization === */
 void		receive_guests(int argc, char **argv);
 void		set_table(t_table *table, int argc, char **argv);
 void		welcome_philosophers(t_table *table);
 void		set_rules(t_table *table);
 int			seat_philosophers_at_the_table(t_table *table);
 
 /* === Simulation Core === */
 void		*dinner_routine(void *arg);
 bool		is_dinner_over(t_philo *philo, bool order);
 void		advance_time(t_philo *philo, long long ms);
 void		print_action(t_philo *philo, const char *status);
 
 /* === Monitoring & Cleanup === */
 void		dinner_monitor(t_table *table);
 void		clean_table(t_table *table);
 void		end_dinner(t_table *table);
 
 /* === Utility === */
 long long	get_current_time(void);
 long long	ft_atoi(const char *str);
 int			ft_putstr_fd(int fd, char *str);
 
 /** @} */ // end of philosopher_core
 
 #endif
 