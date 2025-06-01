#include <iostream> // For console input/output (cin, cout)
#include <string>   // For using std::string
#include <limits>   // For clearing input buffer (numeric_limits)
#include <vector>   // Although not directly used here, often needed in main
#include "PDA.h"    // Include our main PDA logic class

// Forward declarations for helper functions
void displayMenu();
int getIntInput(const std::string &prompt);
std::string getStringInput(const std::string &prompt);

// ** EDUCATIONAL NOTE: `main` Function **
// This is the entry point for *every* standard C++ program.
// Execution begins here. It's equivalent to Arduino's setup() running once,
// followed by the logic you'd put inside loop() running within a loop here.
// It returns an integer: 0 usually indicates success, non-zero indicates an error.
// `int argc, char* argv[]` are parameters for command-line arguments (optional here).

// Main application entry point
int main()
{
    // ** EDUCATIONAL NOTE: Object Creation **
    // We create an instance of our PDA class on the stack.
    // Its constructor (PDA::PDA) is called automatically, which loads the data.
    PDA myPDA("my_tasks.dat", "my_notes.dat"); // Use different filenames

    int choice;
    // Main application loop
    do
    {
        displayMenu();
        choice = getIntInput(""); // Get validated integer choice

        switch (choice)
        {
        case 1: // Add Task
        {
            std::string desc = getStringInput("Enter task description: ");
            int priority = getIntInput("Enter priority (e.g., 1-5): ");
            myPDA.addTask(desc, priority);
            break;
        }
        case 2: // List Tasks
            myPDA.listTasks();
            break;
        case 3: // Mark Task Complete
        {
            myPDA.listTasks(); // Show tasks to help user choose
            int index = getIntInput("Enter task number to mark complete: ");
            myPDA.markTaskComplete(index);
            break;
        }
        case 4: // Remove Task
        {
            myPDA.listTasks();
            int index = getIntInput("Enter task number to remove: ");
            myPDA.removeTask(index);
            break;
        }
        case 5: // Add Note
        {
            std::string title = getStringInput("Enter note title: ");
            // Note: Currently reads only a single line for content
            std::string content = getStringInput("Enter note content: ");
            myPDA.addNote(title, content);
            break;
        }
        case 6: // List Notes
            myPDA.listNotes();
            break;
        case 7: // View Note
        {
            myPDA.listNotes();
            int index = getIntInput("Enter note number to view: ");
            myPDA.viewNote(index);
            break;
        }
        case 8: // Remove Note
        {
            myPDA.listNotes();
            int index = getIntInput("Enter note number to remove: ");
            myPDA.removeNote(index);
            break;
        }
        case 9: // Save Data
            myPDA.saveData();
            break;
        case 10:
        {
            myPDA.listTasks();
            int index = getIntInput("Enter task number to to edit: ");
            std::string desce = getStringInput("Enter new task description: ");
            int prioritye = getIntInput("Enter new priority (e.g., 1-5): ");
            myPDA.editTask(desce, prioritye, index);
            break;
        }
        case 11:
        {
            std::string keyWord = getStringInput("Enter a key word to search for");
            myPDA.searchTasks(keyWord);
            break;
        }
        case 0: // Exit
            std::cout << "Saving data before exiting...\n";
            myPDA.saveData(); // Attempt to save data on exit
            std::cout << "Exiting PDA. Goodbye!\n";
            break;
        default:
            std::cerr << "Invalid choice. Please try again.\n";
        }

        // ** EDUCATIONAL NOTE: Program Loop **
        // This `do-while` loop serves a similar purpose to Arduino's `loop()`,
        // repeatedly executing the menu and user actions until the user chooses to exit.
        // However, it's explicitly controlled within the `main` function.
    } while (choice != 0);

    // ** EDUCATIONAL NOTE: Return Value **
    // Returning 0 from main indicates successful program execution.
    return 0;
} // The myPDA object goes out of scope here, and its destructor would be called if it had one.

// Displays the main menu options to the console.
void displayMenu()
{
    std::cout << "\n===== Personal Digital Assistant =====\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. List Tasks\n";
    std::cout << "3. Mark Task Complete\n";
    std::cout << "4. Remove Task\n";
    std::cout << "5. Add Note\n";
    std::cout << "6. List Notes\n";
    std::cout << "7. View Note\n";
    std::cout << "8. Remove Note\n";
    std::cout << "9. Save Data\n";
    std::cout << "10. Edit Task\n";
    std::cout << "0. Exit\n";
    std::cout << "====================================\n";
    std::cout << "Enter your choice: ";
}

// Prompts the user and reads an integer input from the console.
// Handles non-integer input errors and reprompts.
int getIntInput(const std::string &prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value; // Attempt to read integer

        if (std::cin.fail()) // Check for input failure
        {
            std::cerr << "Invalid input. Please enter a number.\n";
            std::cin.clear();                                                   // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input line
        }
        else
        {
            // Discard the rest of the line (e.g., the newline after the number)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value; // Return the valid integer
        }
    }
}

// Prompts the user and reads a full line of string input from the console.
std::string getStringInput(const std::string &prompt)
{
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value); // Read entire line, including spaces
    return value;
}