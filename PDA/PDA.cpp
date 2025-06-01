#include "PDA.h"
#include <iostream>
#include <limits> // Required for numeric_limits in main, but good practice to include where used if separating further

// Constructor: Initializes storage member and loads initial data.
PDA::PDA(const std::string &taskFile, const std::string &noteFile)
    : dataStorage(taskFile, noteFile) // Initialize Storage member via initializer list
{
    loadData(); // Load data from files immediately upon creation
}

// --- Task Management --- //

// Adds a new task to the internal vector.
void PDA::addTask(const std::string &description, int priority)
{
    tasks.push_back(Task(description, priority));
    std::cout << "Task added.\n";
}

void PDA::editTask(const std::string &description, int priority, int index)
{
    if (index > 0 && index <= tasks.size())
    {
        tasks[index - 1].setTaskDescription(description);
        tasks[index - 1].setTaskPriority(priority);
        std::cout << "Task edited.\n";
    }
    else
    {
        std::cerr << "Error: Invalid task number." << std::endl;
    }
}

// Lists all current tasks to the console.
void PDA::listTasks() const
{
    std::cout << "\n--- TASKS ---" << std::endl;
    if (tasks.empty())
    {
        std::cout << "No tasks to display." << std::endl;
    }
    else
    {
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            std::cout << i + 1 << ". ";
            tasks[i].display();
        }
    }
    std::cout << "-------------" << std::endl;
}

void PDA::listTasksByIndices(const std::vector<int> &indices) const
{
    std::cout << "\n--- Matching Tasks ---" << std::endl;
    if (indices.empty())
    {
        std::cout << "No matching tasks found." << std::endl;
    }
    else
    {
        for (int index : indices)
        {
            if (index >= 0 && index < tasks.size())
            {
                std::cout << index + 1 << ". ";
                tasks[index].display();
            }
            else
            {
                std::cerr << "Warning: Invalid index encountered: " << index << std::endl;
            }
        }
    }
    std::cout << "--------------------" << std::endl;
}

// Marks a task as complete based on its 1-based index.
void PDA::markTaskComplete(size_t index)
{
    // Validate 1-based index against 0-based vector size
    if (index > 0 && index <= tasks.size())
    {
        tasks[index - 1].markComplete(); // Adjust index for 0-based access
        std::cout << "Task marked as complete.\n";
    }
    else
    {
        std::cerr << "Error: Invalid task number." << std::endl;
    }
}

// Removes a task based on its 1-based index.
void PDA::removeTask(size_t index)
{
    if (index > 0 && index <= tasks.size())
    {
        // vector::erase takes an iterator; begin() + offset gives the correct iterator
        tasks.erase(tasks.begin() + (index - 1));
        std::cout << "Task removed.\n";
    }
    else
    {
        std::cerr << "Error: Invalid task number." << std::endl;
    }
}

// --- Note Management --- //

// Adds a new note to the internal vector.
void PDA::addNote(const std::string &title, const std::string &content)
{
    notes.push_back(Note(title, content));
    std::cout << "Note added.\n";
}

// Lists the titles of all current notes to the console.
void PDA::listNotes() const
{
    std::cout << "\n--- NOTES ---" << std::endl;
    if (notes.empty())
    {
        std::cout << "No notes to display." << std::endl;
    }
    else
    {
        // Display with 1-based indexing for the user
        for (size_t i = 0; i < notes.size(); ++i)
        {
            std::cout << i + 1 << ". " << notes[i].getTitle() << std::endl;
        }
    }
    std::cout << "-------------" << std::endl;
}

// Displays the full content of a note based on its 1-based index.
void PDA::viewNote(size_t index) const
{
    if (index > 0 && index <= notes.size())
    {
        notes[index - 1].display(); // Adjust index for 0-based access
    }
    else
    {
        std::cerr << "Error: Invalid note number." << std::endl;
    }
}

// Removes a note based on its 1-based index.
void PDA::removeNote(size_t index)
{
    if (index > 0 && index <= notes.size())
    {
        notes.erase(notes.begin() + (index - 1));
        std::cout << "Note removed.\n";
    }
    else
    {
        std::cerr << "Error: Invalid note number." << std::endl;
    }
}

void PDA::searchTasks(const std::string &keyWord) const
{
    std::vector<int> tasksWithKeyWord;
    if (tasks.empty())
    {
        // Output handled by listTasksByIndices below
    }
    else
    {
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            std::string description = tasks[i].getDescription();
            size_t location = description.find(keyWord);
            if (location != std::string::npos)
            {
                tasksWithKeyWord.push_back(i);
            }
        }
    }

    listTasksByIndices(tasksWithKeyWord);
}

// --- Data Persistence --- //

// Loads tasks and notes from files using the Storage object.
// Called by the constructor.
void PDA::loadData()
{
    tasks = dataStorage.loadTasks();
    notes = dataStorage.loadNotes();
    // Optional: Provide feedback on loaded data count
    // std::cout << "Data loaded. " << tasks.size() << " tasks, " << notes.size() << " notes.\n";
}

// Saves current tasks and notes to files using the Storage object.
bool PDA::saveData()
{
    bool tasksSaved = dataStorage.saveTasks(tasks);
    bool notesSaved = dataStorage.saveNotes(notes);
    if (tasksSaved && notesSaved)
    {
        std::cout << "Data saved successfully.\n";
        return true;
    }
    else
    {
        // Error messages should be printed by Storage class
        std::cerr << "Error: Failed to save all data.\n";
        return false;
    }
}