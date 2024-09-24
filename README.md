# philosophers

### Introduction

This project is an implementation of the classic Dining Philosophers Problem, a fundamental problem in concurrent programming. The goal is to synchronize philosophers, who alternate between eating, thinking, and sleeping, while avoiding deadlocks (when no one can eat) and ensuring all philosophers get to eat. This problem illustrates issues in resource sharing and synchronization, making it a great tool for learning multi-threaded programming.

### Problem Description

In the dining philosophers problem, several philosophers are seated around a table with a fork between each pair. To eat, a philosopher needs to pick up both the fork on their left and the fork on their right. After eating, they put the forks down and think before the next meal.

The challenge is to implement this in a way that avoids:

1. Deadlocks: where every philosopher is holding one fork and waiting for the other, leading to no one being able to eat.
2. Race conditions: where philosophers might try to pick up or release forks simultaneously, corrupting the system state.

### Tools and Concepts Used

- POSIX Threads (pthreads): Used for creating concurrent threads representing philosophers.
- Mutexes (pthread_mutex_t): Used to synchronize access to shared resources (forks) and prevent race conditions.

### Code structure

#### Input
The input data is stored in the t_state struct, which contains global settings and mutexes:
``` C
typedef struct s_state
{
	t_milliseconds   s_start;
	t_milliseconds   time_to_die;
	t_milliseconds   time_to_eat;
	t_milliseconds   time_to_sleep;
	int              nb_philos;
	int              meal_count;

	pthread_mutex_t  forks[MAX_COUNT];
	pthread_mutex_t  print_mtx;

	pthread_mutex_t  exit_mtx;
	int              exit;
}	t_state;
```
This struct holds time parameters, the number of philosophers, shared mutexes for forks, and a flag to signal if a philosopher has died.
#### Philosopher Logic
Each philosopher is represented by the t_philo struct:
``` C
typedef struct s_philo
{
    int              idx;

    int              eaten_times;
    pthread_mutex_t  eaten_times_mutex;

    pthread_mutex_t  last_meal_mtx;
    t_milliseconds   last_meal;

    t_state          *state;
} t_philo;
```
Philosophers operate in a cycle of eating, sleeping, and thinking. Their behavior is controlled by a routine running in separate threads:
```C
void	*routine(void *philo_void)
​{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if (philo->state->nb_philos == 1)
	​￼{
		usleep(philo->state->time_to_die);
		return (NULL);
	}
	while (1)
	​￼{
		​￼if (eat(philo))
			return (NULL);
		​￼if (philo_sleep(philo))
			return (NULL);
		​￼if (think(philo))
			return (NULL);
	}
}
```
#### Deadlock prevention
To avoid deadlocks:
- Philosophers with even indices pick up their right fork first, while odd ones pick up their left fork first.
- A delay is added to prevent a philosopher from immediately re-attempting to eat after finishing.
```C
int	eat(t_philo *philo)
​{
	int	left;
	int	right;

	​￼if (is_somebody_dead(philo))
		return (EXIT);
	left = philo->idx;
	right = (left + 1) % philo->state->nb_philos;
	if (philo->idx % 2)
	​￼{
		​￼if (right_first(philo, right, left))
			return (EXIT);
	}
	else
	​￼{
		​￼if (left_first(philo, right, left))
			return (EXIT);
	}
	print_message(EAT, philo);
	update_meal_fields(philo);
	usleep(philo->state->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->state->forks[left]);
	pthread_mutex_unlock(&philo->state->forks[right]);
	return (SUCCESS);
}
```
This routine locks the appropriate forks, updates the philosopher’s state, and ensures all resources are properly released after eating.
#### Mutex usage
- Forks: Each fork is represented by a mutex. Philosophers lock the appropriate fork mutexes before eating and unlock them afterward.
- Print: A mutex is used to control access to printing messages to avoid garbled output.
- Meal Count and Last Meal Time: Mutexes are used to protect these fields as they are updated by multiple threads.
#### Features
- Deadlock-free: The code ensures that no deadlock conditions are met by controlling the order in which forks are picked up.
- Thread-safe: All shared resources are protected by mutexes to ensure consistency and prevent race conditions.
