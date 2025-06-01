#include "Room.h"
#include "Item.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>   // For splitting commands
#include <iterator>  // For splitting commands
#include <algorithm> // For std::find_if

// Helper function to convert string to lowercase
std::string toLower(const std::string &str)
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return lowerStr;
}

// Helper function to split a string by spaces
std::vector<std::string> splitCommand(const std::string &command)
{
    std::istringstream iss(command);
    std::vector<std::string> tokens{
        std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>{}};
    return tokens;
}

// Helper function to print inventory
void printInventory(const std::vector<Item> &inventory)
{
    std::cout << "Inventory:" << std::endl;
    if (inventory.empty())
    {
        std::cout << "  (empty)" << std::endl;
    }
    else
    {
        for (const auto &item : inventory)
        {
            std::cout << "  - " << item.getName() << std::endl;
        }
    }
}

// Helper function for help text
void printHelp()
{
    std::cout << "Available commands:" << std::endl;
    std::cout << "  go [direction] / n, s, e, w - Move to another room (e.g., go north)" << std::endl;
    std::cout << "  look                      - Describe the current room again" << std::endl;
    std::cout << "  take [item name]          - Pick up an item from the room" << std::endl;
    std::cout << "  drop [item name]          - Drop an item from your inventory" << std::endl;
    std::cout << "  inventory / i             - Show your inventory" << std::endl;
    std::cout << "  help                      - Show this help message" << std::endl;
    std::cout << "  quit                      - Exit the game" << std::endl;
}

