/**
 * @file receive_guests.c
 * @author 
 * @date 2025/01/25
 * @brief Validates CLI arguments before starting the simulation.
 *
 * @details
 * This file contains input validation logic to ensure the philosopher
 * simulation receives correct parameters. Checks for syntax, value range,
 * and argument count before proceeding to initialize the simulation.
 *
 * @ingroup philosopher_core
 */

 #include "../include/philo.h"

 /**
  * @internal
  * @brief Check if a value falls within acceptable bounds.
  *
  * @details
  * Handles special rules for specific argument positions, like number of philosophers,
  * time values, and optional meal count. Also rejects negative or overflowed values.
  *
  * @param value The parsed integer value.
  * @param i The index of the argument being checked (1-based).
  *
  * @ingroup philosopher_core
  */
 static void	check_value(long long value, int i)
 {
	 if (value == -1)
	 {
		 ft_putstr_fd(2, "Error: integer overflow detected\n");
		 exit(EXIT_FAILURE);
	 }
	 if ((i == 1) && (value <= 0 || value > MAX_PHILO))
	 {
		 ft_putstr_fd(2, "Error: <number_of_philosophers> ");
		 ft_putstr_fd(2, "must be between 1 and 200\n");
		 exit(EXIT_FAILURE);
	 }
	 if ((i == 5) && (value <= 0))
	 {
		 ft_putstr_fd(2, "Error: <nbr_of_times_each_philosopher_must_eat> ");
		 ft_putstr_fd(2, "must be an integer greater than 0\n");
		 exit(EXIT_FAILURE);
	 }
	 if ((i > 1 && i < 5) && (value < 1))
	 {
		 ft_putstr_fd(2, "Error: ");
		 ft_putstr_fd(2, "<time_to_die> <time_to_eat> <time_to_sleep> ");
		 ft_putstr_fd(2, "must be integers greater than 0\n");
		 exit(EXIT_FAILURE);
	 }
 }
 
 /**
  * @internal
  * @brief Check if the argument string contains only digits.
  *
  * @param str The argument string to check.
  *
  * @ingroup philosopher_core
  */
 static void	check_syntax(char *str)
 {
	 while (*str)
	 {
		 if (*str < '0' || *str > '9')
		 {
			 ft_putstr_fd(2, "Wrong format: ");
			 ft_putstr_fd(2, "Arguments can only be positive integers\n");
			 exit(EXIT_FAILURE);
		 }
		 str++;
	 }
 }
 
 /**
  * @internal
  * @brief Validate each argument's syntax and numeric value.
  *
  * @details
  * Loops over each argument, checks its format and value using
  * `check_syntax` and `check_value`.
  *
  * @param argc Number of arguments.
  * @param argv Argument array.
  *
  * @ingroup philosopher_core
  */
 static void	validate_arguments(int argc, char **argv)
 {
	 int			i;
	 long long	value;
 
	 i = 1;
	 while (i < argc)
	 {
		 check_syntax(argv[i]);
		 value = ft_atoi(argv[i]);
		 check_value(value, i);
		 i++;
	 }
 }
 
 /**
  * @internal
  * @brief Ensure argument count is correct (either 5 or 6).
  *
  * @param argc Argument count.
  *
  * @ingroup philosopher_core
  */
 static void	validate_argument_count(int argc)
 {
	 if (argc < 5 || argc > 6)
	 {
		 ft_putstr_fd(2, "Wrong format\n");
		 ft_putstr_fd(2, "Usage: ");
		 ft_putstr_fd(2, "./philo <number_of_philosophers> ");
		 ft_putstr_fd(2, "<time_to_die> <time_to_eat> <time_to_sleep>\n");
		 ft_putstr_fd(2, " (Opt : <nbr_of_times_each_philosopher_must_eat>)\n");
		 exit(EXIT_FAILURE);
	 }
 }
 
 /**
  * @brief Validates command-line arguments for the philosopher simulation.
  *
  * @details
  * Ensures proper argument count, numeric format, and range constraints
  * for each required and optional parameter.
  *
  * @param argc Number of command-line arguments.
  * @param argv Array of argument strings.
  *
  * @ingroup philosopher_core
  */
 void	receive_guests(int argc, char **argv)
 {
	 validate_argument_count(argc);
	 validate_arguments(argc, argv);
 }
 