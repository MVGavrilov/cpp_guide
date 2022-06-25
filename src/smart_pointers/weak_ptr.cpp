//

#include <iostream>
#include <memory>

void check_ptr(std::weak_ptr<int> ptr) {
    if (auto sp = ptr.lock())
        std::cout << *sp << std::endl;
    else
        std::cout << "ptr is expired" << std::endl;
}

int main() {
    std::weak_ptr<int> ptr;
    {
        auto s_ptr = std::make_shared<int>(1);
        ptr = s_ptr;
        check_ptr(ptr);
    }
    check_ptr(ptr);
    return 0;
}