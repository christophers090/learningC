#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <optional>
#include <limits>
#include <cstddef> // For size_t

// --- C++ & Game Dev Concepts Quiz ---

// --- Inheritance & OOP ---

// 1. We created a GameObject base class for Item and Room.
//    What is the primary benefit of using inheritance here?
// ANSWER: I dont have to type out the methods and values shared by all game classes
// FEEDBACK: Correct. The main benefit is code reuse (avoiding duplication of common members like name, description, getName(), getDescription()) and establishing an "is-a" relationship (an Item is-a GameObject), which can be useful for polymorphism later.

// 2. When inheriting one class from another (e.g., class Derived : Base),
//    what is the difference between using `public Base` and just `Base` (or `private Base`)?
// ANSWER: base will put both the public and private methods and values in private of Derived. Public Base will put the public methods in public of Derived
// FEEDBACK: Correct. `public Base` (public inheritance) means public members of Base stay public in Derived, protected members of Base stay protected in Derived. `private Base` (or the default for `class`) means public and protected members of Base become private in Derived.

// 3. Why is it important to declare a `virtual` destructor in a base class
//    like GameObject, especially if you might delete derived objects through base class pointers?
// ANSWER: I have no idea, what is virtual and what do you mean my delete derived objected through vlse class pointers? give an example
// FEEDBACK: Okay, this is important for polymorphism. Imagine:
//    GameObject* ptr = new Item("Key", "Opens doors"); // Pointer to base, points to derived object
//    // ... later ...
//    delete ptr; // Delete through base class pointer
//    If ~GameObject() is NOT virtual, ONLY the GameObject destructor runs. The Item part of the object might not be cleaned up properly (e.g., if Item allocated memory).
//    If ~GameObject() IS virtual, the program knows to check the actual type of the object ptr points to at runtime. It calls the ~Item() destructor first, then the ~GameObject() destructor, ensuring proper cleanup.
//    So, `virtual` destructors ensure the correct derived class destructor is called when deleting via a base class pointer, preventing resource leaks.

// 4. In the Item constructor `Item::Item(...) : GameObject(name, desc) {}`,
//    what is the purpose of the `: GameObject(name, desc)` part?
// ANSWER:GameObject() is the constructor for the base game object class. it is like doing name(name) description(description) for a non derived class but in this case you send name and desc to the constructior of GameObj
// Is that right? how does it work exactly?
// FEEDBACK: Exactly right! When a derived object (Item) is created, the base class part (GameObject) must be constructed first. The syntax `: GameObject(name, desc)` in the derived constructor's initializer list explicitly calls the appropriate constructor of the base class (GameObject), passing the necessary arguments (`name`, `desc`) up to it to initialize the inherited `name` and `description` members.

// 5. What does the `protected` access specifier mean? How does it differ from `private`?
// ANSWER: No idea, what is prtected?
// FEEDBACK: `protected` members are similar to `private` in that they cannot be accessed from *outside* the class. However, unlike `private` members, `protected` members *can* be accessed directly by member functions of **derived classes** (classes that inherit from this one). `private` members cannot be accessed directly even by derived classes.

// --- STL Containers (Vector, Map, List) ---

// 6. What is the key difference in how `std::vector` and `std::list` store
//    their elements in memory? How does this affect accessing elements by index?
// ANSWER: vectors are stroed sequentially in memory, if you want to find the ith index its easy O(1) as you know where it is. each item of a list will store where the next and previos item is. this makes itterating through it harder (i forget why this is usefull tho, explain again when and why wed use a list. is it just the inserting thing??)
// FEEDBACK: Your description of memory storage is correct: vector is contiguous (like an array), list uses linked nodes. This makes vector index access (myVec[i]) very fast (O(1)), while list index access is very slow (O(n)) because you have to traverse the links from the start/end. Iterating through *both* using iterators or range-based for is efficient.
//    Why use list? Primarily for its O(1) constant-time insertion and deletion *anywhere* in the list (if you have an iterator to the location). In a vector, inserting/deleting in the middle requires shifting subsequent elements (O(n)). Also, list iterators/pointers remain valid after insertions/deletions elsewhere, unlike vector iterators.

