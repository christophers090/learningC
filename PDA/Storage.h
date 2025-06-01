#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include "Task.h"
#include "Note.h"

// Handles loading and saving Task and Note data to/from files.
class Storage
{
public:
    // Constructor - specifies the files to use for tasks and notes.
    Storage(const std::string &taskFile, const std::string &noteFile);

    // Saves the provided vector of Tasks to the task file.
    // Returns true on success, false on failure.
    bool saveTasks(const std::vector<Task> &tasks) const;

    // Loads Tasks from the task file.
    // Returns a vector of Tasks (empty if file not found or empty).
    std::vector<Task> loadTasks() const;

    // Saves the provided vector of Notes to the note file.
    // Returns true on success, false on failure.
    bool saveNotes(const std::vector<Note> &notes) const;

    // Loads Notes from the note file.
    // Returns a vector of Notes (empty if file not found or empty).
    std::vector<Note> loadNotes() const;

private:
    // File paths
    std::string taskFilename;
    std::string noteFilename;
};

#endif // STORAGE_H