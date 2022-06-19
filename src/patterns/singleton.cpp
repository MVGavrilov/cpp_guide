// Подробнее в https://refactoring.guru/ru/design-patterns/singleton

#include <iostream>

class Singleton
{
public:
    static Singleton* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Singleton();
        }
        return instance;
    }

    void operator=(const Singleton&) = delete;
    Singleton(const Singleton&) = delete;

    void doSomething()
    {
        std::cout<<"Singleton did something "<<++counter<<" times"<<std::endl;
    }

    ~Singleton()
    {
        delete instance;
    }
private:
    Singleton() = default;
    static Singleton* instance;
    int counter = 0;
};

Singleton* Singleton::instance = nullptr;

int main() {
    Singleton *s1 = Singleton::getInstance();
    s1->doSomething();
    Singleton *s2 = Singleton::getInstance();
    s2->doSomething();
    return 0;
}