#ifndef ITEM_H
#define ITEM_H

#include "GameObject.h"
#include <string>

/**
 * @brief Represents an item that can be picked up, dropped, or used.
 *        Inherits basic properties from GameObject.
 */
class Item : public GameObject
{
public:
    // Constructor: Initializes name and description via GameObject base.
    Item(const std::string &name, const std::string &description);

    // Override base class functions if needed (optional here)
    // std::string getDescription() const override;

    // Item-specific methods can be added later (e.g., use(), isTakable())

    // Destructor is implicitly virtual because base class destructor is virtual.
    // ~Item() override = default; // Can explicitly default it if desired.

private:
    // Item-specific members (e.g., weight, value) could go here.
};

#endif // ITEM_H