#include <iostream>
#include <unordered_map>
#include <string>
#include <limits>

struct RationalNumber {
    double value;

    bool operator==(const RationalNumber& other) const {
        return value == other.value;
    }
};


struct FinancialAsset {
    std::string name;

    // Відвідувач для обробки активу
    virtual void accept(class FinancialAssetVisitor& visitor) = 0;
};

// Хешування для раціональних чисел
struct RationalHash {
    size_t operator()(const RationalNumber& key) const {
        std::hash<double> hasher;
        size_t numeratorHash = hasher(key.value);
        size_t denominatorHash = hasher(1.0 / key.value); // Хеш знаменника

        // Комбінуємо хеші чисельника і знаменника
        return numeratorHash ^ (denominatorHash << 1);
    }
};

using FinanceHashTable = std::unordered_map<RationalNumber, FinancialAsset*, RationalHash>;

// Функція пошуку фінансового активу за ключем
// Повертає вказівник на фінансовий актив або nullptr, якщо актив не знайдено
FinancialAsset* findValue(const FinanceHashTable& hashTable, const RationalNumber& key) {
    auto it = hashTable.find(key);
    if (it != hashTable.end()) {
        return it->second;
    }
    return nullptr;
}

// Функція для видалення фінансового активу за ключем
// Приймає посилання на хеш-таблицю та ключ (раціональне число)
// Повертає true, якщо актив видалено, або false, якщо актив не знайдено
bool removeValue(FinanceHashTable& hashTable, const RationalNumber& key) {
    auto it = hashTable.find(key);
    if (it != hashTable.end()) {
        delete it->second;
        hashTable.erase(it);
        return true;
    }
    return false;
}

// Функція для оновлення фінансового активу за ключем
// Приймає посилання на хеш-таблицю, ключ (раціональне число) та новий фінансовий актив
// Повертає true, якщо актив оновлено, або false, якщо актив не знайдено
bool updateValue(FinanceHashTable& hashTable, const RationalNumber& key, const FinancialAsset& newAsset) {
    auto it = hashTable.find(key);
    if (it != hashTable.end()) {
        *(it->second) = newAsset;
        return true;
    }
    return false;
}
// Функція інтерпретації виразу
bool interpretExpression(const std::string& expression) {
    // Реалізація функції інтерпретації виразу
    // TODO: Додатковий код для інтерпретації виразу
    return false;
}
// Клас FinanceHashTableIterator
class FinanceHashTableIterator {
private:
    using IteratorType = typename FinanceHashTable::const_iterator;

public:
    FinanceHashTableIterator(const FinanceHashTable& hashTable) : iterator(hashTable.begin()), endIterator(hashTable.end()) {}

    void next() {
        ++iterator;
    }
    bool isDone() const {
            return iterator == endIterator;
        }

        const FinancialAsset& currentItem() const {
            return iterator->second;
        }

    private:
        IteratorType iterator;
        IteratorType endIterator;
    };
// Клас FinancialAssetPrinter
class FinancialAssetPrinter {
public:
    void visit(const FinancialAsset& asset) {
        std::cout << "Назва фінансового активу: " << asset.name << std::endl;
    }
};

// Клас Interpreter
class Interpreter {
public:
    double interpret(const std::string& expression) {
        // Повертає результат обчислення
    }
};

// Клас Iterator
class FinanceHashTableIterator {
public:
    bool hasNext() {
    }

    FinancialAsset* next() {
    }
};

// Клас FinancialAssetPrinter
class FinancialAssetPrinter {
public:
    void visit(FinancialAsset& asset) {
        // виведення на екран
    }
};

// Клас FinancialAsset
class StockAsset : public FinancialAsset {
public:
    void accept(FinancialAssetVisitor& visitor) override {
        visitor.visit(*this);
    }
};

// Головна функція
int main() {
    FinanceHashTable financeHashTable;
    Interpreter interpreter;
    FinancialAssetPrinter printer;

    while (true) {
        std::cout << "1. Додати фінансовий актив" << std::endl;
        std::cout << "2. Знайти фінансовий актив" << std::endl;
        std::cout << "3. Видалити фінансовий актив" << std::endl;
        std::cout << "4. Оновити фінансовий актив" << std::endl;
        std::cout << "5. Вийти" << std::endl;
        std::cout << "Виберіть опцію: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            RationalNumber key;
            std::cout << "Введіть ключ (раціональне число): ";
            while (!(std::cin >> key.value) || !isValidNumber(key.value)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Неправильне значення. Введіть ключ ще раз: ";
            }

            StockAsset* asset = new StockAsset();
            std::cout << "Введіть назву фінансового активу: ";
            std::cin.ignore();
            std::getline(std::cin, asset->name);

            financeHashTable[key] = asset;
            std::cout << "Фінансовий актив додано" << std::endl;
        } else if (choice == 2) {
            RationalNumber key;
            std::cout << "Введіть ключ (раціональне число) для пошуку: ";
            while (!(std::cin >> key.value) || !isValidNumber(key.value)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Неправильне значення. Введіть ключ ще раз: ";
            }

            FinancialAsset* result = findValue(financeHashTable, key);
            if (result != nullptr) {
                result->accept(printer);
            } else {
                std::cout << "Фінансовий актив не знайдено" << std::endl;
            }
        } else if (choice == 3) {
            RationalNumber key;
            std::cout << "Введіть ключ (раціональне число) для видалення: ";
            while (!(std::cin >> key.value) || !isValidNumber(key.value)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Неправильне значення. Введіть ключ ще раз: ";
            }

            if (removeValue(financeHashTable, key)) {
                std::cout << "Фінансовий актив видалено" << std::endl;
            } else {
                std::cout << "Фінансовий актив не знайдено" << std::endl;
            }
        } else if (choice == 4) {
            RationalNumber key;
            std::cout << "Введіть ключ (раціональне число) для оновлення: ";
            while (!(std::cin >> key.value) || !isValidNumber(key.value)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Неправильне значення. Введіть ключ ще раз: ";
            }

            FinancialAsset* existingAsset = findValue(financeHashTable, key);
            if (existingAsset != nullptr) {
                StockAsset newAsset;
                std::cout << "Введіть нову назву фінансового активу: ";
                std::cin.ignore();
                std::getline(std::cin, newAsset.name);

                if (updateValue(financeHashTable, key, newAsset)) {
                    std::cout << "Фінансовий актив оновлено" << std::endl;
                } else {
                    std::cout << "Помилка при оновленні фінансового активу" << std::endl;
                }
            } else {
                std::cout << "Фінансовий актив не знайдено" << std::endl;
            }
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Невідома опція. Спробуйте ще раз." << std::endl;
        }

        std::cout << std::endl;
    }

    // Видалення фінансових активів
    for (auto& item : financeHashTable) {
        delete item.second;
    }

    return 0;
}

