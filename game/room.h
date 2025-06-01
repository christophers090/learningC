#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "item.h"
#include "GameObject.h"

class Room : public GameObject
{
public:
    Room(const std::string &name, const std::string &desc);

    void listItems() const;
    void addItem(const Item &item);
    std::optional<Item> removeItem(int index);

    std::string getItemsDescription() const;

    void addExit(const std::string &direction, Room *room);
    Room *getExit(const std::string &direction) const;

    void getExitsDescription() const;

    std::string getDescription() const override;

private:
    std::map<std::string, Room *> exits;

    std::vector<Item> items;
};

#endif
