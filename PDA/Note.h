#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <iostream>

// Represents a simple text note with a title and content.
class Note
{
public:
    // Constructor
    Note(const std::string &title, const std::string &content);

    // Member functions
    void display() const; // Prints note details to standard output
    std::string getTitle() const;
    std::string getContent() const;

    // Serialization/Deserialization
    // Returns string representation for file storage (Format: title|content)
    std::string serialize() const;
    // Creates a Note object from a serialized string representation
    static Note deserialize(const std::string &data);

private:
    std::string noteTitle;
    std::string noteContent;
};

#endif // NOTE_H