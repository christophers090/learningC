// ==========================================================================
// common_interview_examples.cpp - Illustrative Examples for C++ Interviews
// ==========================================================================

#include <iostream>
#include <vector>
#include <string>
#include <memory>    // For std::unique_ptr
#include <algorithm> // For std::reverse
#include <map>
#include <cstdint>   // For uint8_t
#include <stdexcept> // For std::runtime_error

// --- 1. Pointers vs. References ---

void modifyViaPointer(int *ptr)
{
    if (ptr)
    {             // Always check pointers for null
        (*ptr)++; // Dereference to modify the original value
    }
}

void modifyViaReference(int &ref)
{
    // No null check needed for references
    // No dereference needed, acts as alias
    ref++;
}

void pointers_vs_references_demo()
{
    std::cout << "\n--- Pointers vs. References Demo ---" << std::endl;
    int x = 10;
    int y = 10;

    int *x_ptr = &x;
    int &y_ref = y; // Must be initialized

    modifyViaPointer(x_ptr);
    modifyViaReference(y_ref);

    std::cout << "x after modifyViaPointer: " << x << " (Expected: 11)" << std::endl;
    std::cout << "y after modifyViaReference: " << y << " (Expected: 11)" << std::endl;

    // Reassign pointer
    int z = 20;
    x_ptr = &z;
    std::cout << "Pointer now points to value: " << *x_ptr << std::endl;

    // Cannot reseat reference
    // y_ref = z; // This assigns z's VALUE (20) to y, doesn't make y_ref refer to z.
    // std::cout << "y after trying to reseat reference: " << y << std::endl;
}

// --- 2. Const Correctness ---

class ConstDemo
{
    int value_ = 0;

public:
    // Getter marked const - promises not to change object state
    int getValue() const
    {
        // value_++; // Compile Error: Cannot modify member in const method
        return value_;
    }

    // Setter is not const - it intends to change object state
    void setValue(int v)
    {
        value_ = v;
    }
};

void useConstObject(const ConstDemo &demo)
{
    std::cout << "Value from const object: " << demo.getValue() << std::endl;
    // demo.setValue(5); // Compile Error: Cannot call non-const method on const object/reference
}

void const_correctness_demo()
{
    std::cout << "\n--- Const Correctness Demo ---" << std::endl;
    ConstDemo obj;
    obj.setValue(100);
    useConstObject(obj); // Pass non-const obj to function expecting const ref (OK)
}

// --- 3. Virtual Functions & Polymorphism ---

class BaseShape
{
public:
    // Virtual destructor is crucial for base classes!
    virtual ~BaseShape() { std::cout << "BaseShape Destructor\n"; }

    // Pure virtual function makes BaseShape an abstract class
    virtual double area() const = 0;

    // Regular virtual function with a default implementation
    virtual void draw() const
    {
        std::cout << "Drawing a generic shape\n";
    }
};

class Circle : public BaseShape
{
    double radius_;

public:
    Circle(double r) : radius_(r) {}
    ~Circle() override { std::cout << "Circle Destructor\n"; } // Override is good practice

    double area() const override
    { // Override base implementation
        return 3.14159 * radius_ * radius_;
    }
    void draw() const override
    {
        std::cout << "Drawing a circle with radius " << radius_ << "\n";
    }
};

class Rectangle : public BaseShape
{
    double width_, height_;

public:
    Rectangle(double w, double h) : width_(w), height_(h) {}
    ~Rectangle() override { std::cout << "Rectangle Destructor\n"; }

    double area() const override
    {
        return width_ * height_;
    }
    // Inherits BaseShape::draw() if not overridden
    void draw() const override
    {
        std::cout << "Drawing a rectangle " << width_ << "x" << height_ << "\n";
    }
};

void polymorphism_demo()
{
    std::cout << "\n--- Polymorphism Demo ---" << std::endl;
    // Using smart pointers is safer!
    std::vector<std::unique_ptr<BaseShape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Circle>(2.0));

    // Polymorphic behavior: Calling virtual functions via base class pointers
    for (const auto &shape_ptr : shapes)
    {
        shape_ptr->draw();                                         // Calls the correct derived class version
        std::cout << "  Area: " << shape_ptr->area() << std::endl; // Calls derived area()
    }

    std::cout << "Shapes going out of scope (destructors should run correctly)...\n";
    // unique_ptrs automatically manage deletion when vector is destroyed
}

// --- 4. RAII and Smart Pointers ---

void unsafe_resource_management()
{
    std::cout << "\n--- Manual Resource Management (Unsafe Example) ---" << std::endl;
    int *raw_ptr = new int(10); // Manually allocate
    // If an exception occurs here, the memory is leaked!
    if (*raw_ptr > 5)
    {
        std::cout << "Raw pointer value: " << *raw_ptr << std::endl;
        // Forget to delete? Memory Leak!
        // delete raw_ptr; // Need to remember this
    }
    delete raw_ptr; // Must remember to delete manually
}

