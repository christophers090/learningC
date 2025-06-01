#include <iostream>
#include <string>

// --- Pointer & Reference Syntax Quiz (v2) ---

// Instructions: Fill in the blanks (???) or fix the lines marked with // FIX ME

// Struct for examples
struct Dimensions
{
    double width;
    double height;
};

int main()
{
    std::string label = "Box";
    int count = 50;
    Dimensions size = {10.5, 4.2};

    std::string *labelPtr = nullptr;
    int &countRef = count; // Reference initialized

    std::cout << "--- Quiz v2 Start ---" << std::endl;

    // Q1: Make labelPtr point to the 'label' variable.
    labelPtr = &label;

    // Q2: Using labelPtr, print the value of the string it points to.
    std::cout << "Label via pointer: " << *labelPtr << std::endl; // Should print "Box"

    // Q3: Using labelPtr, change the original 'label' string to "Container".
    *labelPtr = "Container";
    std::cout << "Original label after pointer change: " << label << std::endl; // Should print "Container"

    // Q4: Using the existing countRef, print the value of 'count'.
    std::cout << "Count via reference: " << countRef << std::endl; // Should print 50

    // Q5: Using the existing countRef, change the original 'count' to 55.
    countRef = 55;
    std::cout << "Original count after reference change: " << count << std::endl; // Should print 55

    // Q6: Declare a pointer named 'dimsPtr' and make it point to the 'size' struct.
    Dimensions *dimsPtr = &size;

    // Q7: Using dimsPtr and the arrow operator, print the 'width' of 'size'.
    std::cout << "Width via pointer: " << dimsPtr->width << std::endl; // Should print 10.5

    // Q8: Declare a reference named 'dimsRef' that refers to the 'size' struct.
    Dimensions &dimsRef = size;

    // Q9: Using dimsRef and the dot operator, change the 'height' of 'size' to 5.0.
    dimsRef.height = 5.0;
    std::cout << "Height via reference (check original): " << size.height << std::endl; // Should print 5.0

    // Q10: FIX ME: This tries to assign a pointer to a non-pointer integer.
    // How should 'countAddressHolder' be declared?
    int *countAddressHolder = &count;

    // Q11: FIX ME: This tries to compare an address (pointer) with a value.
    // How do you check if labelPtr actually points to something (is not null)?
    if (labelPtr == nullptr) // or if(!labelPtr), does this work?
    {
        std::cout << "labelPtr is null!" << std::endl;
    }
    else
    {
        std::cout << "labelPtr points to: " << *labelPtr << std::endl;
    }

    std::cout << "--- Quiz v2 End ---" << std::endl;

    return 0;
}

// You can add the answers here yourself after trying!