// 7. If you need to frequently insert or delete elements in the *middle*
//    of a large sequence, would `std::vector` or `std::list` generally be more efficient? Why?
// ANSWER:  list, you dont need to push everthing else around in memory
// FEEDBACK: Correct. `std::list` is much more efficient (O(1)) for middle insertions/deletions because it only involves updating pointers, while `std::vector` requires shifting elements (O(n)).

// 8. What kind of data does `std::map<std::string, Room*>` store? What are the keys and what are the values?
// ANSWER:it relates room exit directions (string keys) to the actual rooms that are in that exit direction (value, room pointer).
// FEEDBACK: Correct. It stores key-value pairs. The keys are `std::string` (representing directions like "north"), and the values are `Room*` (pointers to the Room objects in those directions).

// 9. When iterating through a `std::map`, in what order are the elements visited?
// ANSWER: Whatever order the.... shit i forget the process name but something happens to the keys and that places them in some order, we ittrate in that order. I think. explain beter
// FEEDBACK: You iterate through a `std::map` in **sorted order based on the keys**. The map automatically keeps the keys sorted using its internal structure (usually a balanced binary search tree like a Red-Black Tree). So, if you iterate, you'd likely visit "east", then "north", then "south", then "west" (alphabetical order for strings).

// 10. Explain the difference between `myMap[key]` and `myMap.at(key)` for accessing elements in a map.
//     Which one is generally safer if you're unsure the key exists?
// ANSWER: .at(key) ensures it exists and is safer, i think the other one will just go to the memory location of key no matter if there is actually antyhing there. but i dont really know, explain what happens
// FEEDBACK: You're right that `.at(key)` is safer. Here's the difference:
//    - `myMap.at(key)`: Checks if `key` exists. If yes, returns a reference to the value. If no, it throws a `std::out_of_range` exception (error).
//    - `myMap[key]`: Checks if `key` exists. If yes, returns a reference to the value. If no, it **inserts a new element** with that `key` and a **default-constructed value** (e.g., 0 for int, nullptr for pointer, empty string for string), and *then* returns a reference to that newly inserted value. This insertion behavior can be surprising if you only intended to read.
//    So, `.at()` is safer when you only want to access existing elements and treat non-existence as an error.

// 11. How do you correctly remove the element at index `idx` from `std::vector<Item> myVec`?
//     Write the necessary C++ code snippet (assume `idx` is already validated).
// CODE:
// if (/* validation check */) {
//   itter = vector.begin() + removalIndex;
//   vector.erase(itter)
// } not really sure if this is right am i forgetting anything?
// FEEDBACK: Very close! Use the actual vector name (`myVec`), use `auto` for the iterator type, and use the correct index variable name (`idx`). Semicolons are also needed.
// if (idx >= 0 && static_cast<size_t>(idx) < myVec.size()) { // Example validation
//    auto iter_to_remove = myVec.begin() + idx;
//    myVec.erase(iter_to_remove);
// }

// 12. What is the difference between `myVector.push_back(object)` and `myVector.emplace_back(arg1, arg2)`?
//     Which one is often more efficient and why?
// ANSWER: push pack needs a fully formed object already. emplace creates an object. i think emplace is better but idk. also help me understand how these work in memory more. lets say i have an object and i use push back, i assuume a coppy of this object is then put into memory in the heap sequentially in the vectors memory block, that origonal obj might live on the stack, do i have this right? emplace takes whatever inputs you give it and also makes a new object in sequential memeory order on the heap. is this right?
// FEEDBACK: Your understanding is excellent!
//    - `push_back(object)` takes an existing object and *copies* (or *moves* if possible) it into the vector's storage.
//    - `emplace_back(arg1, arg2)` takes constructor arguments and *constructs* the object directly *in place* within the vector's storage, avoiding the creation of a separate temporary object.
//    - `emplace_back` is often more efficient because it can avoid the extra copy/move operation.
//    - Your memory understanding is correct. `std::vector` usually stores its elements on the heap. If you have `MyObject objOnStack; myVec.push_back(objOnStack);`, a copy of `objOnStack` is made on the heap space managed by the vector. `emplace_back` directly constructs the new object on the heap using the provided arguments.

// --- Pointers, References, Memory ---

