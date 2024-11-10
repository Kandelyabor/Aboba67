#include "Item.h"

Item::Item() {
    std::cout << "[Item] Конструктор по умолчанию" << std::endl;
}

Item::Item(const Item& /*other*/) {
    std::cout << "[Item] Конструктор копирования" << std::endl;
}

Item::~Item() {
    std::cout << "[Item] Деструктор" << std::endl;
}

Item& Item::operator=(const Item& /*other*/) {
    std::cout << "[Item] Оператор присваивания" << std::endl;
    return *this;
}
