#include <iostream>
#include <any>
#include <typeinfo>
#include "thread.cpp"

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

int main() {
    std::any i = 10;
    if (typeid(simpleThread::Callable<int>) == i.type()) {
        std::cout << "yes"<< std::endl;
    }

    int x = 10 + std::any_cast<int>(i);
    std::cout << x << std::endl;
    // int a = 10;
    // auto add = [a](int x, int y) {return x+y+a;};
    // std::vector<int(int, int)const> vec;

    // Dog dog;
    // dog.showKind();
    //
    // Animal animal = dog;
    // animal.showKind();
    //
    // Animal *animal1 = &dog;
    // animal1->showKind();
    //
    // Animal &animal2 = dog;
    // animal2.showKind();


    // Animal *animal = new Dog;
    // process(animal);
    // process1(*animal);

    // Animal *animal = new Dog;	// 赋值给父类指针
    // animal->showKind();			// animal
    // Person person;
    // person.doShowKind();
    //
    // Animal animal = person;
    // animal.doShowKind();
    // func(person);
    return 0;
}