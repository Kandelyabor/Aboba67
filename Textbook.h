#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include "Item.h"

class Textbook : public Item {
private:
    std::string m_title;
    std::string m_author;
    int m_year;
    std::string m_institution;
    int m_studyYear; // класс или курс
    int m_pages;
    double m_price;

public:
    Textbook();
    Textbook(const std::string& title, const std::string& author, int year,
             const std::string& institution, int studyYear, int pages, double price);
    Textbook(const Textbook& other);
    ~Textbook() override;

    Textbook& operator=(const Textbook& other);

    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    std::string getInstitution() const;
    int getStudyYear() const;
    int getPages() const;
    double getPrice() const;

    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setYear(int year);
    void setInstitution(const std::string& inst);
    void setStudyYear(int studyYear);
    void setPages(int pages);
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

#endif // TEXTBOOK_H
