#ifndef TASK_H
#define TASK_H

#include <string>   // Standard C++ string library
#include <iostream> // For potential debugging output (optional here)

// Represents a single task with description, priority, and completion status.
class Task
{
public:
    // Constructor
    Task(const std::string &desc, int priority = 0);

    // Member Functions
    void markComplete();
    void display() const; // Prints task details to standard output

    // Getters
    std::string getDescription() const;
    int getPriority() const;
    bool isComplete() const;
    int getID() const; // Getter for the constant task ID

    // Editors
    void setTaskDescription(const std::string &desc);
    void setTaskPriority(int prio);

    // Returns a string representation for file storage (Format: completed|priority|description)
    std::string serialize() const;
    // Creates a Task object from a serialized string representation
    static Task deserialize(const std::string &data);

private:
    // ** EDUCATIONAL NOTE: Member Variables (Attributes) **
    // Data stored within each Task object. These are private for encapsulation.
    std::string description;
    int taskPriority;
    bool completed;
    const int taskID; // <<< Added: Constant ID for this task

    // Static member to ensure unique IDs
    static int nextID; // <<< Added: Counter shared by all Task objects
};

#endif // TASK_H