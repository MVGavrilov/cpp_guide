// Подробнее в https://refactoring.guru/ru/design-patterns/factory-method

#include <string>
#include <iostream>

/*
 * Общий интерфейс создаваемых фабрикой объектов. Реализация интерфейса в дочерних классах.
 */

class Transport {
public:
    virtual ~Transport() = default;

    virtual std::string deliver() = 0;
};

class Ship : public Transport {
public:
    std::string deliver() override {
        return "Sent by ship";
    }
};

class Car : public Transport {
public:
    std::string deliver() override {
        return "Sent by car";
    }
};

/*
 * Класс создателя объявляет фабричный метод создания продукта и имеет в себе базовую бизнес-логику работы с этим самым
 * продуктом. Подклассы могут косвенно изменять эту бизнес-логику, переопределяя фабричный метод и возвращая из него
 * другой тип продукта. Реализация фабричного метода создания продукта осуществляется в дочерних классах
 */

class Logistic {
public:
    virtual ~Logistic() = default;

    /*
     * Тот самый фабричный метод. Он так же может быть определен по-умолчанию
     */
    virtual Transport *createTransport() = 0;

    /*
     * Бизнес-логика, которая не зависит от конкретного типа "продукта", создаваемого фабричным методом
     */
    void sendSomething() {
        Transport *t = createTransport();
        std::cout << "I don't care, what transport is this as client, but: " << t->deliver() << std::endl;
        delete t;
    }
};

/*
 * В дочерних классах "Создателя" переопределяется, по сути, только фабричный метод. Сама бизнес-логика работы с
 * созданными объектами остается той же, и описана она в классе "Создателя"
 */

class CarLogistic : public Logistic {
public:
    Transport *createTransport() override {
        return new Car();
    }
};

class ShipLogistic : public Logistic {
    Transport *createTransport() override {
        return new Ship();
    }
};

/*
 * Клиентский код работает с экземпляром конкретного создателя, хотя и через его базовый интерфейс. Пока клиент
 * продолжает работать с создателем через базовый интерфейс, вы можете передать ему любой подкласс создателя.
 */
void makeSomeLogistic(Logistic *logistic) {
    std::cout << "I use class with factory method and I don't know, what type of logistic i use" << std::endl;
    logistic->sendSomething();
}

int main() {
    std::cout << "Begin:" << std::endl;
    Logistic *logistic1 = new CarLogistic();
    Logistic *logistic2 = new ShipLogistic();
    makeSomeLogistic(logistic1);
    makeSomeLogistic(logistic2);
    delete logistic1;
    delete logistic2;
    std::cout << "End" << std::endl;
}