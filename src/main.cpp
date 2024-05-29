#include <iostream>
#include <any>
#include <typeinfo>
#include "task.h"

class Animal{
private:
    std::string kind = "animal";
public:
    virtual void showKind() const = 0;
};

class Dog :public Animal{
private:
    std::string kind = "dog";
public:
    Dog() =default;
    Dog(Dog const &dog) {
        std::cout << "copy" << std::endl;
    }
    void showKind() const {
        std::cout << this->kind << std::endl;
    }
};


void process(Animal *animal) {
    animal->showKind();
}

void process1(Animal &animal) {
    animal.showKind();
}

Dog* createDog() {
    return new Dog;
//    dog->showKind();
//    Dog& tmp = *dog;
//    return dog;
}

int main() {
    auto i = createDog();
    i->showKind();

//    std::any i = 10;
//    if (typeid(simpleThread::Callable<int>) == i.type()) {
//        std::cout << "yes"<< std::endl;
//    }
//
//    int x = 10 + std::any_cast<int>(i);
//    std::cout << x << std::endl;

    return 0;
}