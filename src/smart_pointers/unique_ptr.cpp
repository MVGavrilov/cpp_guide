//

#include <iostream>
#include <memory>

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

void my_func(std::unique_ptr<MyClass> ptr)
{
    std::cout << *ptr << std::endl;
}

int main() {
    std::unique_ptr<MyClass> ptr(new MyClass(1));
    std::cout << "Before function call" << std::endl;
    my_func(std::move(ptr));
    std::cout << "After function call" << std::endl;

    return 0;
}
