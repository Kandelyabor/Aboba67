#ifndef BOOK_H
#define BOOK_H

#include "Item.h"

class Book : public Item {
private:
    std::string m_title;
    std::string m_author;
    int m_year;
    std::string m_annotation;
    std::string m_genre;
    int m_pages;
    double m_price;

public:
    Book();
    Book(const std::string& title, const std::string& author, int year,
         const std::string& annotation, const std::string& genre, int pages, double price);
    Book(const Book& other);
    ~Book() override;

    Book& operator=(const Book& other);

    // Get-методы
    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    std::string getAnnotation() const;
    std::string getGenre() const;
    int getPages() const;
    double getPrice() const;

    // Set-методы
    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setYear(int year);
    void setAnnotation(const std::string& annotation);
    void setGenre(const std::string& genre);
    void setPages(int pages);
    void setPrice(double price);

    // Полиморфные методы
    ItemType getType() const override;
    const char* getTypeName() const override;
    void inputFromConsole() override;
    void printToConsole() const override;
    void editConsole() override;
    void saveToFile(std::ofstream& out) const override;
    void loadFromFile(std::ifstream& in) override;
    Item* clone() const override;
};

#endif // BOOK_H