int main()
{
    // --- World Creation ---
    Room entrance("Crypt Entrance", "You stand at the crumbling stone entrance to the Whispering Crypt.\nA dark passageway leads north into the earth. The air is cool and smells of damp soil and dust.");
    Room antechamber("Antechamber", "You are in the Antechamber.\nWater drips steadily from the ceiling into a small puddle near the west wall.\nThe walls are smooth, damp stone.");
    Room hall("Hall of Echoes", "You are in the Hall of Echoes.\nThis long hall stretches north into darkness. Your torchlight barely penetrates the gloom ahead.\nAlong the west wall stands a heavy wooden DOOR. It looks sturdy.");
    Room dusty_tomb("Dusty Tomb", "This small chamber is filled with ancient sarcophagi, coated in thick dust.\nAn eerie silence hangs in the air. An exit leads south.");

    // --- Link Rooms (Two-way, lowercase directions) ---
    entrance.addExit("north", &antechamber);
    antechamber.addExit("south", &entrance);
    antechamber.addExit("north", &hall);
    hall.addExit("south", &antechamber);
    hall.addExit("north", &dusty_tomb);
    dusty_tomb.addExit("south", &hall);
    // TODO: Add east/west exits and rooms, potentially locked doors

    // --- Add Items ---
    Item rustyKey("Rusty Key", "It feels cold and rough in your hand.");
    Item torch("Torch", "A flickering wooden torch. Provides light.");
    Item dustyCoin("Dusty Coin", "A tarnished silver coin, perhaps valuable.");

    antechamber.addItem(rustyKey);
    entrance.addItem(torch);
    dusty_tomb.addItem(dustyCoin);
    dusty_tomb.addItem(Item("Skull", "A yellowed human skull.")); // Adding another item

    // --- Player State ---
    Room *currentRoom = &entrance; // Player starts at the entrance
    std::vector<Item> playerInventory;
    playerInventory.push_back(Item("Tattered Map", "A map that seems mostly useless.")); // Starting item

    std::cout << "--- Welcome to the Whispering Crypt --- \n"
              << std::endl;
    printHelp(); // Show help initially
    std::cout << std::endl;

    // --- Main Game Loop ---
    bool gameRunning = true;
    while (gameRunning)
    {
        std::cout << "----------------------------------------\n";
        // Describe the current room
        std::cout << currentRoom->getDescription() << std::endl;

        std::cout << "\n> ";
        std::string lineInput;
        if (!std::getline(std::cin, lineInput))
        {
            break; // Exit loop on EOF/error
        }

        // Convert to lowercase and split into tokens
        std::string lowerInput = toLower(lineInput);
        std::vector<std::string> commandTokens = splitCommand(lowerInput);

        if (commandTokens.empty())
        {
            continue; // Ignore empty input
        }

        std::string verb = commandTokens[0];
        std::string noun = (commandTokens.size() > 1) ? commandTokens[1] : ""; // Basic noun extraction
        // For multi-word nouns, we might need to rejoin tokens[1] onwards
        if (commandTokens.size() > 2)
        {
            for (size_t i = 2; i < commandTokens.size(); ++i)
            {
                noun += " " + commandTokens[i];
            }
        }

        // --- Command Parsing ---
        if (verb == "quit")
        {
            gameRunning = false;
        }
        else if (verb == "help")
        {
            printHelp();
        }
        else if (verb == "look" || verb == "l")
        {
            // Handled at the start of the loop
            continue;
        }
        else if (verb == "inventory" || verb == "i")
        {
            printInventory(playerInventory);
        }
        else if (verb == "go")
        {
            if (noun.empty())
            {
                std::cout << "Go where? (Specify a direction)" << std::endl;
            }
            else
            {
                // Handle single letter directions too
                if (noun == "n")
                    noun = "north";
                else if (noun == "s")
                    noun = "south";
                else if (noun == "e")
                    noun = "east";
                else if (noun == "w")
                    noun = "west";

                Room *nextRoom = currentRoom->getExit(noun);
                if (nextRoom != nullptr)
                {
                    currentRoom = nextRoom;
                    // Room description prints at the top of the next loop iteration
                }
                else
                {
                    std::cout << "You can't go that way." << std::endl;
                }
            }
        }
        else if (verb == "n" || verb == "s" || verb == "e" || verb == "w")
        {
            // Handle single letter directions directly
            std::string direction = verb;
            if (direction == "n")
                direction = "north";
            else if (direction == "s")
                direction = "south";
            else if (direction == "e")
                direction = "east";
            else if (direction == "w")
                direction = "west";

            Room *nextRoom = currentRoom->getExit(direction);
            if (nextRoom != nullptr)
            {
                currentRoom = nextRoom;
            }
            else
            {
                std::cout << "You can't go that way." << std::endl;
            }
        }
        else if (verb == "take")
        {
            if (noun.empty())
            {
                std::cout << "Take what?" << std::endl;
            }
            else
            {
                // Attempt to remove item from room (case-sensitive for now)
                std::optional<Item> removedItemOpt = currentRoom->removeItem(noun); // Using exact name

                if (!removedItemOpt)
                { // Try again with title case for multi-word items
                    std::string titleCaseNoun = noun;
                    if (!titleCaseNoun.empty())
                        titleCaseNoun[0] = std::toupper(titleCaseNoun[0]);
                    for (size_t i = 1; i < titleCaseNoun.length(); ++i)
                    {
                        if (titleCaseNoun[i - 1] == ' ')
                            titleCaseNoun[i] = std::toupper(titleCaseNoun[i]);
                    }
                    removedItemOpt = currentRoom->removeItem(titleCaseNoun);
                }

                if (removedItemOpt.has_value())
                {
                    std::cout << "You take the " << removedItemOpt.value().getName() << "." << std::endl;
                    playerInventory.push_back(std::move(removedItemOpt.value())); // Move item to inventory
                }
                else
                {
                    std::cout << "You don't see a '" << noun << "' here." << std::endl;
                }
            }
        }
        else if (verb == "drop")
        {
            if (noun.empty())
            {
                std::cout << "Drop what?" << std::endl;
            }
            else
            {
                // Find item in inventory (case-insensitive comparison)
                auto it = std::find_if(playerInventory.begin(), playerInventory.end(),
                                       [&](const Item &item)
                                       {
                                           return toLower(item.getName()) == noun;
                                       });

                if (it != playerInventory.end())
                {
                    std::cout << "You drop the " << it->getName() << "." << std::endl;
                    currentRoom->addItem(*it); // Add a copy back to the room
                    playerInventory.erase(it); // Remove from inventory
                }
                else
                {
                    std::cout << "You don't have a '" << noun << "'." << std::endl;
                }
            }
        }
        // Add more commands: look at, use, open, ...
        else
        {
            std::cout << "Unknown command. Try 'help'." << std::endl;
        }
    }

    std::cout << "\nThanks for playing!" << std::endl;

    return 0;
}