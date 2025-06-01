#include "GameObject.h"

// Constructor definition
GameObject::GameObject(const std::string &name, const std::string &desc)
    : name(name), description(desc) {};

GameObject::GameObject() : name(""), description("") {};

// Getter implementations
std::string GameObject::getName() const
{
    return name;
}

std::string GameObject::getDescription() const
{
    return description;
}
