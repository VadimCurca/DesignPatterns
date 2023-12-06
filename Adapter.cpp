/**
 * The Target defines the domain-specific interface used by the client code.
 */
#include <iostream>
class Target {
  public:
    virtual ~Target() = default;

    virtual std::string Request() const {
        return "Target: The default target's behavior.";
    }
};

/**
 * The Adaptee contains some useful behavior, but its interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 */
class Adaptee {
  public:
    std::string SpecificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

/**
 * The Adapter makes the Adaptee's interface compatible with the Target's
 * interface.
 */

class ObjectAdapter : public Target {
  private:
    Adaptee *adaptee_;

  public:
    ObjectAdapter(Adaptee *adaptee) : adaptee_(adaptee) {}
    std::string Request() const override {
        std::string to_reverse = this->adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "ObjectAdapter: (TRANSLATED) " + to_reverse;
    }
};

class ClassAdapter : public Target, private Adaptee {
  public:
    std::string Request() const override {
        std::string to_reverse = Adaptee::SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "ClassAdapter: (TRANSLATED) " + to_reverse;
    }
};

/**
 * The client code supports all classes that follow the Target interface.
 */
void ClientCode(const Target *target) { std::cout << target->Request(); }

int main() {
    std::cout << "Client: I can work just fine with the Target objects:\n";
    Target *target = new Target;
    ClientCode(target);
    std::cout << "\n\n";
    Adaptee *adaptee = new Adaptee;
    std::cout << "Client: The Adaptee class has a weird interface. See, I "
                 "don't understand it:\n";
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "\n\n";
    std::cout << "Client: But I can work with it via the ObjectAdapter:\n";
    ObjectAdapter *objectAdapter = new ObjectAdapter(adaptee);
    ClientCode(objectAdapter);
    std::cout << "\n\n";
    std::cout << "Client: Or I can work with it via the ClassAdapter:\n";
    ClassAdapter *classAdapter = new ClassAdapter();
    ClientCode(classAdapter);
    std::cout << "\n";

    delete target;
    delete adaptee;
    delete objectAdapter;
    delete classAdapter;

    return 0;
}
