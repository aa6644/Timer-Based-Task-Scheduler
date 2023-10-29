#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Maximum number of tasks
#define MAX_TASKS 10

// Structure to represent a task
typedef struct {
    void (*function)(void);
    int interval;
    int active;
    int counter;
} Task;

// Array to store tasks
Task tasks[MAX_TASKS];

// Function to be executed as a task
void task1() {
    printf("Task 1 executed!\n");
}

void task2() {
    printf("Task 2 executed!\n");
}

// Function to manage tasks
void manage_tasks() {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].active) {
            tasks[i].counter--;
            if (tasks[i].counter <= 0) {
                tasks[i].function();
                tasks[i].counter = tasks[i].interval;
            }
        }
    }
}

// Add a new task to the task list
int add_task(void (*function)(void), int interval) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (!tasks[i].active) {
            tasks[i].function = function;
            tasks[i].interval = interval;
            tasks[i].active = 1;
            tasks[i].counter = interval;
            return i;
        }
    }
    return -1; // Task list is full
}

// Remove a task from the task list
void remove_task(int task_id) {
    if (task_id >= 0 && task_id < MAX_TASKS) {
        tasks[task_id].active = 0;
    }
}

int main() {
    int interval = 1; // Interval in seconds

    // Initialize task list
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].active = 0;
    }

    // Add tasks to the task list
    int task1_id = add_task(task1, 3);
    int task2_id = add_task(task2, 5);

    // Run an infinite loop to keep the program running
    while (1) {
        manage_tasks(); // Execute tasks
        usleep(interval * 1000000); // Sleep in microseconds
    }

    // Optionally, remove tasks
    remove_task(task1_id);
    remove_task(task2_id);

    return 0;
}
