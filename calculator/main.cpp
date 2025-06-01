#include <iostream> // For standard I/O (cin, cout, cerr)
#include <string>   // For using std::string
#include <limits>   // For std::numeric_limits (used in input clearing)
#include <optional> // For returning optional results from calculation
#include <cctype>   // For std::tolower

// Forward Declarations
void displayWelcomeMessage();
std::optional<double> getValidatedNumber(const std::string &prompt);
std::optional<char> getValidatedOperator(const std::string &prompt);
std::optional<double> performCalculation(double num1, double num2, char op);
bool askToContinue();

/**
 * @brief Main entry point for the calculator application.
 *
 * Orchestrates the program flow: displaying the welcome message,
 * getting user input within a loop, performing calculations,
 * displaying results or errors, and asking the user if they wish
 * to perform another calculation.
 *
 * @return int Returns 0 on successful execution, non-zero otherwise.
 */
int main()
{
    displayWelcomeMessage();

    do
    {
        std::optional<double> num1Opt = getValidatedNumber("Enter the first number: ");
        // Check if number input was successful (e.g., user didn't hit EOF)
        if (!num1Opt)
            break;

        std::optional<char> opOpt = getValidatedOperator("Enter an operator (+, -, *, /): ");
        if (!opOpt)
            break;

        std::optional<double> num2Opt = getValidatedNumber("Enter the second number: ");
        if (!num2Opt)
            break;

        // Perform calculation only if all inputs were validly obtained
        std::optional<double> resultOpt = performCalculation(num1Opt.value(), num2Opt.value(), opOpt.value());

        // Display result or appropriate error message
        if (resultOpt.has_value())
        {
            std::cout << "Result: "
                      << num1Opt.value() << " " << opOpt.value() << " " << num2Opt.value()
                      << " = " << resultOpt.value() << std::endl;
        }
        else
        {
            // Specific error (like div by zero) is handled by performCalculation printing to cerr
            // We could add a more generic message here if desired, but often letting
            // the calculation function report the specific error is sufficient.
            std::cout << "Calculation could not be performed." << std::endl;
        }

    } while (askToContinue()); // Loop based on user choice

    std::cout << "\nExiting calculator. Goodbye!" << std::endl;
    return 0; // Indicate successful execution
}

/**
 * @brief Displays a simple welcome message to the console.
 */
void displayWelcomeMessage()
{
    std::cout << "--- Simple Console Calculator ---" << std::endl;
}

/**
 * @brief Prompts the user for a number and validates the input.
 *
 * Continuously prompts the user with the given message until a valid
 * double is entered. Handles non-numeric input and clears the input buffer.
 * Returns std::nullopt if an unrecoverable stream error occurs (like EOF).
 *
 * @param prompt The message to display to the user.
 * @return std::optional<double> Containing the valid number, or std::nullopt on stream failure.
 */
std::optional<double> getValidatedNumber(const std::string &prompt)
{
    double value{}; // Use {} initialization
    while (true)
    {
        std::cout << prompt;
        // Attempt to read and check stream state in one go
        if (std::cin >> value)
        {
            // Clear the rest of the line (e.g., the newline character)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value; // Success
        }
        else
        {
            // Handle potential stream errors (including EOF)
            if (std::cin.eof())
            {
                std::cerr << "\nError: End of input reached while expecting a number." << std::endl;
                return std::nullopt; // Indicate failure due to EOF
            }
            // Handle format errors (non-numeric input)
            std::cerr << "Error: Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // Clear the error flags (like failbit)
            // Discard the invalid input line
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

/**
 * @brief Prompts the user for a valid operator (+, -, *, /) and validates it.
 *
 * Continuously prompts until exactly one valid operator character is entered.
 * Reads the entire line to handle extraneous input.
 * Returns std::nullopt if an unrecoverable stream error occurs (like EOF).
 *
 * @param prompt The message to display to the user.
 * @return std::optional<char> Containing the valid operator char, or std::nullopt on stream failure.
 */
std::optional<char> getValidatedOperator(const std::string &prompt)
{
    std::string input;
    while (true)
    {
        std::cout << prompt;
        if (std::getline(std::cin, input))
        {
            // Validate: Input should be exactly one character long
            if (input.length() == 1)
            {
                char op = input[0];
                // Validate: Character must be one of the allowed operators
                if (op == '+' || op == '-' || op == '*' || op == '/')
                {
                    return op; // Success
                }
            }
            // If length != 1 or char is not valid, fall through to error message
        }
        else
        {
            // Handle potential stream errors (likely EOF)
            if (std::cin.eof())
            {
                std::cerr << "\nError: End of input reached while expecting an operator." << std::endl;
                return std::nullopt; // Indicate failure due to EOF
            }
            // For other getline errors, just clear and try again
            std::cin.clear();
            // Ignore might not be needed here if getline failed, but can be harmless
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        // If we reach here, input was invalid
        std::cerr << "Error: Invalid operator. Please enter exactly one of +, -, *, /." << std::endl;
    }
}

/**
 * @brief Performs the calculation based on the provided operands and operator.
 *
 * Handles basic arithmetic operations (+, -, *, /).
 * Includes a check for division by zero.
 *
 * @param num1 The first operand.
 * @param num2 The second operand.
 * @param op The operator character (+, -, *, /).
 * @return std::optional<double> The result of the calculation, or std::nullopt if the operation
 *         is invalid (e.g., division by zero, unknown operator).
 */
std::optional<double> performCalculation(double num1, double num2, char op)
{
    switch (op)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        if (num2 == 0.0)
        {
            std::cerr << "Error: Division by zero is not permitted." << std::endl;
            return std::nullopt; // Indicate error
        }
        return num1 / num2;
    default:
        // This case should technically not be reachable if getValidatedOperator works correctly,
        // but it's good defensive programming.
        std::cerr << "Error: An unknown operator was encountered: '" << op << "'" << std::endl;
        return std::nullopt; // Indicate error
    }
}

/**
 * @brief Asks the user if they want to perform another calculation.
 *
 * Handles 'y'/'Y' for yes and 'n'/'N' for no, re-prompting on invalid input.
 * Reads the whole line to handle extraneous input.
 *
 * @return true If the user wants to continue, false otherwise.
 */
bool askToContinue()
{
    std::string input;
    while (true)
    {
        std::cout << "\nPerform another calculation? (y/n): ";
        if (std::getline(std::cin, input))
        {
            if (input.length() == 1)
            {
                char choice = static_cast<char>(std::tolower(input[0])); // Convert to lowercase
                if (choice == 'y')
                {
                    return true;
                }
                if (choice == 'n')
                {
                    return false;
                }
            }
        }
        else
        {
            // Handle potential stream errors (likely EOF)
            if (std::cin.eof())
            {
                std::cerr << "\nError: End of input reached while asking to continue." << std::endl;
                return false; // Treat EOF as wanting to exit
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        // If we reach here, input was invalid
        std::cerr << "Error: Please enter 'y' or 'n'." << std::endl;
    }
}