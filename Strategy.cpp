#include <exception>
#include <iostream>
#include <list>
#include <memory>

class Compositor {
  public:
    virtual int Compose(int natural[], int stretch[], int shrink[],
                        int componentCount, int lineWidth, int breaks[]) = 0;
    virtual ~Compositor() = default;
};

class SimpleCompositor : public Compositor {
  public:
    int Compose(int natural[], int stretch[], int shrink[], int componentCount,
                int lineWidth, int breaks[]) override {
        return 0;
    };
    // ...
};

class TeXCompositor : public Compositor {
  public:
    int Compose(int natural[], int stretch[], int shrink[], int componentCount,
                int lineWidth, int breaks[]) override {
        return 0;
    };
    // ...
};

class ArrayCompositor : public Compositor {
  public:
    int Compose(int natural[], int stretch[], int shrink[], int componentCount,
                int lineWidth, int breaks[]) override {
        return 0;
    };
    // ...
};

class Component {};

class Composition {
  public:
    Composition(std::shared_ptr<Compositor> compositor)
        : _compositor(compositor){};
    void Repair();

  private:
    std::shared_ptr<Compositor> _compositor;
    Component *_components; // the list of components
    int _componentCount;    // the number of components
    int _lineWidth;         // the Composition's line width
    int *_lineBreaks;       // the position of linebreaks
                            // in components
    int _lineCount;         // the number of lines
};

void Composition::Repair() {
    int *natural;
    int *stretchability;
    int *shrinkability;
    int componentCount;
    int *breaks;

    // prepare the arrays with the desired component sizes
    // ...

    // determine where the breaks are:
    int breakCount;
    breakCount = _compositor->Compose(natural, stretchability, shrinkability,
                                      componentCount, _lineWidth, breaks);

    // lay out components according to breaks
    // ...
}

int main() {
    Composition quick(std::make_shared<SimpleCompositor>());
    Composition slick(std::make_shared<TeXCompositor>());
    Composition iconic(std::make_shared<ArrayCompositor>());
}
