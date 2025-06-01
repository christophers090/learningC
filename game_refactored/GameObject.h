#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector> // Included for potential use by derived classes

/**
 * @brief Base class for all entities in the game world that have
 *        a name and a description.
 */
class GameObject
{
public:
    // Constructor: Takes name and description.
    GameObject(const std::string &name, const std::string &description);

    // Virtual destructor: Essential for base classes with derived types.
    virtual ~GameObject() = default;

    // Common getters (const indicates they don't modify the object).
    virtual std::string getName() const;
    virtual std::string getDescription() const;

    // Allow changing description (optional, could be protected/removed)
    // Made virtual in case derived classes want specialized setting logic.
    virtual void setDescription(const std::string &description);

protected:
    // Protected members are accessible by derived classes (Item, Room).
    std::string name_;
    std::string description_;

private:
    // No private members currently needed.
};

#endif // GAMEOBJECT_H