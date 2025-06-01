#ifndef ROOM_H
#define ROOM_H

#include "GameObject.h"
#include "Item.h" // Include Item definition
#include <string>
#include <vector>
#include <map>

// Forward declaration for Room to allow Room* in the map value
class Room;

/**
 * @brief Represents a location in the game world.
 */
class Room : public GameObject
{
public:
    // Constructor: Only needs name and description for the GameObject part.
    Room(const std::string &name, const std::string &description);

    // --- Exits ---
    // Add an exit from this room to another room in a given direction.
    void addExit(const std::string &direction, Room *targetRoom);
    // Get the room pointer for a given exit direction, or nullptr if no exit.
    Room *getExit(const std::string &direction) const;
    // Get a description of available exits.
    std::string getExitsDescription() const;

    // --- Items ---
    // Add an item to the room.
    void addItem(const Item &item);
    // Attempt to remove an item by name and return it (or nullopt).
    // Using optional<Item> requires Item to be copyable/movable.
    std::optional<Item> removeItem(const std::string &itemName);
    // Get a description of items currently in the room.
    std::string getItemsDescription() const;

    // --- Room Description ---
    // Provide a full description of the room including exits and items.
    // This overrides the base getDescription for more detail.
    std::string getDescription() const override;

private:
    // Stores items currently in the room.
    std::vector<Item> items_;
    // Stores exits: Key=direction (lowercase), Value=pointer to target room.
    std::map<std::string, Room *> exits_;
};

#endif