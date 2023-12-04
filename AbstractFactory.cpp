#include <iostream>
#include <string>

class ScrollBar {
  public:
    virtual std::string kind() = 0;
    virtual ~ScrollBar() = default;
};
class TypeAScrollBar : public ScrollBar {
    std::string kind() { return "Type A Scroll Bar"; }
};
class TypeBScrollBar : public ScrollBar {
    std::string kind() { return "Type B Scroll Bar"; }
};

class Button {
  public:
    virtual std::string kind() = 0;
    virtual ~Button() = default;
};
class TypeAButton : public Button {
    std::string kind() { return "Type A Button"; }
};
class TypeBButton : public Button {
    std::string kind() { return "Type B Button"; }
};

class GUIFactory {
  public:
    virtual ScrollBar *CreateScrollBar() = 0;
    virtual Button *createButton() = 0;
    virtual ~GUIFactory() = default;
};

class TypeAGUIFactory : public GUIFactory {
    ScrollBar *CreateScrollBar() { return new TypeAScrollBar; }
    Button *createButton() { return new TypeAButton; }
};

class TypeBGUIFactory : public GUIFactory {
    ScrollBar *CreateScrollBar() { return new TypeBScrollBar; }
    Button *createButton() { return new TypeBButton; }
};

int main() {
    GUIFactory *guiFactory;
    std::string type = "type A";

    if (type == "type A") {
        guiFactory = new TypeAGUIFactory;
    } else {
        guiFactory = new TypeBGUIFactory;
    }

    ScrollBar *scrollBar = guiFactory->CreateScrollBar();
    Button *button = guiFactory->createButton();

    std::cout << scrollBar->kind() << "\n";
    std::cout << button->kind() << "\n";

    delete scrollBar;
    delete button;
    delete guiFactory;
}
