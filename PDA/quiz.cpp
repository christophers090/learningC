#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits> // For std::cin.ignore

// C++ Concepts Quiz
// Instructions: Answer each question directly in this file.
// For comment-based questions, write your answer below the comment.
// For code-based questions, fill in the blanks or add comments as needed.

// --- Questions ---

// 1. What is the primary purpose of placing function declarations (like `void displayMenu();`)
//    near the top of `main.cpp`, before the `main` function itself?
// ANSWER:
// it initializes the functions telling C++ compiler what to expect. (not sure exactly if this is right, why would it fail if there arent these .h or the declerations before the file?)

// 2. Explain the difference between where a function is *declared* (prototype)
//    and where it is *defined* (implementation).
// ANSWER: Decleration often happens in the .h files the implementation is in the .cpp files. decleration just tells you what inputs and outputs there are not how it actually works

// 3. When the C++ preprocessor encounters a line like `#include "Task.h"`,
//    what does it effectively do with the contents of `Task.h`?
// ANSWER: it takes the contents and pastes them into the cpp file that has the include. it also pastes in any other included .h files in the .h file its self. like PDA.h has other .h files that will also get pasted into the pda.cpp file

// 4. What is the role of the C++ *linker* in the overall process of creating
//    an executable program from multiple `.cpp` files?
// ANSWER: (i think) it is what takes all the compiled .o machine code fieles and combines them into one program (lets go over the process again, just give a short overview below)

// 5. Why does the `getIntInput` function (which reads an integer) require
//    error-checking logic involving `std::cin.fail()` and `std::cin.clear()`,
//    while the simpler `getStringInput` function using `std::getline` generally does not?
// ANSWER: any input to the terminal will be hadled as a string and passed to the getLine fuction. the getInt needs to check if we actually put in an integer, if we didnt we need to remove whatever bac charictor exists in the input buffer

// 6. If you have a class `MyData` with a member variable `int count;` and you forget
//    to initialize it in the constructor (either in the initializer list or body),
//    what is the state of the `count` variable? Is it zero?
// ANSWER: not zero, its whatever was in that position in memory at compile time, garbage

// 7. What does the `const` keyword signify when placed *after* the closing parenthesis
//    of a member function declaration (e.g., `std::string getDescription() const;`)?
// ANSWER: that funciton is not going to edit any of the member variabes of the function

// 8. In the context of Object-Oriented Programming, what is **encapsulation**,
//    and give one reason why using private member variables with public getter functions
//    is often preferred over making member variables public.
// ANSWER: its where you seperate the data from the getter functions. you do this so that getters/setters can perform opperations on the underlying data. if you change the underlying data type you dont need to change all the class.var things you just change the getter/setter once in the class

// 9. Consider the `Task` class from our discussion. Explain the fundamental difference
//    between the `static int nextID;` member and the non-static `std::string description;` member
//    in terms of how many copies exist and what they belong to.
// ANSWER: one coppy of nextID exists for all classes a coppy of description exists for each task class enstantiated

// 10. Why is it mandatory to initialize `const` member variables (like `Task::taskID`)
//     within the constructor's **initializer list**?
// ANSWER: we need to update the next id, we need to set it to next id + 1, if not all classes would have the same ID (i might be missing part of the anser here tho)

// 11. Write the basic syntax for the constructor initializer list for the `Product` class below.
class Product
{
private:
    std::string name_;
    double price_;

public:
    Product(const std::string &name, double price)
        // ANSWER: Fill in the initializer list syntax here:
        : name_(name),
          price_(price)
    {
        // Constructor body (can be empty)
    }
};
// not sure if i got that right, what are the underscores and how do i handle the fact that the name input is a pointer

// 12. What is the *only* technical difference in C++ between defining a type
//     using the `struct` keyword versus the `class` keyword?
// ANSWER: public vs private default. class is private default.

// 13. Identify the potential issue in the `printValue` function when interacting with the
//     `ValueHolder` class as shown below. How would you fix the `getValue` function in the class?
#include <iostream>
class ValueHolder
{
private:
    int value;

public:
    ValueHolder(int v) : value(v) {}

    int getValue() const;

    // Potential issue here in the context of printValue:
    int getValue()
    {
        return value;
    }
    // ANSWER: How should getValue() be declared to fix the issue for printValue?
    //         Write the corrected declaration below (or modify the one above):
    // int getValue() { if (!value) return -1; return value; } maybe something like this where it checks to see if value is an integer and not garbage?
};

void printValue(const ValueHolder &holder)
{
    // This line might cause a compile error depending on the fix for getValue:
    std::cout << holder.getValue() << std::endl;
}
// ANSWER: Explain the issue briefly: i actually dont know here. is it because its an integer and not a string? i thought cout is ok with that

// 14. After successfully reading an integer using `std::cin >> some_int;`, why is it often
//     necessary to use `std::cin.ignore(...)` afterwards, especially before trying to read
//     a string using `std::getline`?
// ANSWER: not sure, please explain

// 15. What is the primary purpose of using `std::ostringstream`?
//     (Hint: Recall its use in `Task::serialize`).
// ANSWER: not sure

// 16. Can a `static` member function (like `Task::deserialize`) directly access or modify
//     a non-static member variable (like `description` or `taskID`) of the `Task` class
//     without being given a specific `Task` object? Explain briefly why or why not.
// ANSWER:  no, it only opperates on things that are general to all task clases like nextID

// 17. Why does it make sense for a function like `Task::deserialize`, whose job is to
//     create a `Task` object from a string, to be declared as `static`?
// ANSWER: there is not task instantiated yet, its job is to create one, its not operating on any specific task

// 18. Give one specific advantage (related to control or flexibility) of having
//     a private member `bool completed;` and a public member function `void markComplete();`
//     instead of just making `completed` public.
// ANSWER: if you wanted to change complete to an int to allow for percentage completeness you would have to change your whole codebase if it was all coded with task.complete = true. but this way we just change the set and get fucntiosn and add a setPercentage fucntion

// 19. What happens to the `std::string noteTitle;` member variable if this `Note` constructor is called?
//     Is it initialized? If so, to what?
class Note
{
private:
    std::string noteTitle;
    std::string noteContent;

public:
    Note(const std::string &content)
        : noteContent(content) // Only noteContent is in the initializer list
    {
        // Constructor body
    }
    // Assume other necessary parts of the class exist (like include guards, etc.)
};
// ANSWER: Its a string, so for this case its set as the empty string, if it were a bool, float, int, ect it would be garbage

// --- End of Quiz ---
// Save this file with your answers and let me know when you're ready for grading!

//  Ok give feedback, expand on my answers if nessisairy. give me a grade