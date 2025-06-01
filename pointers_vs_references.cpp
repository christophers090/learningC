#include <iostream>
#include <string>

// ==========================================================================
// C++ Pointers vs. References: Syntax and Usage Examples
// ==========================================================================

// --- Helper struct for examples ---
struct MyData
{
    int value;
    std::string name;

    MyData(int v, const std::string &n) : value(v), name(n) {}

    void display() const
    {
        std::cout << "MyData: { value: " << value << ", name: '" << name << "' }" << std::endl;
    }

    void incrementValue()
    {
        value++;
    }
};

// --- Function to demonstrate pass-by-value (for comparison) ---
void processByValue(int val, MyData data_obj)
{
    val++;                     // Modifies local copy
    data_obj.incrementValue(); // Modifies local copy
    std::cout << "  Inside processByValue: val = " << val << std::endl;
    std::cout << "  Inside processByValue: data_obj.value = " << data_obj.value << std::endl;
}

// --- Function demonstrating pass-by-pointer ---
void processByPointer(int *ptr_val, MyData *ptr_obj)
{
    if (ptr_val)
    {                 // Always check for nullptr before dereferencing
        (*ptr_val)++; // Dereference to modify original value
        std::cout << "  Inside processByPointer: *ptr_val = " << *ptr_val << std::endl;
    }
    if (ptr_obj)
    {                              // Always check for nullptr
        ptr_obj->incrementValue(); // Use -> to access members of object via pointer
        std::cout << "  Inside processByPointer: ptr_obj->value = " << ptr_obj->value << std::endl;
    }
}

// --- Function demonstrating pass-by-reference ---
void processByReference(int &ref_val, MyData &ref_obj)
{
    // No need to check for null, references must refer to valid objects
    ref_val++;                // Directly modifies original value (acts like an alias)
    ref_obj.incrementValue(); // Use . to access members of object via reference
    std::cout << "  Inside processByReference: ref_val = " << ref_val << std::endl;
    std::cout << "  Inside processByReference: ref_obj.value = " << ref_obj.value << std::endl;
}

// --- Function demonstrating pass-by-const-reference (avoids copy, read-only) ---
void printByConstReference(const MyData &const_ref_obj)
{
    // const_ref_obj.incrementValue(); // COMPILE ERROR: cannot modify via const reference
    std::cout << "  Inside printByConstReference: " << std::endl;
    const_ref_obj.display(); // Can call const member functions
}

