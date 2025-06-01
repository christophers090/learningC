#include "Task.h"    // Include the header file for the class definition
#include <sstream>   // Needed for string manipulation in serialize/deserialize
#include <vector>    // Needed for splitting string in deserialize
#include <stdexcept> // For error handling

// ** EDUCATIONAL NOTE: Implementation File (.cpp) **
// We separate the definition (in .h) from the implementation (in .cpp).
// This improves organization and compilation times in larger projects.
// Arduino often puts everything in one .ino file, which is simpler but less scalable.
// The 'Task::' prefix tells the compiler that these functions belong to the Task class.

// Initialize the static member variable outside the class definition
int Task::nextID = 1; // Start IDs from 1

// Constructor implementation - uses initializer list
Task::Task(const std::string &desc, int priority)
    : description(desc),
      taskPriority(priority),
      completed(false),
      taskID(nextID++) // Initialize const member using nextID, then increment nextID
{
    // ** EDUCATIONAL NOTE: Initializer List **
    // ': description(desc), ...' is an initializer list. It's the preferred
    // way to initialize member variables in C++ constructors. More efficient than
    // assigning inside the {} braces for many types.
    // It is the ONLY way to initialize const members and reference members.
    // Body intentionally empty
}

// Marks the task as completed
void Task::markComplete()
{
    completed = true;
}

// Prints task details to standard output
void Task::display() const
{
    // ** EDUCATIONAL NOTE: std::cout **
    // This is the standard C++ way to print to the console.
    // Equivalent to Arduino's Serial.print() or Serial.println().
    // 'std::' specifies the namespace where cout is defined.
    // '<<' is the stream insertion operator.
    // '\n' is a newline character (like println).
    // Display the ID as well
    std::cout << "ID: " << taskID << " " // Added ID display
              << "[" << (completed ? "X" : " ") << "] "
              << "P" << taskPriority << ": "
              << description << std::endl; // std::endl flushes the output buffer too
}

// Getter for description
std::string Task::getDescription() const
{
    return description;
}

// Getter for priority
int Task::getPriority() const
{
    return taskPriority;
}

// Getter for completion status
bool Task::isComplete() const
{
    return completed;
}

// Getter for the constant task ID
int Task::getID() const
{
    return taskID;
}

// setter for task
void Task::setTaskDescription(const std::string &desc)
{
    description = desc;
}

void Task::setTaskPriority(int prio)
{
    taskPriority = prio;
}

// Converts Task object to a string for saving (Format: completed|priority|description)
// Newlines in description are escaped as "\\n"
// NOTE: The taskID is NOT included in this serialized string currently.
std::string Task::serialize() const
{
    // ** EDUCATIONAL NOTE: std::ostringstream **
    // A string stream allows you to build a string using stream insertion operators (<<),
    // similar to how you use std::cout. Useful for formatting data.
    std::ostringstream oss;
    std::string safe_desc = description;

    // Escape newlines
    size_t pos = safe_desc.find('\n');
    while (pos != std::string::npos)
    {
        safe_desc.replace(pos, 1, "\\n");
        pos = safe_desc.find('\n', pos + 2);
    }

    oss << (completed ? '1' : '0') << '|' << taskPriority << '|' << safe_desc;
    return oss.str(); // Get the resulting string from the stream
}

// Creates Task object from a serialized string
// Expects format: completed|priority|description (newlines escaped as "\\n")
Task Task::deserialize(const std::string &data)
{
    // ** EDUCATIONAL NOTE: std::istringstream and std::getline **
    // istringstream lets you read from a string as if it were a stream (like cin or a file).
    // std::getline reads until a delimiter character is found.
    std::istringstream iss(data);
    std::string segment;
    std::vector<std::string> parts;

    // Split string by delimiter '|'
    while (std::getline(iss, segment, '|'))
    {
        parts.push_back(segment);
    }

    if (parts.size() != 3)
    {
        // ** EDUCATIONAL NOTE: Error Handling (Exceptions) **
        // Standard C++ often uses exceptions for error handling, unlike Arduino's
        // typical return codes or simple checks. std::runtime_error is a standard exception type.
        // We'll see how to CATCH this later in Storage.cpp or main.cpp.
        throw std::runtime_error("Invalid task data format for deserialization: " + data);
    }

    bool completed = (parts[0] == "1");
    int priority = 0;
    std::string description = parts[2];

    // ** EDUCATIONAL NOTE: std::stoi **
    // Converts a string (std::string) to an integer. Standard C++ library function.
    // Throws an exception if conversion fails.
    // Convert priority string to integer
    try
    {
        priority = std::stoi(parts[1]);
    }
    catch (const std::invalid_argument &e)
    {
        throw std::runtime_error("Invalid priority value in task data: " + parts[1]);
    }
    catch (const std::out_of_range &e)
    {
        throw std::runtime_error("Priority value out of range in task data: " + parts[1]);
    }

    // Restore escaped newline characters
    size_t pos = description.find("\\n");
    while (pos != std::string::npos)
    {
        description.replace(pos, 2, "\n");
        pos = description.find("\\n", pos + 1);
    }

    // Create and return the Task object
    Task task(description, priority);
    if (completed)
    {
        task.markComplete();
    }
    return task;
}