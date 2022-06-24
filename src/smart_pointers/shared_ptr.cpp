//

#include <iostream>
#include <memory>
#include <sys/unistd.h>
#include <thread>

class MyClass {
public:
    MyClass(int a): a(a) {
        std::cout << "MyClass created" << std::endl;
    }
    ~MyClass() {
        std::cout << "MyClass destroyed" << std::endl;
    }
    int a;
};

std::ostream &operator<<(std::ostream& os, const MyClass &tmp) {
    return os << "MyClass with a = " << tmp.a << std::endl;
}

void f1(std::shared_ptr<MyClass> ptr)
{
    sleep(2);
    std::cout << *ptr << std::endl;
    sleep(2);
    std::cout << "f1 finished" << std::endl;
}

void f2(std::shared_ptr<MyClass> ptr)
{
    sleep(1);
    std::cout << *ptr << std::endl;
    sleep(1);
    std::cout << "f2 finished" << std::endl;
}

int main() {
    std::shared_ptr<MyClass> ptr(new MyClass(2));
    auto t1 = std::thread(f1, ptr);
    auto t2 = std::thread(f2, ptr);
    ptr.reset();
    std::cout<< "ptr reset" << std::endl;
    t1.join();
    t2.join();
    std::cout << "main finished" << std::endl;
    sleep(1);
    return 0;
}
