#ifndef STATIONERY_H
#define STATIONERY_H

#include "Item.h"

class Stationery : public Item {
private:
    std::string m_stationeryType; // ручка, тетрадь, линейка и т.д.
    std::string m_color;
    std::string m_purpose;
    double m_price;

public:
    Stationery();
    Stationery(const std::string& type, const std::string& color,
               const std::string& purpose, double price);
    Stationery(const Stationery& other);
    ~Stationery() override;

    Stationery& operator=(const Stationery& other);

    std::string getStationeryType() const;
    std::string getColor() const;
    std::string getPurpose() const;
    double getPrice() const;

    void setStationeryType(const std::string& type);
    void setColor(const std::string& color);
    void setPurpose(const std::string& purpose);
    void setPrice(double price);

    ItemType getType() const override;
    const char* getTypeName() const override;
    void inputFromConsole() override;
    void printToConsole() const override;
    void editConsole() override;
    void saveToFile(std::ofstream& out) const override;
    void loadFromFile(std::ifstream& in) override;
    Item* clone() const override;
};

#endif // STATIONERY_H
