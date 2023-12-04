#include <iostream>
#include <string>
#include <vector>

class DrawingAPI {
  public:
    virtual ~DrawingAPI() = default;
    virtual std::string DrawCircle(float x, float y, float radius) const = 0;
};

class DrawingAPI01 : public DrawingAPI {
  public:
    std::string DrawCircle(float x, float y, float radius) const override {
        return "API01.circle at " + std::to_string(x) + ":" +
               std::to_string(y) + " - radius: " + std::to_string(radius);
    }

  private:
    // lots of DrawingAPI01 specific methods and state
};

class DrawingAPI02 : public DrawingAPI {
  public:
    std::string DrawCircle(float x, float y, float radius) const override {
        return "API02.circle at " + std::to_string(x) + ":" +
               std::to_string(y) + " - radius: " + std::to_string(radius);
    }

  private:
    // lots of DrawingAPI02 specific methods and state
};

class Shape {
  public:
    Shape(const DrawingAPI &drawing_api) : drawing_api_(drawing_api) {}
    virtual ~Shape() = default;

    // requests handled by Shape
    virtual float ResizeByPercentage(const float percent) = 0;

    // requests implemented and forwarded using primitives provided by
    // DrawindAPI interface
    virtual std::string Draw() const = 0;

  protected:
    const DrawingAPI &drawing_api_;
};

class CircleShape : public Shape {
  public:
    CircleShape(float x, float y, float radius, const DrawingAPI &drawing_api)
        : Shape(drawing_api), x_(x), y_(y), radius_(radius) {}

    float ResizeByPercentage(const float percent) override {
        return radius_ *= (1.0f + percent / 100.0f);
    }

    std::string Draw() const override {
        return drawing_api_.DrawCircle(x_, y_, radius_);
    }

  private:
    float x_, y_, radius_;
};

int main(int argc, char **argv) {
    const DrawingAPI01 api1{};
    const DrawingAPI02 api2{};
    std::vector<CircleShape> shapes{CircleShape{1.0f, 2.0f, 3.0f, api1},
                                    CircleShape{5.0f, 7.0f, 11.0f, api2}};

    for (auto &shape : shapes) {
        shape.ResizeByPercentage(2.5);
        std::cout << shape.Draw() << std::endl;
    }

    return 0;
}
