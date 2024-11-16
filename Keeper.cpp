#include "Keeper.h"
#include "Book.h"
#include "Textbook.h"
#include "Stationery.h"
#include "Exception.h"
#include <fstream>

Keeper::Keeper() : m_data(nullptr), m_size(0), m_capacity(0) {
    std::cout << "[Keeper] Конструктор по умолчанию" << std::endl;
    reallocate(4);
}

Keeper::Keeper(int initialCapacity) : m_data(nullptr), m_size(0), m_capacity(0) {
    std::cout << "[Keeper] Конструктор с параметрами (емкость: " << initialCapacity << ")" << std::endl;
    if (initialCapacity <= 0) initialCapacity = 4;
    reallocate(initialCapacity);
}

Keeper::Keeper(const Keeper& other) : m_data(nullptr), m_size(0), m_capacity(0) {
    std::cout << "[Keeper] Конструктор копирования" << std::endl;
    reallocate(other.m_capacity > 0 ? other.m_capacity : 4);
    for (int i = 0; i < other.m_size; ++i) {
        m_data[i] = other.m_data[i]->clone();
    }
    m_size = other.m_size;
}

Keeper::~Keeper() {
    std::cout << "[Keeper] Деструктор" << std::endl;
    clear();
    delete[] m_data;
}

void Keeper::reallocate(int newCapacity) {
    Item** newData = new Item*[newCapacity];
    for (int i = 0; i < m_size; ++i) {
        newData[i] = m_data[i];
    }
    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
}

Keeper& Keeper::operator=(const Keeper& other) {
    std::cout << "[Keeper] Оператор присваивания" << std::endl;
    if (this != &other) {
        clear();
        delete[] m_data;
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;

        reallocate(other.m_capacity > 0 ? other.m_capacity : 4);
        for (int i = 0; i < other.m_size; ++i) {
            m_data[i] = other.m_data[i]->clone();
        }
        m_size = other.m_size;
    }
    return *this;
}

Item* Keeper::operator[](int index) {
    if (index < 0 || index >= m_size) {
        throw BookstoreException("Индекс вне диапазона контейнера Keeper!");
    }
    return m_data[index];
}

const Item* Keeper::operator[](int index) const {
    if (index < 0 || index >= m_size) {
        throw BookstoreException("Индекс вне диапазона контейнера Keeper!");
    }
    return m_data[index];
}

int Keeper::getSize() const { return m_size; }
int Keeper::getCapacity() const { return m_capacity; }

void Keeper::add(Item* item) {
    if (!item) throw BookstoreException("Попытка добавить нулевой указатель в Keeper!");
    if (m_size >= m_capacity) {
        reallocate(m_capacity == 0 ? 4 : m_capacity * 2);
    }
    m_data[m_size++] = item;
}

void Keeper::removeAt(int index) {
    if (index < 0 || index >= m_size) {
        throw BookstoreException("Удаление невозможно: некорректный индекс!");
    }
    delete m_data[index];
    for (int i = index; i < m_size - 1; ++i) {
        m_data[i] = m_data[i + 1];
    }
    --m_size;
}

void Keeper::clear() {
    for (int i = 0; i < m_size; ++i) {
        delete m_data[i];
    }
    m_size = 0;
}

void Keeper::displayAll() const {
    if (m_size == 0) {
        std::cout << ">>> Контейнер пуст. Элементов нет. <<<\n";
        return;
    }
    std::cout << "========= СПИСОК ТОВАРОВ В МАГАЗИНЕ (" << m_size << ") =========\n";
    for (int i = 0; i < m_size; ++i) {
        std::cout << "[" << (i + 1) << "] ";
        m_data[i]->printToConsole();
    }
    std::cout << "================================================\n";
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw BookstoreException("Не удалось открыть файл для записи: " + filename);
    }
    out << m_size << "\n";
    for (int i = 0; i < m_size; ++i) {
        m_data[i]->saveToFile(out);
    }
    out.close();
    std::cout << "Данные успешно сохранены в файл: " << filename << std::endl;
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw BookstoreException("Не удалось открыть файл для чтения: " + filename);
    }
    int count = 0;
    if (!(in >> count)) {
        throw BookstoreException("Файл пуст или поврежден: " + filename);
    }
    clear();
    for (int i = 0; i < count; ++i) {
        int rawType;
        if (!(in >> rawType)) {
            throw BookstoreException("Ошибка чтения типа элемента из файла!");
        }
        in.ignore(10000, '\n');

        Item* newItem = nullptr;
        if (rawType == TYPE_BOOK) {
            newItem = new Book();
        } else if (rawType == TYPE_TEXTBOOK) {
            newItem = new Textbook();
        } else if (rawType == TYPE_STATIONERY) {
            newItem = new Stationery();
        } else {
            throw BookstoreException("Неизвестный тип объекта при чтении файла!");
        }

        newItem->loadFromFile(in);
        add(newItem);
    }
    in.close();
    std::cout << "Данные успешно загружены из файла (" << count << " элементов)." << std::endl;
}
