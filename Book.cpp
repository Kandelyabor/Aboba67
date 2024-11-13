#include "Book.h"
#include "Exception.h"
#include <limits>

Book::Book() 
    : Item(), m_title(""), m_author(""), m_year(0), m_annotation(""), m_genre(""), m_pages(0), m_price(0.0) {
    std::cout << "[Book] Конструктор по умолчанию" << std::endl;
}

Book::Book(const std::string& title, const std::string& author, int year,
           const std::string& annotation, const std::string& genre, int pages, double price)
    : Item(), m_title(title), m_author(author), m_year(year),
      m_annotation(annotation), m_genre(genre), m_pages(pages), m_price(price) {
    std::cout << "[Book] Конструктор с параметрами" << std::endl;
}

Book::Book(const Book& other)
    : Item(other), m_title(other.m_title), m_author(other.m_author), m_year(other.m_year),
      m_annotation(other.m_annotation), m_genre(other.m_genre), m_pages(other.m_pages), m_price(other.m_price) {
    std::cout << "[Book] Конструктор копирования" << std::endl;
}

Book::~Book() {
    std::cout << "[Book] Деструктор (объект: \"" << m_title << "\")" << std::endl;
}

Book& Book::operator=(const Book& other) {
    std::cout << "[Book] Оператор присваивания" << std::endl;
    if (this != &other) {
        Item::operator=(other);
        m_title = other.m_title;
        m_author = other.m_author;
        m_year = other.m_year;
        m_annotation = other.m_annotation;
        m_genre = other.m_genre;
        m_pages = other.m_pages;
        m_price = other.m_price;
    }
    return *this;
}

std::string Book::getTitle() const { return m_title; }
std::string Book::getAuthor() const { return m_author; }
int Book::getYear() const { return m_year; }
std::string Book::getAnnotation() const { return m_annotation; }
std::string Book::getGenre() const { return m_genre; }
int Book::getPages() const { return m_pages; }
double Book::getPrice() const { return m_price; }

void Book::setTitle(const std::string& title) { m_title = title; }
void Book::setAuthor(const std::string& author) { m_author = author; }
void Book::setYear(int year) {
    if (year < 0 || year > 2100) throw BookstoreException("Некорректный год выпуска книги!");
    m_year = year;
}
void Book::setAnnotation(const std::string& annotation) { m_annotation = annotation; }
void Book::setGenre(const std::string& genre) { m_genre = genre; }
void Book::setPages(int pages) {
    if (pages <= 0) throw BookstoreException("Количество страниц должно быть положительным!");
    m_pages = pages;
}
void Book::setPrice(double price) {
    if (price < 0.0) throw BookstoreException("Стоимость не может быть отрицательной!");
    m_price = price;
}

ItemType Book::getType() const { return TYPE_BOOK; }
const char* Book::getTypeName() const { return "Книга"; }

void Book::inputFromConsole() {
    std::cout << "Введите название книги: ";
    std::getline(std::cin, m_title);
    std::cout << "Введите автора книги: ";
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

    std::cout << "Введите аннотацию: ";
    std::getline(std::cin, m_annotation);
    std::cout << "Введите жанр: ";
    std::getline(std::cin, m_genre);

    std::cout << "Введите количество страниц: ";
    int pages;
    if (!(std::cin >> pages)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw BookstoreException("Ошибка ввода количества страниц!");
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

void Book::printToConsole() const {
    std::cout << "[Книга] \"" << m_title << "\", Автор: " << m_author 
              << ", Год: " << m_year << ", Жанр: " << m_genre 
              << ", Стр.: " << m_pages << ", Цена: " << m_price << " руб.\n"
              << "   Аннотация: " << m_annotation << std::endl;
}

void Book::editConsole() {
    std::cout << "Редактирование книги \"" << m_title << "\":\n";
    inputFromConsole();
}

void Book::saveToFile(std::ofstream& out) const {
    out << TYPE_BOOK << "\n";
    out << m_title << "\n";
    out << m_author << "\n";
    out << m_year << "\n";
    out << m_annotation << "\n";
    out << m_genre << "\n";
    out << m_pages << "\n";
    out << m_price << "\n";
}

void Book::loadFromFile(std::ifstream& in) {
    std::getline(in, m_title);
    std::getline(in, m_author);
    in >> m_year;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(in, m_annotation);
    std::getline(in, m_genre);
    in >> m_pages;
    in >> m_price;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Item* Book::clone() const {
    return new Book(*this);
}
