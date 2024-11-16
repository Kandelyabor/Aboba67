#ifndef KEEPER_H
#define KEEPER_H

#include "Item.h"
#include <string>

class Keeper {
private:
    Item** m_data;
    int m_size;
    int m_capacity;

    void reallocate(int newCapacity);

public:
    Keeper();
    explicit Keeper(int initialCapacity);
    Keeper(const Keeper& other);
    ~Keeper();

    Keeper& operator=(const Keeper& other);
    Item* operator[](int index);
    const Item* operator[](int index) const;

    int getSize() const;
    int getCapacity() const;

    void add(Item* item);
    void removeAt(int index);
    void clear();

    void displayAll() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // KEEPER_H