int main()
{
    std::cout << "--- Section 1: Declaration and Initialization ---" << std::endl;

    int original_x = 10;
    MyData original_data_obj(100, "Original");

    // --- Pointers ---
    std::cout << "\n* Pointers *" << std::endl;
    int *x_ptr;          // 1. Declaration: Can be declared without immediate initialization.
                         //    x_ptr currently holds a garbage address.
    x_ptr = &original_x; // 2. Initialization/Assignment: Assign address of original_x.
                         //    Now x_ptr "points to" original_x.

    int *y_ptr = nullptr; // 3. Nullability: Pointers can be explicitly set to nullptr (or NULL in older C++).
                          //    Indicates it doesn't point to any valid object.

    MyData *data_obj_ptr = &original_data_obj;

    std::cout << "original_x address: " << &original_x << std::endl;
    std::cout << "x_ptr stores address: " << x_ptr << std::endl;
    std::cout << "Value pointed to by x_ptr (*x_ptr): " << *x_ptr << std::endl;
    data_obj_ptr->display(); // Access member using ->

    // --- References ---
    std::cout << "\n* References *" << std::endl;
    // int& x_ref;           // 1. Declaration: COMPILE ERROR! References MUST be initialized upon declaration.
    int &x_ref = original_x; // 2. Initialization: x_ref is now an alias for original_x.
                             //    It refers to the same memory location as original_x.

    // int& y_ref = nullptr; // 3. Nullability: COMPILE ERROR! References cannot be null (they must refer to an existing object).

    MyData &data_obj_ref = original_data_obj;

    std::cout << "original_x address: " << &original_x << std::endl;
    std::cout << "x_ref refers to address: " << &x_ref << " (same as original_x)" << std::endl;
    std::cout << "Value of x_ref (acts like original_x): " << x_ref << std::endl;
    data_obj_ref.display(); // Access member using .

    std::cout << "\n--- Section 2: Core Differences ---" << std::endl;

    // --- Reassignment ---
    std::cout << "\n* Reassignment *" << std::endl;
    int another_x = 20;
    x_ptr = &another_x; // Pointers CAN be reseated (reassigned) to point to another object.
    std::cout << "x_ptr now points to another_x. *x_ptr = " << *x_ptr << std::endl;

    // x_ref = another_x;    // This does NOT make x_ref refer to another_x.
    // Instead, it ASSIGNS the VALUE of another_x to original_x (which x_ref aliases).
    // References CANNOT be reseated to refer to a different memory location after initialization.
    x_ref = 30; // This changes original_x to 30.
    std::cout << "Assigned 30 to x_ref. original_x = " << original_x << ", x_ref = " << x_ref << std::endl;
    original_x = 10; // Reset for next examples

    // --- Accessing the value ---
    std::cout << "\n* Accessing the Value *" << std::endl;
    *x_ptr = 15; // Dereference operator `*` needed to access/modify the value pointed to.
    std::cout << "After *x_ptr = 15; original_x (via another_x) = " << another_x << std::endl;
    another_x = 20;      // Reset another_x
    x_ptr = &original_x; // Point x_ptr back to original_x for consistency

    x_ref = 16; // No special operator needed. Acts directly on the aliased variable.
    std::cout << "After x_ref = 16; original_x = " << original_x << std::endl;
    original_x = 10; // Reset

    // --- Arithmetic (Pointers vs. References) ---
    // Pointer arithmetic is possible (moves pointer by sizeof(type) * n)
    // Reference arithmetic is not a concept (operations apply to the aliased object).

    std::cout << "\n--- Section 3: Usage in Functions ---" << std::endl;

    int num = 5;
    MyData obj(50, "TestObj");
    std::cout << "Before function calls: num = " << num << ", obj.value = " << obj.value << std::endl;

    // Pass-by-value (copies are made)
    std::cout << "Calling processByValue:" << std::endl;
    processByValue(num, obj);
    std::cout << "After processByValue:  num = " << num << ", obj.value = " << obj.value << " (originals unchanged)" << std::endl;

    // Pass-by-pointer (can modify original, can pass nullptr)
    std::cout << "Calling processByPointer with valid pointers:" << std::endl;
    processByPointer(&num, &obj);
    std::cout << "After processByPointer: num = " << num << ", obj.value = " << obj.value << " (originals modified)" << std::endl;

    num = 5;
    obj.value = 50; // Reset
    std::cout << "Calling processByPointer with nullptr for int:" << std::endl;
    processByPointer(nullptr, &obj);
    std::cout << "After processByPointer (nullptr int): num = " << num << ", obj.value = " << obj.value << std::endl;

    // Pass-by-reference (modifies original, cannot pass "null")
    num = 5;
    obj.value = 50; // Reset
    std::cout << "Calling processByReference:" << std::endl;
    processByReference(num, obj);
    std::cout << "After processByReference: num = " << num << ", obj.value = " << obj.value << " (originals modified)" << std::endl;

    // Pass-by-const-reference (avoids copy, guarantees no modification)
    std::cout << "Calling printByConstReference:" << std::endl;
    MyData large_obj(200, "LargeObject");
    printByConstReference(large_obj); // Efficient for large objects, no copy made.
                                      // large_obj is guaranteed not to be modified.
    std::cout << "After printByConstReference: large_obj.value = " << large_obj.value << " (unchanged)" << std::endl;

    // Example of a pointer member (common)
    struct Node
    {
        int data;
        Node *next; // Pointer to another Node, can be nullptr
        Node(int d) : data(d), next(nullptr) {}
    };
    Node n1(1), n2(2);
    n1.next = &n2;
    if (n1.next)
    {
        std::cout << "Node n1 points to Node with data: " << n1.next->data << std::endl;
    }

    // Example of a reference member (less common, must be initialized in constructor list)
    struct Owner
    {
        MyData &owned_data;                                     // Reference member
        Owner(MyData &data_to_own) : owned_data(data_to_own) {} // Must be initialized here

        void show_owned()
        {
            owned_data.display();
        }
    };
    MyData external_data(500, "External");
    Owner o(external_data);
    o.show_owned();
    external_data.incrementValue(); // Modifying external_data also changes what o.owned_data refers to
    std::cout << "After modifying external_data:" << std::endl;
    o.show_owned();

    std::cout << "\n--- End of Pointers vs. References Demo ---" << std::endl;
    return 0;
}

/*
Key Takeaways:

1.  Initialization:
    -   Pointers: Can be uninitialized (dangerous), can be nullptr.
    -   References: MUST be initialized at declaration and cannot be "null" (must refer to a valid object).

2.  Reassignment (Reseating):
    -   Pointers: CAN be reassigned to point to different objects or nullptr.
    -   References: CANNOT be reseated to refer to a different object after initialization.
        Assigning to a reference changes the value of the object it refers to.

3.  Nullability:
    -   Pointers: Can be `nullptr`, indicating they don't point to anything.
    -   References: Should always refer to a valid object. There's no direct concept of a "null reference"
        in the same way as a null pointer (though you can have a pointer to a reference which is null, that's advanced and rare).

4.  Syntax:
    -   Pointers: Use `*` to declare and dereference. Use `->` to access members of an object via pointer.
    -   References: Use `&` to declare. Access the object and its members directly using `.` (like a regular variable).

5.  Use Cases:
    -   Pointers: Optional values, ability to change what is pointed to, C-style arrays/APIs, low-level memory manipulation.
    -   References: Aliasing, pass-by-reference (especially const-reference for efficiency without modification), operator overloading.
        Often preferred for function parameters when an object is required and null is not a valid option.
*/