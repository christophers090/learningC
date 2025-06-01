#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "GameObject.h"

class Item : public GameObject
{
public:
    Item(const std::string &name, const std::string &desc);

private:
};

#endif