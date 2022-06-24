// Подробнее в https://refactoring.guru/ru/design-patterns/adapter

#include <string>
#include <iostream>

class StdInReader {
public:
    virtual std::string read_from_input() const {
        std::string str;
        std::cin >> str;
        return str;
    };
    virtual ~StdInReader() = default;
};

class StringReturner {
private:
    std::string str;
public:
    StringReturner(std::string str): str(str){};
    StringReturner() = delete;
    std::string return_string() const {
        return str;
    };
};

class StdInReaderAdapter : public StdInReader {
public:
    StdInReaderAdapter() = delete;
    StdInReaderAdapter(StringReturner* str_returner): str_returner(str_returner){};
    std::string read_from_input() const override {
        return str_returner->return_string();
    };
private:
    StringReturner* str_returner;
};

void f1(const StdInReader& std_in_reader)
{
    std::cout << "Print something: " << std::endl;
    std::string str = std_in_reader.read_from_input();
    std::cout << "You printed " << str << std::endl;
}

int main() {
    StdInReader std_in_reader;
    f1(std_in_reader);
    StringReturner str_returner("Hello");
    StdInReaderAdapter std_in_reader_adapter(&str_returner);
    f1(std_in_reader_adapter);
    return 0;
}