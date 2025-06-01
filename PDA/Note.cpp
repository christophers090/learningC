#include "Note.h"
#include <sstream>
#include <vector>
#include <stdexcept> // For error handling

// Constructor - uses initializer list
Note::Note(const std::string &title, const std::string &content)
    : noteTitle(title), noteContent(content) {}

// Prints note details to standard output
void Note::display() const
{
    std::cout << "--- NOTE: " << noteTitle << " ---" << std::endl;
    std::cout << noteContent << std::endl;
    std::cout << "--------------------" << std::endl;
}

// Getter for title
std::string Note::getTitle() const
{
    return noteTitle;
}

// Getter for content
std::string Note::getContent() const
{
    return noteContent;
}

// Helper function (file scope) to replace all occurrences of a substring
// Needed for safely serializing strings containing delimiters or newlines.
std::string replaceAll(std::string str, const std::string &from, const std::string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Move past the replaced substring
    }
    return str;
}

// Serializes Note to string (Format: title|content)
// Escapes special characters ('|', '\n') in title and content.
std::string Note::serialize() const
{
    std::ostringstream oss;

    // Escape delimiters and newlines before saving
    std::string safe_title = replaceAll(noteTitle, "|", "\\|");
    safe_title = replaceAll(safe_title, "\n", "\\n");

    std::string safe_content = replaceAll(noteContent, "|", "\\|");
    safe_content = replaceAll(safe_content, "\n", "\\n");

    oss << safe_title << '|' << safe_content;
    return oss.str();
}

// Deserializes string data into a Note object.
// Expects format: title|content (special characters escaped)
Note Note::deserialize(const std::string &data)
{
    // Find the first delimiter ONLY, as content might contain original '|'
    std::size_t first_delimiter = data.find('|');
    if (first_delimiter == std::string::npos)
    {
        throw std::runtime_error("Invalid note data format (missing delimiter): " + data);
    }

    std::string title_part = data.substr(0, first_delimiter);
    std::string content_part = data.substr(first_delimiter + 1);

    // Restore escaped delimiters and newlines
    std::string title = replaceAll(title_part, "\\|", "|");
    title = replaceAll(title, "\\n", "\n");

    std::string content = replaceAll(content_part, "\\|", "|");
    content = replaceAll(content, "\\n", "\n");

    // Create and return the Note object
    return Note(title, content);
}