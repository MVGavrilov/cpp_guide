// Подробнее в https://refactoring.guru/ru/design-patterns/abstract-factory

#include <string>
#include <iostream>
#include <chrono>

/*
 * Абстрактный класс содержит интерфейсы взаимодействия с объектами, реализация которых определяется в дочерних классах.
 */

class Chair {
public:
    virtual ~Chair() = default;
    virtual std::string sit() = 0;
};

class ModernChair: public Chair {
public:
    std::string sit() override {
        return "Sitting down on modern chair";
    };
};

class VictorianChair: public Chair {
public:
    std::string sit() override {
        return "Sitting down on victorian chair";
    };
};

class Sofa {
public:
    virtual ~Sofa() = default;
    virtual std::string lay() = 0;
};

class ModernSofa: public Sofa {
    std::string lay() {
        return "Laying down on modern sofa";
    };
};

class VictorianSofa: public Sofa {
    std::string lay() {
        return "Laying down on victorian sofa";
    };
};

class Table {
public:
    virtual ~Table() = default;
    virtual std::string put(std::string obj) = 0;
};

class ModernTable: public Table {
    std::string put(std::string obj) override {
        return "Putting " + obj + " on modern table";
    };
};

class VictorianTable: public Table {
    std::string put(std::string obj) override {
        return "Putting " + obj + " on victorian table";
    };
};

/*
 * Абстрактная фабрика содержит интерфейсы создания абстрактных объектов. Какие конкретно это будут объекты указывается
 * в подклассах.
 */

class FurnitureFactory {
public:
    virtual ~FurnitureFactory() = default;
    virtual Chair* createChair() = 0;
    virtual Sofa* createSofa() = 0;
    virtual Table* createTable() = 0;
};

class ModernFurnitureFactory: public FurnitureFactory {
public:
    Chair * createChair() override {
        return new ModernChair();
    };
    Sofa * createSofa() override {
        return new ModernSofa();
    };
    Table * createTable() override {
        return new ModernTable();
    };
};

class VictorianFurnitureFactory: public FurnitureFactory {
public:
    Chair * createChair() override {
        return new VictorianChair();
    };
    Sofa * createSofa() override {
        return new VictorianSofa();
    };
    Table * createTable() override {
        return new VictorianTable();
    };
};

void createFurniture(FurnitureFactory* factory) {
    Chair *chair = factory->createChair();
    Sofa *sofa = factory->createSofa();
    Table *table = factory->createTable();
    std::cout << chair->sit() << std::endl;
    std::cout << sofa->lay() << std::endl;
    std::cout << table->put("book") << std::endl;
    delete chair;
    delete sofa;
    delete table;
}

int main() {
    /*
     * Зачастую выбор между конкретными фабриками осуществляется в самом начале реализации программы и зависит от
     * среды, в которой программа будет использоваться. Всё остальное тело программы остается неизменным, вне
     * зависимости от того, какая фабрика будет использоваться.
     */
    FurnitureFactory *factory;
    auto time = std::chrono::system_clock::now();
    if (time.time_since_epoch().count() / 5000000 % 2 == 0) { // Тип фабрики меняется каждые 5 секунд
        factory = new ModernFurnitureFactory();
    } else {
        factory = new VictorianFurnitureFactory();
    }
    createFurniture(factory);
    delete factory;

    return 0;
}