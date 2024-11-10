#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <fstream>
#include <string>

enum ItemType {
    TYPE_BOOK = 1,
    TYPE_TEXTBOOK = 2,
    TYPE_STATIONERY = 3
};

class Item {
public:
    Item();
    Item(const Item& other);
    virtual ~Item();

    virtual Item& operator=(const Item& other);

    virtual ItemType getType() const = 0;
    virtual const char* getTypeName() const = 0;

    virtual void inputFromConsole() = 0;
    virtual void printToConsole() const = 0;
    virtual void editConsole() = 0;

    virtual void saveToFile(std::ofstream& out) const = 0;
    virtual void loadFromFile(std::ifstream& in) = 0;

    virtual Item* clone() const = 0;
};

#endif // ITEM_H