// 13. Explain the difference between `*` and `&` when used in a variable declaration
//     (e.g., `int* ptr;` vs `int& ref = someVar;`).
// ANSWER: they are quite similar. & cant be null and cant be reassigned. int* ptr will be null here. they both are memory addresses tho. refs act more like the origonal, for a class ref you can do ref.method() but for a pointer you have to use ->. explain the syntax again, give an example and tell me more when to use one vs the other.
// FEEDBACK: Good points! Key clarifications:
//    - `int* ptr;`: Declares `ptr` as a **pointer** to an integer. `ptr` stores a *memory address*. It *can* be null (`nullptr`), and it *can* be reassigned to point to different addresses later. Access members via `->` (e.g., `taskPtr->display()`). Needs explicit dereference (`*ptr`) to get the value.
//    - `int& ref = someVar;`: Declares `ref` as a **reference** to an integer. A reference is an **alias** (another name) for `someVar`. It does *not* store an address itself; it directly refers to the original variable's memory. It *must* be initialized when declared and *cannot* be null or reseated to refer to a different variable. Access members via `.` (e.g., `taskRef.display()`). Acts syntactically like the original variable.
//    - When to use which (for function parameters): Use references (`const Type&` or `Type&`) when you need to refer to an existing object, want simpler syntax, and know it won't be null. Use pointers (`const Type*` or `Type*`) when the object might be optional (pass `nullptr`), or when interfacing with C APIs/arrays.

// 14. Explain the difference between `*` and `&` when used in an expression
//     (e.g., `*ptr = 5;` vs `ptr = &someVar;`).
// ANSWER: *ptr means take 5 and put it in the address at ptr. ptr = 5 means make the memory address = 5, which doesnt make sense. i htink doing ptr = &someval means take the memory address of someval and makt ptr that, but idk
// FEEDBACK: You are exactly right.
//    - `*ptr = 5;`: The `*` here is the **dereference operator**. It means "go to the address stored in `ptr` and set the value *at that address* to 5".
//    - `ptr = &someVar;`: The `&` here is the **address-of operator**. It means "get the memory address *of* `someVar` and store that address *in* the pointer variable `ptr`".
//    - `ptr = 5;` would indeed try to make the pointer store the literal memory address 5, which is almost always invalid and dangerous.

// 15. If a function takes a parameter `const std::string& str`, can the function modify
//     the original string object that was passed in? Why or why not?
// ANSWER: no, the const
// FEEDBACK: Correct. The `const` keyword prevents the function from modifying the object through the reference `str`. The `&` means it receives a reference (avoids copying), but `const` makes it read-only access.

// 16. If a function takes a parameter `MyClass* ptrParam`, what special value can the caller
//     pass to indicate that no object is being provided? How should the function check for this?
// ANSWER: nullPtr, idk how to check
// FEEDBACK: Correct value: `nullptr`. How to check:
//    if (ptrParam == nullptr) { /* Handle null case */ }
//    // Or, since nullptr evaluates to false in boolean contexts:
//    if (!ptrParam) { /* Handle null case */ }
//    // Conversely, to check if it's valid before using:
//    if (ptrParam) { /* Safe to use ptrParam->... */ }

// 17. Briefly describe the difference between Stack memory and Heap memory in terms of how
//     allocation/deallocation is managed and typical use cases.
// ANSWER: stak is more organized, first in first out, its faster used for local values in functions but cant hold huge values, the heap is unorganized blocks are assigned to variables with new, you must delete when done with the variable. What else am i missing
// FEEDBACK: Excellent summary! You covered the key points: Stack is LIFO, fast, automatic (compiler manages via function calls/returns), limited size, used for locals/params. Heap is manually managed (`new`/`delete`), slower allocation, larger size, flexible lifetime, used for dynamic data. You didn't miss much for a brief description!

// --- Input/Output & Control Flow ---

// 18. What are the two distinct actions performed by `std::endl` that differentiate it from just `"\n"`?
// ANSWER: the flush, endl forces a flush of cout buffer
// FEEDBACK: Correct. It inserts a newline character (`\n`) AND flushes the output stream buffer.

// 19. When reading numeric input followed by string input (using `std::cin >> num;` then `std::getline(std::cin, str);`),
//     why is it usually necessary to use `std::cin.ignore(...)` after reading the number?
// ANSWER: you hit enter to give the value to cin, cin consumes the num but leaves the new line in the buffer, if you didnt do ignore(what do i put here i forget), then getline will imedately hit the \n and fail
// FEEDBACK: Perfect explanation! The arguments typically used are:
//    `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');`
//    This discards characters until it encounters and discards the newline, ensuring `getline` waits for fresh input.

