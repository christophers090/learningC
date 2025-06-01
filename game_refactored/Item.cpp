#include "Item.h"

/**
 * @brief Construct a new Item object.
 *
 * @param name The name of the item (e.g., "Rusty Key").
 * @param description The item's description (e.g., "An old key covered in rust.").
 */
Item::Item(const std::string &name, const std::string &description)
    : GameObject(name, description) // Call the base class constructor
{
    // Item-specific initialization could go here if needed.
}

// If any Item methods were overridden or added, their definitions would go here.
// For example:
// std::string Item::getDescription() const override {
//     return "You examine the " + name_ + ". " + description_;
// }