void safe_resource_management()
{
    std::cout << "\n--- RAII with Smart Pointer (Safe Example) ---" << std::endl;
    // Resource acquisition IS initialization
    std::unique_ptr<int> smart_ptr = std::make_unique<int>(20);

    // If an exception occurs here, smart_ptr's destructor still runs (stack unwinding)
    if (smart_ptr && *smart_ptr > 10)
    { // Can check smart pointer like a raw pointer
        std::cout << "Smart pointer value: " << *smart_ptr << std::endl;
    }
    // No delete needed! Destructor of unique_ptr called automatically when it goes out of scope.
    std::cout << "Smart pointer going out of scope... memory automatically freed.\n";
}

// --- 5. Basic STL Containers ---

void stl_demo()
{
    std::cout << "\n--- STL Demo ---" << std::endl;

    // Vector: Dynamic array
    std::vector<int> numbers = {1, 2, 3};
    numbers.push_back(4);    // Add to end
    numbers.emplace_back(5); // Construct in place at end
    std::cout << "Vector elements: ";
    for (int num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << "\nVector size: " << numbers.size() << ", capacity: " << numbers.capacity() << std::endl;
    if (!numbers.empty())
    {
        std::cout << "First element: " << numbers.front() << ", Last element: " << numbers.back() << std::endl;
        std::cout << "Element at index 1: " << numbers[1] << " (or numbers.at(1))" << std::endl;
    }

    // Map: Key-value store (ordered)
    std::map<std::string, int> ages;
    ages["Alice"] = 30;
    ages["Bob"] = 25;
    ages.insert({"Charlie", 35}); // Another way to insert
    // ages.emplace("David", 40); // Can also emplace

    std::cout << "\nMap elements (ordered by key):" << std::endl;
    for (const auto &pair : ages)
    {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }

    std::string search_key = "Bob";
    auto it = ages.find(search_key); // Efficient lookup
    if (it != ages.end())
    {
        std::cout << search_key << " found, age: " << it->second << std::endl;
    }
    else
    {
        std::cout << search_key << " not found." << std::endl;
    }

    // Access with [] - careful, inserts if key doesn't exist!
    std::cout << "Accessing Bob via []: " << ages["Bob"] << std::endl;
    // std::cout << "Accessing Unknown via []: " << ages["Unknown"] << std::endl; // Inserts "Unknown" with value 0!
}

// --- 6. Simple Algorithm Example ---

void reverse_string(std::string &str)
{
    std::reverse(str.begin(), str.end());
    // Manual implementation:
    // size_t n = str.length();
    // for (size_t i = 0; i < n / 2; ++i) {
    //     std::swap(str[i], str[n - 1 - i]);
    // }
}

void algorithm_demo()
{
    std::cout << "\n--- Algorithm Demo ---" << std::endl;
    std::string text = "Hello World";
    std::cout << "Original string: '" << text << "'" << std::endl;
    reverse_string(text);
    std::cout << "Reversed string: '" << text << "'" << std::endl;
}

// --- 7. Basic Bit Manipulation ---

void bit_manipulation_demo()
{
    std::cout << "\n--- Bit Manipulation Demo ---" << std::endl;
    uint8_t flags = 0b00001010; // Start with bits 1 and 3 set (value 10)

    // Set bit 5
    flags |= (1 << 5); // flags is now 0b00101010
    std::cout << "After setting bit 5: " << static_cast<int>(flags) << std::endl;

    // Check if bit 3 is set
    bool bit3_set = (flags & (1 << 3)) != 0;
    std::cout << "Is bit 3 set? " << std::boolalpha << bit3_set << " (Expected: true)" << std::endl;

    // Clear bit 1
    flags &= ~(1 << 1); // flags is now 0b00101000
    std::cout << "After clearing bit 1: " << static_cast<int>(flags) << std::endl;

    // Toggle bit 5
    flags ^= (1 << 5); // flags is now 0b00001000
    std::cout << "After toggling bit 5: " << static_cast<int>(flags) << std::endl;
}

// --- Main Function to Run Demos ---
int main()
{
    std::cout << "====== Common C++ Interview Examples ======" << std::endl;

    pointers_vs_references_demo();
    const_correctness_demo();
    polymorphism_demo();
    // unsafe_resource_management(); // Can run to see leak detectors work (if configured)
    safe_resource_management();
    stl_demo();
    algorithm_demo();
    bit_manipulation_demo();

    std::cout << "\n====== Demos Complete ======" << std::endl;
    return 0;
}