// 20. What does `std::cin.fail()` check for? What function do you call to reset the error state flags on `std::cin`?
// ANSWER: i think its cin.clear() but idk. i forget what it checks for
// FEEDBACK: `std::cin.fail()` returns `true` if either the `failbit` or the `badbit` error state flags are set on the stream. `failbit` is usually set for format errors (like reading 'abc' into an int). `badbit` indicates a more severe loss of stream integrity. You are correct, `std::cin.clear()` is the function used to reset these error flags.

// 21. What does the `break;` statement do when encountered inside a `do-while` loop?
// ANSWER: exits the do while
// FEEDBACK: Correct. It immediately terminates the enclosing `do-while` loop (or `while`, `for`, `switch`) and execution continues after the loop.

// 22. What is `std::optional<T>` used for? How do you check if an `std::optional<T>` object named `optVal` actually contains a value?
//     How do you access the contained value if it exists?
// ANSWER: its used when a value may or may not exist, you could check for null or so toher things but there are other issues assosiated with that. i think val1 is if it worked and val2 is the actual value but idk. explain more
// FEEDBACK: You've got the core purpose right! It represents an optional value.
//    - To check if it contains a value: Use the `.has_value()` member function (e.g., `if (optVal.has_value())`). Alternatively, `std::optional` can be used directly in a boolean context (e.g., `if (optVal)`), which is equivalent to checking `has_value()`.
//    - To access the value *after* you've confirmed it exists: Use the `.value()` member function (e.g., `auto theValue = optVal.value();`). Using `.value()` on an empty optional throws an exception. You can also use the dereference operator (`*optVal`) if you've already checked it has a value.

// --- Types & Casting ---

// 23. What is `size_t` and why is it typically used for loop counters when iterating over standard containers like `std::vector`?
// ANSWER: its an unsigned value (i think integer?) it is system agnostic.
// FEEDBACK: Correct, it's an unsigned integer type. It's system agnostic in the sense that it's guaranteed to be large enough to represent the maximum possible object size on that specific system. It's used because `.size()` returns `size_t`, and using `size_t` for the loop counter avoids potential signed/unsigned comparison warnings or errors.

// 24. What is the purpose of `static_cast<Type>(value)`?
// ANSWER: not sure
// FEEDBACK: `static_cast` is a C++ operator for performing relatively safe, explicit type conversions that can be verified by the compiler at compile time. Examples include converting between numeric types (`int` to `double`, `double` to `int` (with truncation)), converting pointers up or down a known inheritance hierarchy, or converting `void*` pointers back to their original type.

// --- Syntax & General ---

// 25. Correct the syntax error in this range-based for loop header:
//     `for (myVecValue : myVector)` (assuming `myVector` contains `int`s and you want copies)
// CORRECTED: for (int myVecValue : myVector). also it makes coppies? does it not use pointers?
// FEEDBACK: Correct syntax! `for (int myVecValue : myVector)`. Yes, this version makes a *copy* of each integer from `myVector` into `myVecValue` for each iteration. To avoid copies (more efficient for large objects), you'd use a reference: `for (const int& myVecValue : myVector)` (read-only) or `for (int& myVecValue : myVector)` (modifiable).

// 26. What is the purpose of header guards (e.g., `#ifndef MYHEADER_H ... #define MYHEADER_H ... #endif`)?
// ANSWER: when compiling each file is compiled seperately first then added together, if multple files include the same inports then all the defs in the h files will be repeted. this makes sure that the final one ishnt redefining a bunch of things. like in gameObject, this is everywhere but we just need it defined once. question, would it actully fail if we didnt have the ifndef thing? or is it just inefficient.
// FEEDBACK: Excellent explanation of the problem! Header guards prevent the contents of a header file from being included (and thus processed by the compiler) more than once within a single translation unit (.cpp file after preprocessing). Yes, it would absolutely cause compile-time errors (not just inefficiency) without guards if a header was included multiple times (e.g., if `room.h` includes `item.h` and `main.cpp` includes both `room.h` and `item.h`). You would get errors about redefining classes, functions, etc., because the compiler would see the definitions multiple times within the same expanded `main.cpp` file.

// --- End of Quiz ---
// Save this file with your answers.