#include "GameObject.h"

GameObject::GameObject(const std::string &name, const std::string &description)
    : name_(name), description_(description) {}

// Default implementations for getters/setters.
// Derived classes can override these if needed.

std::string GameObject::getName() const
{
    return name_;
}

std::string GameObject::getDescription() const
{
    return description_;
}

void GameObject::setDescription(const std::string &description)
{
    description_ = description;
}