#include "room.h"
#include <vector>
#include <optional>
#include <iostream>

Room::Room(const std::string &name, const std::string &desc) : GameObject(name, desc) {};

void Room::listItems() const
{
    for (size_t i = 0; i < items.size(); ++i)
    {
        std::cout << "[" << i + 1 << "]" << " " << items[i].getName() << std::endl;
    }
};

void Room::addItem(const Item &item)
{
    items.push_back(item);
};

std::optional<Item> Room::removeItem(int index)
{
    if (index >= 0 && static_cast<size_t>(index) < items.size())
    {
        auto it = items.begin() + index;

        Item removedItem = std::move(*it);

        items.erase(it);

        return removedItem;
    }
    std::cerr << "Error: Cannot remove item at invalid index " << index << std::endl;
    return std::nullopt;
};

std::string Room::getItemsDescription() const
{
    if (items.empty())
    {
        return "You see nothing here.";
    }
    else
    {
        for (const Item &item : items)
        {
            // std::cout << item.getName() << std::endl; // Should build a string instead
        }
    }
    return "Items description not fully implemented.";
}

void Room::addExit(const std::string &direction, Room *room)
{
    exits[direction] = room;
}

Room *Room::getExit(const std::string &direction) const
{
    auto itr = exits.find(direction);
    if (itr != exits.end())
    {
        return itr->second;
    }
    return nullptr;
}

void Room::getExitsDescription() const
{
    std::cout << "You see exits:" << std::endl;

    for (const auto &pair : exits)
    {
        std::cout << "Direction: " << pair.first << std::endl;
        // std::cout << "Desc: " << pair.second->getDescription(); // Calling getDescription might be too verbose here
    }
}

std::string Room::getDescription() const
{
    return description;
}
