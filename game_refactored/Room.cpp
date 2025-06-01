#include "Room.h"
#include <sstream>   // For string stream to build descriptions
#include <algorithm> // For std::find_if
#include <iterator>  // For std::make_move_iterator

/**
 * @brief Construct a new Room object.
 *
 * @param name The name of the room (e.g., "Antechamber").
 * @param description The base description of the room (e.g., "Water drips steadily...").
 */
Room::Room(const std::string &name, const std::string &description)
    : GameObject(name, description) // Initialize base class
{
}

// --- Exit Management ---

void Room::addExit(const std::string &direction, Room *targetRoom)
{
    // Consider converting direction to lowercase here for consistency
    exits_[direction] = targetRoom;
}

Room *Room::getExit(const std::string &direction) const
{
    // Consider converting direction to lowercase here
    auto it = exits_.find(direction);
    if (it != exits_.end())
    {
        return it->second; // Return the Room pointer
    }
    return nullptr; // No exit found in that direction
}

std::string Room::getExitsDescription() const
{
    if (exits_.empty())
    {
        return "There are no obvious exits.";
    }
    std::stringstream ss;
    ss << "Exits:";
    // Use a range-based for loop over the map
    for (const auto &pair : exits_)
    {
        ss << " " << pair.first; // pair.first is the direction (key)
    }
    return ss.str();
}

// --- Item Management ---

void Room::addItem(const Item &item)
{
    items_.push_back(item); // Add a copy of the item
}

std::optional<Item> Room::removeItem(const std::string &itemName)
{
    // Find the item by name (case-sensitive search here)
    auto it = std::find_if(items_.begin(), items_.end(),
                           [&](const Item &item)
                           {
                               return item.getName() == itemName;
                           });

    if (it != items_.end())
    {
        // Found the item
        // Create an optional containing a *moved* copy of the item
        // Moving is efficient if Item supports it, otherwise it copies.
        std::optional<Item> removedItem = std::move(*it);
        items_.erase(it); // Erase the original from the vector
        return removedItem;
    }

    return std::nullopt; // Item not found
}

std::string Room::getItemsDescription() const
{
    if (items_.empty())
    {
        return "You see nothing of interest on the floor.";
    }
    std::stringstream ss;
    ss << "You see here:";
    for (const auto &item : items_)
    {
        ss << " " << item.getName(); // Just list names for brevity
    }
    return ss.str();
}

// --- Full Room Description ---

std::string Room::getDescription() const
{
    // Combine base description with exits and items
    std::stringstream ss;
    ss << GameObject::getDescription() << std::endl; // Get base description
    ss << getItemsDescription() << std::endl;
    ss << getExitsDescription();
    return ss.str();
}