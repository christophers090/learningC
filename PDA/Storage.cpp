#include "Storage.h"
#include <fstream>   // Standard C++ library for file input/output streams
#include <iostream>  // For error messages
#include <stdexcept> // For exception handling during deserialization

// Constructor: Stores file paths
Storage::Storage(const std::string &taskFile, const std::string &noteFile)
    : taskFilename(taskFile), noteFilename(noteFile) {}

// Saves Tasks to the specified file.
// Overwrites the file if it exists.
bool Storage::saveTasks(const std::vector<Task> &tasks) const
{
    // Open file stream for output (RAII ensures file closure)
    std::ofstream outFile(taskFilename);

    if (!outFile.is_open())
    { // Check if the file opened successfully
        std::cerr << "Error: Could not open task file for writing: " << taskFilename << std::endl;
        return false;
    }

    // Write each task's serialized representation to a new line
    for (const auto &task : tasks)
    {
        outFile << task.serialize() << std::endl;
    }

    return true; // outFile closed automatically by RAII
}

// Loads Tasks from the specified file.
// Returns an empty vector if the file cannot be opened or is empty.
std::vector<Task> Storage::loadTasks() const
{
    std::vector<Task> loadedTasks;
    // Open file stream for input (RAII ensures file closure)
    std::ifstream inFile(taskFilename);

    if (!inFile.is_open())
    {
        // File not existing on first run is not an error, return empty vector
        return loadedTasks;
    }

    std::string line;
    // Read file line by line
    while (std::getline(inFile, line))
    {
        if (!line.empty()) // Avoid processing blank lines
        {
            try
            {
                // Attempt to deserialize line and add to vector
                loadedTasks.push_back(Task::deserialize(line));
            }
            catch (const std::runtime_error &e)
            {
                // Log error and skip corrupted line
                std::cerr << "Error loading task: " << e.what() << " (Skipping line: '" << line << "')" << std::endl;
            }
        }
    }

    return loadedTasks; // inFile closed automatically by RAII
}

// Saves Notes to the specified file.
// Overwrites the file if it exists.
bool Storage::saveNotes(const std::vector<Note> &notes) const
{
    std::ofstream outFile(noteFilename);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open note file for writing: " << noteFilename << std::endl;
        return false;
    }
    for (const auto &note : notes)
    {
        outFile << note.serialize() << std::endl;
    }
    return true;
}

// Loads Notes from the specified file.
// Returns an empty vector if the file cannot be opened or is empty.
std::vector<Note> Storage::loadNotes() const
{
    std::vector<Note> loadedNotes;
    std::ifstream inFile(noteFilename);
    if (!inFile.is_open())
    {
        return loadedNotes;
    }
    std::string line;
    while (std::getline(inFile, line))
    {
        if (!line.empty())
        {
            try
            {
                loadedNotes.push_back(Note::deserialize(line));
            }
            catch (const std::runtime_error &e)
            {
                // Log error and skip corrupted line
                std::cerr << "Error loading note: " << e.what() << " (Skipping line: '" << line << "')" << std::endl;
            }
        }
    }
    return loadedNotes;
}