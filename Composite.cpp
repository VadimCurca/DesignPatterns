#include <exception>
#include <iostream>
#include <list>
#include <memory>

class Component {
  public:
    virtual void Draw() = 0;
    virtual void PushBack(std::shared_ptr<Component> g) {
        throw "Not implementd";
    }
    virtual void Remove(std::shared_ptr<Component> g) {
        throw "Not implementd";
    }
    virtual ~Component() = default;
};

class Composite : public Component {
  public:
    void Draw() override {
        for (auto it = children.begin(); it != children.end(); it++) {
            (*it)->Draw();
        }
        std::cout << "\n";
    }
    void PushBack(std::shared_ptr<Component> g) override {
        children.push_back(g);
    }
    void Remove(std::shared_ptr<Component> g) override { children.remove(g); }

  private:
    std::list<std::shared_ptr<Component>> children;
};

class Character : public Component {
  public:
    Character(char c) : c(c) {}
    void Draw() override { std::cout << c; }

  private:
    char c;
};

int main() {
    std::shared_ptr<Component> column = std::make_shared<Composite>();
    std::shared_ptr<Component> row1 = std::make_shared<Composite>();
    std::shared_ptr<Component> row2 = std::make_shared<Composite>();

    column->PushBack(row1);
    column->PushBack(row2);

    row1->PushBack(std::make_shared<Character>('a'));
    row1->PushBack(std::make_shared<Character>('b'));
    row2->PushBack(std::make_shared<Character>('c'));
    row2->PushBack(std::make_shared<Character>('d'));
    row2->PushBack(std::make_shared<Character>('e'));

    column->Draw();
}
