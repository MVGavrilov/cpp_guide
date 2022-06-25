// Подробнее в https://refactoring.guru/ru/design-patterns/prototype

#include <string>
#include <iostream>

class Robot {
protected:
    std::string name;
public:
    explicit Robot(const std::string &name) : name(name) {}

    virtual ~Robot() = default;

    virtual Robot *clone() = 0;

    virtual std::string voice() = 0;
};

class RoboDog : public Robot {
public:
    explicit RoboDog(const std::string &name) : Robot(name) {} //Пример делегирующего конструктора
    Robot *clone() override {
        return new RoboDog(*this);
    }

    std::string voice() override {
        return name + " says 'Woof'";
    }
};

class RoboCat : public Robot {
public:
    explicit RoboCat(const std::string &name) : Robot(name) {}

    Robot *clone() override {
        return new RoboCat(*this);
    }

    std::string voice() override {
        return name + " says 'Meow'";
    }
};

int main() {
    Robot *animal1 = new RoboDog("Sharik");
    Robot *animal2 = new RoboCat("Murka");
    /*
     * Мы не знаем, какой тип животного реализует интерфейс Robot, но функция clone() позволяет
     * нам об этом не задумываться
     */
    Robot *animal1_copy = animal1->clone();
    Robot *animal2_copy = animal2->clone();

    std::cout << animal1->voice() << std::endl;
    std::cout << animal2->voice() << std::endl;
    std::cout << animal1_copy->voice() << std::endl;
    std::cout << animal2_copy->voice() << std::endl;

    delete animal1;
    delete animal2;
    delete animal1_copy;
    delete animal2_copy;
    return 0;
}

