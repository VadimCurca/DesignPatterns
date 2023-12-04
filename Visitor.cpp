#include <initializer_list>
#include <iostream>
#include <memory>

class Car;
class Wheel;
class Engine;

class CarElementVisitor {
  public:
    virtual void visit(Car *) = 0;
    virtual void visit(Wheel *) = 0;
    virtual void visit(Engine *) = 0;
    virtual ~CarElementVisitor() = default;
};

class CarElementPrintVisitor : public CarElementVisitor {
  public:
    void visit(Car *) {
        std::cout << "Visiting Car\n";
        printedElements++;
    }
    void visit(Wheel *) {
        std::cout << "Visiting Wheel\n";
        printedElements++;
    }
    void visit(Engine *) {
        std::cout << "Visiting Engine\n";
        printedElements++;
    }
    // Visitors can accumulate state
    int getPrintedElementsCount() { return printedElements; }

  private:
    int printedElements = 0;
};

class CarElementDriveVisitor : public CarElementVisitor {
    void visit(Car *) { std::cout << "Entering my car\n"; }
    void visit(Wheel *) { std::cout << "Kicking my wheel\n"; }
    void visit(Engine *) { std::cout << "Starting my engine\n"; }
};

class CarElement {
  public:
    virtual void accept(CarElementVisitor *visitor) = 0;
    virtual ~CarElement() = default;
};

class Wheel : public CarElement {
    void accept(CarElementVisitor *visitor) { visitor->visit(this); }
};

class Engine : public CarElement {
    void accept(CarElementVisitor *visitor) { visitor->visit(this); }
};

class Car : public CarElement {
  public:
    Car() {}
    Car(std::initializer_list<std::shared_ptr<CarElement>> elements_)
        : elements(elements_) {}

    void accept(CarElementVisitor *visitor) {
        for (auto &it : elements) {
            it.get()->accept(visitor);
        }
        visitor->visit(this);
    }

  private:
    std::vector<std::shared_ptr<CarElement>> elements;
};

int main() {
    Car car = {std::make_shared<Engine>(), std::make_shared<Wheel>(),
               std::make_shared<Wheel>(), std::make_shared<Car>(),
               std::make_shared<Engine>()};

    CarElementPrintVisitor visitor1;
    CarElementDriveVisitor visitor2;

    car.accept(&visitor1);
    car.accept(&visitor2);

    std::cout << "Printed elements count: "
              << visitor1.getPrintedElementsCount() << "\n";
}
