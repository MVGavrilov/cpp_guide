// Подробнее в https://refactoring.guru/ru/design-patterns/builder

#include <string>
#include <iostream>
#include <vector>
/*
 * Далее будет написана наиболее полная реализация паттерна Builder, с различными "продуктами" и
 * "директором", который будет использовать классы строителя.
 * Здесь у нас имеется два вида продуктов - машина и инструкция к ней.
 */
class Car {
public:
    std::vector<std::string> parts;
    void getParts() {
        for (auto part : parts) {
            std::cout << part << std::endl;
        }
    }
};

class Instruction {
public:
    std::vector<std::string> instructions;
    void getInstructions() {
        for (auto instruction : instructions) {
            std::cout << instruction << std::endl;
        }
    }
};
/*
 * Общий интерфейс для всех классов строителей. Он определяет методы для создания продуктов.
 */
class Builder {
public:
    virtual ~Builder() = default;
    virtual void addDoors() = 0;
    virtual void addEngine() = 0;
    virtual void addWheels() = 0;
    virtual void reset() = 0;
};

/*
 * Классы для создания машин и инструкций. Они предоставляют интерфейс для создания продуктов
 */

class CarBuilder : public Builder {
private:
    Car *car;
public:
    void reset() {
        if (car) {
            delete car;
        }
        car = new Car();
    }
    ~CarBuilder() override {
        delete car;
    }
    void addDoors() override {
        car->parts.push_back("doors");
    }
    void addEngine() override {
        car->parts.push_back("engine");
    }
    void addWheels() override {
        car->parts.push_back("wheels");
    }
    Car* getCar() {
        return car;
    }
};

class InstructionBuilder : public Builder {
private:
    Instruction *instruction;
public:
    void reset() {
        instruction = new Instruction();
    }
    ~InstructionBuilder() override {
        delete instruction;
    }
    void addDoors() override {
        instruction->instructions.push_back("doors instruction");
    }
    void addEngine() override {
        instruction->instructions.push_back("engine instruction");
    }
    void addWheels() override {
        instruction->instructions.push_back("wheels instruction");
    }
    Instruction* getInstruction() {
        return instruction;
    }
};

/*
 * Класс-директор принимает объект строителя, который далее используется для создания продуктов.
 * Директор может не иметь механизма возвращения полученного объекта, так как эти объекты (как в данном примере)
 * могут относиться к различным классам.
 */

class Director {
private:
    Builder *builder;
public:
    Director(Builder *builder) : builder(builder) {}
    void baseProduct() {
        builder->reset();
        builder->addEngine();
        builder->addWheels();
    };
    void fullProduct() {
        builder->reset();
        builder->addDoors();
        builder->addEngine();
        builder->addWheels();
    };
    Builder *getBuilder() {
        return builder;
    }
};

int main() {
    /*
     * Последовательность операций для создания машин и инструкций к ним идентичны, и несмотря на различия
     * в реализации, для пользователя код создания продукта идентичен. Но так как для машины и инструкции
     * у нас нет общего родительского класса, нужно учитывать тип возвращаемого продукта.
     */
    Director *director = new Director(new CarBuilder());
    director->baseProduct();
    CarBuilder*  carBuilder = dynamic_cast<CarBuilder*>(director->getBuilder());
    Car *car = carBuilder->getCar();
    car->getParts();
    delete car;
    delete director;

    director = new Director(new InstructionBuilder());
    director->fullProduct();
    InstructionBuilder*  instructionBuilder = dynamic_cast<InstructionBuilder*>(director->getBuilder());
    Instruction *instruction = instructionBuilder->getInstruction();
    instruction->getInstructions();
    delete instruction;
    delete director;
    return 0;
}