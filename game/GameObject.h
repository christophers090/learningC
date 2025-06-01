#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

// Base class for any object in the game that has a name and description
class GameObject
{
public:
    // Virtual destructor is crucial for base classes with derived classes
    virtual ~GameObject() = default;

    // Public getters accessible to everyone
    std::string getName() const;
    virtual std::string getDescription() const;

protected:
    // Constructor for derived classes to use
    GameObject(const std::string &name, const std::string &desc);
    GameObject();

    // Member variables inherited by derived classes
    std::string name;
    std::string description;
};

#endif // GAMEOBJECT_H