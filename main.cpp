#include <iostream>
#include <limits>
#include <string>
#include "Keeper.h"
#include "Book.h"
#include "Textbook.h"
#include "Stationery.h"
#include "Exception.h"

void printMenu() {
    std::cout << "\n================= МЕНЮ УПРАВЛЕНИЯ МАГАЗИНОМ ================\n"
              << "1. Показать все объекты в магазине\n"
              << "2. Добавить новый объект (Книга / Учебник / Канцелярия)\n"
              << "3. Редактировать данные объекта по номеру\n"
              << "4. Удалить объект по номеру\n"
              << "5. Сохранить все данные в файл\n"
              << "6. Загрузить все данные из файла\n"
              << "7. Демонстрация конструкторов копирования и оператора =\n"
              << "0. Выход из программы\n"
              << "Выберите пункт: ";
}

int getIntInput() {
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw BookstoreException("Неверный ввод! Ожидалось целое число.");
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

int main() {
    std::setlocale(LC_ALL, "");
    Keeper store;
    bool running = true;

    while (running) {
        try {
            printMenu();
            int choice = getIntInput();

            switch (choice) {
                case 1: {
                    store.displayAll();
                    break;
                }
                case 2: {
                    std::cout << "\nВыберите тип добавляемого объекта:\n"
                              << "1. Книга художественная\n"
                              << "2. Учебник\n"
                              << "3. Канцелярия\n"
                              << "Выбор: ";
                    int typeChoice = getIntInput();
                    Item* newItem = nullptr;

                    if (typeChoice == 1) {
                        newItem = new Book();
                    } else if (typeChoice == 2) {
                        newItem = new Textbook();
                    } else if (typeChoice == 3) {
                        newItem = new Stationery();
                    } else {
                        throw BookstoreException("Неверный выбор типа объекта!");
                    }

                    newItem->inputFromConsole();
                    store.add(newItem);
                    std::cout << "Элемент успешно добавлен!\n";
                    break;
                }
                case 3: {
                    store.displayAll();
                    if (store.getSize() == 0) break;

                    std::cout << "Введите номер объекта для редактирования (1.." << store.getSize() << "): ";
                    int idx = getIntInput() - 1;
                    store[idx]->editConsole();
                    std::cout << "Элемент обновлен!\n";
                    break;
                }
                case 4: {
                    store.displayAll();
                    if (store.getSize() == 0) break;

                    std::cout << "Введите номер объекта для удаления (1.." << store.getSize() << "): ";
                    int idx = getIntInput() - 1;
                    store.removeAt(idx);
                    std::cout << "Элемент успешно удален!\n";
                    break;
                }
                case 5: {
                    std::cout << "Введите имя файла для сохранения (например, data.txt): ";
                    std::string filename;
                    std::getline(std::cin, filename);
                    if (filename.empty()) filename = "data.txt";
                    store.saveToFile(filename);
                    break;
                }
                case 6: {
                    std::cout << "Введите имя файла для загрузки (например, data.txt): ";
                    std::string filename;
                    std::getline(std::cin, filename);
                    if (filename.empty()) filename = "data.txt";
                    store.loadFromFile(filename);
                    break;
                }
                case 7: {
                    std::cout << "\n--- Тест конструктора копирования и присваивания Keeper ---\n";
                    Keeper storeCopy(store);
                    std::cout << "Создана копия storeCopy. Количество элементов: " << storeCopy.getSize() << "\n";
                    Keeper storeAssigned;
                    storeAssigned = store;
                    std::cout << "Выполнено присваивание storeAssigned = store.\n";
                    break;
                }
                case 0: {
                    std::cout << "Завершение работы программы...\n";
                    running = false;
                    break;
                }
                default:
                    std::cout << "Неизвестный пункт меню. Повторите попытку.\n";
                    break;
            }
        } catch (const BookstoreException& e) {
            std::cout << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "Стандартное исключение: " << e.what() << "\n";
        }
    }

    return 0;
}
