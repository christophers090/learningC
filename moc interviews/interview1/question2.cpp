#include <iostream>
#include <vector> // Included for std::size_t potentially, though not strictly required

// Task: Complete this function
// It should:
// 1. Dynamically allocate an array of 'double' of the given 'size' on the heap.
// 2. Initialize all elements of the array to 0.0.
// 3. (For demonstration) Print the value of the first and last element.
// 4. Correctly deallocate the memory.
// 5. Handle the case where size might be 0 or negative (optional but good practice).

void allocateAndDeallocate(int size)
{
    std::cout << "\nAttempting to allocate for size: " << size << std::endl;

    // Basic size check (good practice)
    if (size <= 0)
    {
        std::cout << "  Invalid size, cannot allocate." << std::endl;
        return;
    }

    // 1. Allocate the array
    double *dataArray = nullptr; // Initialize to nullptr
    dataArray = new double[size];

    // Check if allocation succeeded (important in memory-constrained environments)
    // Note: In modern C++, 'new' usually throws std::bad_alloc on failure
    // instead of returning nullptr. Handling the exception with try/catch
    // is the standard way, but checking for nullptr is still seen in older
    // code or environments where exceptions might be disabled.
    if (dataArray == nullptr)
    {
        std::cout << "  Memory allocation failed!" << std::endl;
        return;
    }

    // 2. Initialize elements to 0.0
    // Q: for(int& el : *dataArray){ this didnt work why is that, does this only work for vectors?
    // A: Range-based for loops (`for (auto& el : container)`) work with containers
    //    that define begin() and end() iterators (like std::vector, std::array, std::string).
    //    A raw pointer (`dataArray`) obtained from `new[]` doesn't inherently have these.
    //    While `*dataArray` gives you the first element (a single double), it's not a container
    //    that the range-based loop knows how to iterate over.
    for (size_t i = 0; i < static_cast<size_t>(size); ++i) // Good practice to cast size to size_t for comparison
    {
        // Q: *dataArray[i] = 0.0; this also failed, why? i thought that we needed to do *dataArray because the dataArray is just  a pointer?
        // A: Operator precedence is the key here. The array subscript operator `[]` has higher
        //    precedence than the dereference operator `*`.
        //    So, `*dataArray[i]` is interpreted as `*(dataArray[i])`.
        //    `dataArray[i]` already gives you the double value *at* index i (it's syntactic sugar for *(dataArray + i)).
        //    Therefore, you are trying to dereference (`*`) a `double` value, which is incorrect.
        //    `dataArray[i] = 0.0;` is the correct way - it accesses the i-th double in the array pointed to by dataArray.
        dataArray[i] = 0.0;
    }

    // 3. Print first and last elements (only if size > 0)
    std::cout << "  First element: " << dataArray[0] << std::endl;
    std::cout << "  Last element: " << dataArray[size - 1] << std::endl;

    std::cout << "  (Array allocated and initialized - pretend work is done)" << std::endl;

    // 4. Deallocate the memory
    delete[] dataArray;

    std::cout << "  Memory deallocated." << std::endl;
}

int main()
{
    allocateAndDeallocate(5);
    allocateAndDeallocate(1);
    allocateAndDeallocate(0);
    allocateAndDeallocate(-2);
    allocateAndDeallocate(1000); // A slightly larger allocation

    return 0;
}