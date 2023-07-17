# philosophers
42/Codam introduction to multithreading/concurrency written in C.

## Description
A solution to The Dining Philosophers problem, serving as an introduction to multithreading. This 42 Network/Codam verson adds some extra constraints to the problem:
- philosophers are not allowed to communicate with each other.
- philosophers don't know when someone is about to die.
- the death timer is reset at the start of the eating phase.
- when philosophers change state, an update with the current time in ms is outputted and lines may not be scrambled between philosophers.
- there cannot be more than 10ms delay between a philosophers death and their death message.

# Usage
#### build
Run ```make``` in the project's root directory.

#### run
The program expects the following CLI arguments:

1. **number_of_philosophers**
2. **time_to_die**
3. **time_to_eat**
4. **time_to_sleep**
5. **number_of_times_each_philosopher_must_eat** (optional)

#### example
```./philo 10 200 80 80 7```

