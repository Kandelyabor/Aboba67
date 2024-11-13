#include "Stationery.h"
#include "Exception.h"
#include <limits>

Stationery::Stationery()
    : Item(), m_stationeryType(""), m_color(""), m_purpose(""), m_price(0.0) {
    std::cout << "[Stationery] Конструктор по умолчанию" << std::endl;
}

Stationery::Stationery(const std::string& type, const std::string& color,
                       const std::string& purpose, double price)
    : Item(), m_stationeryType(type), m_color(color), m_purpose(purpose), m_price(price) {
    std::cout << "[Stationery] Конструктор с параметрами" << std::endl;
}

Stationery::Stationery(const Stationery& other)
    : Item(other), m_stationeryType(other.m_stationeryType), m_color(other.m_color),
      m_purpose(other.m_purpose), m_price(other.m_price) {
    std::cout << "[Stationery] Конструктор копирования" << std::endl;
}

Stationery::~Stationery() {
    std::cout << "[Stationery] Деструктор (объект: \"" << m_stationeryType << "\")" << std::endl;
}

Stationery& Stationery::operator=(const Stationery& other) {
    std::cout << "[Stationery] Оператор присваивания" << std::endl;
    if (this != &other) {
        Item::operator=(other);
        m_stationeryType = other.m_stationeryType;
        m_color = other.m_color;
        m_purpose = other.m_purpose;
        m_price = other.m_price;
    }
    return *this;
}

std::string Stationery::getStationeryType() const { return m_stationeryType; }
std::string Stationery::getColor() const { return m_color; }
std::string Stationery::getPurpose() const { return m_purpose; }
double Stationery::getPrice() const { return m_price; }

void Stationery::setStationeryType(const std::string& type) { m_stationeryType = type; }
void Stationery::setColor(const std::string& color) { m_color = color; }
void Stationery::setPurpose(const std::string& purpose) { m_purpose = purpose; }
void Stationery::setPrice(double price) {
    if (price < 0.0) throw BookstoreException("Стоимость канцелярии не может быть отрицательной!");
    m_price = price;
}

ItemType Stationery::getType() const { return TYPE_STATIONERY; }
const char* Stationery::getTypeName() const { return "Канцелярия"; }

void Stationery::inputFromConsole() {
    std::cout << "Введите тип канцелярии (например: ручка гелевая): ";
    std::getline(std::cin, m_stationeryType);
    std::cout << "Введите цвет: ";
    std::getline(std::cin, m_color);
    std::cout << "Введите назначение (например: для черчения / письма): ";
    std::getline(std::cin, m_purpose);

    std::cout << "Введите стоимость (руб): ";
    double price;
    if (!(std::cin >> price)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw BookstoreException("Ошибка ввода стоимости канцелярии!");
    }
    setPrice(price);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Stationery::printToConsole() const {
    std::cout << "[Канцелярия] Тип: " << m_stationeryType << ", Цвет: " << m_color 
              << ", Назначение: " << m_purpose << ", Цена: " << m_price << " руб." << std::endl;
}

void Stationery::editConsole() {
    std::cout << "Редактирование канцелярии \"" << m_stationeryType << "\":\n";
    inputFromConsole();
}

void Stationery::saveToFile(std::ofstream& out) const {
    out << TYPE_STATIONERY << "\n";
    out << m_stationeryType << "\n";
    out << m_color << "\n";
    out << m_purpose << "\n";
    out << m_price << "\n";
}

void Stationery::loadFromFile(std::ifstream& in) {
    std::getline(in, m_stationeryType);
    std::getline(in, m_color);
    std::getline(in, m_purpose);
    in >> m_price;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Item* Stationery::clone() const {
    return new Stationery(*this);
}
