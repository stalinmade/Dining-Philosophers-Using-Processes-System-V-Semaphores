# Dining Philosophers Using Processes & System V Semaphores

## Objective

Implement the classic **Dining Philosophers Problem** using Linux processes and **System V semaphores** to demonstrate process synchronization, shared resource management, and deadlock avoidance.

## Problem Description

The Dining Philosophers problem consists of:

- 5 philosophers
- 5 forks
- Each philosopher runs as a separate process using `fork()`
- Each fork is represented by a System V semaphore
- A philosopher must acquire two forks before eating
- Forks must be released after eating
- Deadlock must be avoided through proper resource acquisition

## Implementation

The project uses:

- `fork()` to create five philosopher processes
- `semget()` to create a System V semaphore set containing five semaphores
- `semctl()` to initialize and manage semaphore values
- `semop()` to acquire and release forks
- `wait()` for parent-child process synchronization
- `sleep()` to simulate thinking/eating
- `IPC_RMID` to remove the semaphore set after execution

### Semaphore Representation

```text
Semaphore value 1 → Fork available
Semaphore value 0 → Fork occupied
```

Each philosopher uses two adjacent forks:

```text
Philosopher 1 → Fork 0 + Fork 1
Philosopher 2 → Fork 1 + Fork 2
Philosopher 3 → Fork 2 + Fork 3
Philosopher 4 → Fork 3 + Fork 4
Philosopher 5 → Fork 4 + Fork 0
```

## Synchronization

Fork acquisition is performed using `semop()`:

```c
sem_op = -1;
```

This decreases the semaphore value and blocks the process when the required fork is unavailable.

After eating, the philosopher releases the forks using:

```c
sem_op = +1;
```

Both forks are acquired in a single `semop()` operation so that a philosopher does not hold one fork while waiting indefinitely for the second fork.

## Process Flow

```text
Think
  ↓
Hungry
  ↓
Acquire two forks
  ↓
Eat
  ↓
Release two forks
  ↓
Think again
```

## Deadlock Demonstration

A deadlock scenario can occur if every philosopher acquires one fork first and then waits for the second fork:

```text
P1 holds F0 → waits for F1
P2 holds F1 → waits for F2
P3 holds F2 → waits for F3
P4 holds F3 → waits for F4
P5 holds F4 → waits for F0
```

This creates a circular wait.

The implementation avoids this hold-and-wait situation by acquiring both required forks together using a single `semop()` call.

## System Calls / APIs Used

| API | Purpose |
|---|---|
| `fork()` | Create philosopher processes |
| `wait()` | Parent waits for child processes |
| `semget()` | Create/access semaphore set |
| `semctl()` | Initialize/manage semaphores |
| `semop()` | Acquire/release forks |
| `sleep()` | Simulate thinking/eating |
| `exit()` | Terminate child process |

## Learning Outcomes

- Linux process creation using `fork()`
- System V IPC
- Semaphore-based synchronization
- Critical section protection
- Shared resource management
- Race condition prevention
- Deadlock concepts and avoidance
- Parent-child process synchronization

## Build and Run

```bash
gcc dining.c -o dining
./dining
```

## Sample Output

```text
Philosopher 1 executing: 27516
Philosopher 3 executing: 27518
Philosopher 1 done: 27516
Philosopher 3 done: 27518
Philosopher 5 executing: 27520
Philosopher 2 executing: 27517
Philosopher 5 done: 27520
Philosopher 2 done: 27517
Philosopher 4 executing: 27519
Philosopher 4 done: 27519
```

The output demonstrates that philosophers sharing a common fork do not enter the eating section simultaneously.

## Concepts Demonstrated

**Processes → IPC → System V Semaphores → Synchronization → Deadlock Avoidance**

This project was developed as part of Linux System Programming practice to understand process synchronization and System V IPC mechanisms.
