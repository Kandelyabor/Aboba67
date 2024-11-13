#include "Textbook.h"
#include "Exception.h"
#include <limits>

Textbook::Textbook()
    : Item(), m_title(""), m_author(""), m_year(0), m_institution(""), m_studyYear(1), m_pages(0), m_price(0.0) {
    std::cout << "[Textbook] Конструктор по умолчанию" << std::endl;
}

Textbook::Textbook(const std::string& title, const std::string& author, int year,
                   const std::string& institution, int studyYear, int pages, double price)
    : Item(), m_title(title), m_author(author), m_year(year),
      m_institution(institution), m_studyYear(studyYear), m_pages(pages), m_price(price) {
    std::cout << "[Textbook] Конструктор с параметрами" << std::endl;
}

Textbook::Textbook(const Textbook& other)
    : Item(other), m_title(other.m_title), m_author(other.m_author), m_year(other.m_year),
      m_institution(other.m_institution), m_studyYear(other.m_studyYear), m_pages(other.m_pages), m_price(other.m_price) {
    std::cout << "[Textbook] Конструктор копирования" << std::endl;
}

Textbook::~Textbook() {
    std::cout << "[Textbook] Деструктор (объект: \"" << m_title << "\")" << std::endl;
}

Textbook& Textbook::operator=(const Textbook& other) {
    std::cout << "[Textbook] Оператор присваивания" << std::endl;
    if (this != &other) {
        Item::operator=(other);
        m_title = other.m_title;
        m_author = other.m_author;
        m_year = other.m_year;
        m_institution = other.m_institution;
        m_studyYear = other.m_studyYear;
        m_pages = other.m_pages;
        m_price = other.m_price;
    }
    return *this;
}

std::string Textbook::getTitle() const { return m_title; }
std::string Textbook::getAuthor() const { return m_author; }
int Textbook::getYear() const { return m_year; }
std::string Textbook::getInstitution() const { return m_institution; }
int Textbook::getStudyYear() const { return m_studyYear; }
int Textbook::getPages() const { return m_pages; }
double Textbook::getPrice() const { return m_price; }

void Textbook::setTitle(const std::string& title) { m_title = title; }
void Textbook::setAuthor(const std::string& author) { m_author = author; }
void Textbook::setYear(int year) {
    if (year < 0 || year > 2100) throw BookstoreException("Некорректный год выпуска учебника!");
    m_year = year;
}
void Textbook::setInstitution(const std::string& inst) { m_institution = inst; }
void Textbook::setStudyYear(int studyYear) {
    if (studyYear <= 0 || studyYear > 15) throw BookstoreException("Некорректный год обучения (класс/курс: 1..15)!");
    m_studyYear = studyYear;
}
void Textbook::setPages(int pages) {
    if (pages <= 0) throw BookstoreException("Количество страниц учебника должно быть больше нуля!");
    m_pages = pages;
}
void Textbook::setPrice(double price) {
    if (price < 0.0) throw BookstoreException("Стоимость учебника не может быть отрицательной!");
    m_price = price;
}

ItemType Textbook::getType() const { return TYPE_TEXTBOOK; }
const char* Textbook::getTypeName() const { return "Учебник"; }

void Textbook::inputFromConsole() {
    std::cout << "Введите название учебника: ";
    std::getline(std::cin, m_title);
    std::cout << "Введите автора учебника: ";
    std::getline(std::cin, m_author);
    std::cout << "Введите год выпуска: ";
    int year;
    if (!(std::cin >> year)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw BookstoreException("Ошибка ввода числа для года!");
    }
    setYear(year);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Для какого учебного заведения предназначено (школа, вуз и т.д.): ";
    std::getline(std::cin, m_institution);

    std::cout << "Введите год обучения (класс / курс): ";
    int sYear;
    if (!(std::cin >> sYear)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw BookstoreException("Ошибка ввода года обучения!");
    }
    setStudyYear(sYear);

    std::cout << "Введите объем страниц: ";
    int pages;
    if (!(std::cin >> pages)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw BookstoreException("Ошибка ввода страниц!");
    }
    setPages(pages);

    std::cout << "Введите стоимость (руб): ";
    double price;
    if (!(std::cin >> price)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw BookstoreException("Ошибка ввода стоимости!");
    }
    setPrice(price);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Textbook::printToConsole() const {
    std::cout << "[Учебник] \"" << m_title << "\", Автор: " << m_author 
              << ", Год: " << m_year << ", Для: " << m_institution 
              << ", Курс/Класс: " << m_studyYear << ", Стр.: " << m_pages 
              << ", Цена: " << m_price << " руб." << std::endl;
}

void Textbook::editConsole() {
    std::cout << "Редактирование учебника \"" << m_title << "\":\n";
    inputFromConsole();
}

void Textbook::saveToFile(std::ofstream& out) const {
    out << TYPE_TEXTBOOK << "\n";
    out << m_title << "\n";
    out << m_author << "\n";
    out << m_year << "\n";
    out << m_institution << "\n";
    out << m_studyYear << "\n";
    out << m_pages << "\n";
    out << m_price << "\n";
}

void Textbook::loadFromFile(std::ifstream& in) {
    std::getline(in, m_title);
    std::getline(in, m_author);
    in >> m_year;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(in, m_institution);
    in >> m_studyYear;
    in >> m_pages;
    in >> m_price;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Item* Textbook::clone() const {
    return new Textbook(*this);
}
