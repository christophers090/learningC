int main() {
    int a = 10;
    int b = 20;
    int result = 0;

    if (a < b) {
        result = 1; // Condition is true
    } else {
        result = 2; // Condition is false
    }
    // printf("Result: %d\n", result); // We'll ignore printf for simplicity
    return result; // Return value will show which path was taken
}