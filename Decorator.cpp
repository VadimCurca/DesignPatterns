#include <iostream>
#include <memory>
#include <string>

class VisualComponent {
  public:
    virtual void Draw() = 0;
    virtual void Resize() = 0;
    virtual ~VisualComponent() = default;
};

class TextView : public VisualComponent {
  public:
    virtual void Draw() override { std::cout << "Draw\n"; }
    virtual void Resize() override { std::cout << "Resize\n"; }
};

class Decorator : public VisualComponent {
  public:
    Decorator(std::shared_ptr<VisualComponent> component)
        : _component(component){};

    virtual void Draw() { _component->Draw(); }
    virtual void Resize() { _component->Resize(); }

  private:
    std::shared_ptr<VisualComponent> _component;
};

class BorderDecorator : public Decorator {
  public:
    BorderDecorator(std::shared_ptr<VisualComponent> component, int borderWidth)
        : Decorator(component), _width(borderWidth){};

    virtual void Draw() override {
        Decorator::Draw();
        DrawBorder(_width);
    }

  private:
    void DrawBorder(int width) { std::cout << "Border\n"; }

  private:
    int _width;
};

int main() {
    std::shared_ptr<VisualComponent> textView = std::make_shared<TextView>();
    std::shared_ptr<VisualComponent> decoratedTextView =
        std::make_shared<BorderDecorator>(textView, 5);

    textView->Draw();
    decoratedTextView->Draw();
}
