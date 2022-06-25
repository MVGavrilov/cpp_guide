#include <iostream>

class A {
public:
    A() {
        std::cout << "A()" << std::endl;
    }

    ~A() {
        std::cout << "~A()" << std::endl;
    }
};

class B : public A {
public:
    B() {
        std::cout << "B()" << std::endl;
    }

    ~B() {
        std::cout << "~B()" << std::endl;
    }
};

class C {
public:
    C() {
        std::cout << "C()" << std::endl;
    }

    virtual ~C() {
        std::cout << "~C()" << std::endl;
    }
};

class D : public C {
public:
    D() {
        std::cout << "D()" << std::endl;
    }

    ~D() override {
        std::cout << "~D()" << std::endl;
    }
};

int main() {
    {
        B b;
        D d;
    }
    std::cout << "----" << std::endl;
    A *a = new B;
    delete a;
    C *c = new D;
    delete c;
}