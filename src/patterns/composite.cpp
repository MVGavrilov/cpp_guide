// Подробнее тут: https://refactoring.guru/ru/design-patterns/composite/cpp/example

#include <iostream>
#include <list>
#include <string>
#include <memory>

class Component {
public:
    virtual ~Component() = default;
    virtual void operate() = 0;
    explicit Component(std::string name) : name(name) {}
protected:
    std::string name;
};

class Composite : public Component {
public:
    explicit Composite(std::string name) : Component(name) {}
    void operate() override {
        std::cout << "Composite " << name << ": [";
        for (auto& c : children) {
            c->operate();
            if (c != children.back()) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
    }
    void add(std::shared_ptr<Component> child) {
        children.push_back(child);
    }
    void remove(std::shared_ptr<Component> child) {
        children.remove(child);
    }
    ~Composite() override {
        std::cout << "Composite " << name << " destroyed" << std::endl;
    };
private:
    std::list<std::shared_ptr<Component>> children;
};

class Leaf : public Component {
public:
    explicit Leaf(std::string name) : Component(name) {}
    void operate() override {
        std::cout << "Leaf: " << name;
    }
    ~Leaf() override {
        std::cout << "Leaf " << name << " destroyed" << std::endl;
    };
};



int main() {
    std::shared_ptr<Composite> root(new Composite("root"));
    std::shared_ptr<Composite> c1(new Composite("c1"));
    std::shared_ptr<Composite> c2(new Composite("c2"));
    std::shared_ptr<Leaf> l1(new Leaf("l1"));
    std::shared_ptr<Leaf> l2(new Leaf("l2"));
    std::shared_ptr<Leaf> l3(new Leaf("l3"));
    root->add(c1);
    root->add(c2);
    c1->add(l1);
    c1->add(l2);
    c2->add(l3);
    root->operate();
    std::cout<< std::endl;
    root->remove(c1);
    root->operate();
    std::cout<< std::endl;
    return 0;
}