#ifndef PDA_H
#define PDA_H

#include <vector>
#include <string>
#include "Task.h"
#include "Note.h"
#include "Storage.h" // PDA uses Storage

// Main application class coordinating tasks, notes, and storage.
class PDA
{
public:
    // Constructor - Initializes storage and loads data from default or specified files.
    PDA(const std::string &taskFile = "tasks.txt", const std::string &noteFile = "notes.txt");

    // Task Management
    void addTask(const std::string &description, int priority);
    void listTasks() const;
    void listTasksByIndices(const std::vector<int> &indices) const;
    void markTaskComplete(size_t index); // index is 1-based for user input
    void removeTask(size_t index);       // index is 1-based
    void editTask(const std::string &description, int priority, int index);

    // Note Management
    void addNote(const std::string &title, const std::string &content);
    void listNotes() const;
    void viewNote(size_t index) const; // index is 1-based
    void removeNote(size_t index);     // index is 1-based

    void searchTasks(const std::string &keyWord) const;

    // Explicitly saves current tasks and notes to files via Storage object.
    // Returns true on success, false otherwise.
    bool saveData();

private:
    // ** EDUCATIONAL NOTE: Composition **
    // The PDA class *has a* Storage object. This is called Composition.
    // It allows PDA to delegate file operations to the Storage class.
    Storage dataStorage;

    std::vector<Task> tasks;
    std::vector<Note> notes;

    // Helper to load data during construction
    void loadData();
};

#endif // PDA_H