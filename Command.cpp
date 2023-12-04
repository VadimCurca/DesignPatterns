#include <iostream>
#include <list>
#include <memory>

class MyClass { // Receiver
  public:
    // knows how to perform the operations associated with carrying out a
    // request. Any class may serve as a Receiver.
    void action() { std::cout << "MyClass::action\n"; }
};

class Command {
  public:
    // declares an interface for executing an operation.
    virtual void execute() = 0;
    virtual ~Command() = default;

  protected:
    Command() = default;
};

template <typename Receiver> class SimpleCommand : public Command {
  public:
    typedef void (Receiver::*Action)();
    // defines a binding between a Receiver object and an action.
    SimpleCommand(std::shared_ptr<Receiver> receiver_, Action action_)
        : receiver(receiver_.get()), action(action_) {}
    SimpleCommand(const SimpleCommand &) = delete; // rule of three
    const SimpleCommand &operator=(const SimpleCommand &) = delete;
    // implements execute by invoking the corresponding operation(s) on
    // Receiver.
    virtual void execute() override { (receiver->*action)(); }

  private:
    Receiver *receiver;
    Action action;
};

class ComplexCommand : public Command {
  public:
    ComplexCommand(std::shared_ptr<MyClass> receiver_)
        : receiver(receiver_.get()) {}

    void execute() override {
        // Perform some actions and/or store state before forwarding the request
        // to receiver
        std::cout << "ComplexCommand::execute\n";
        receiver->action();
    }

  private:
    MyClass *receiver;
    // state
};

int main() {
    // The smart pointers prevent memory leaks.
    std::shared_ptr<MyClass> receiver1 = std::make_shared<MyClass>();
    std::shared_ptr<MyClass> receiver2 = std::make_shared<MyClass>();

    std::shared_ptr<Command> command1 =
        std::make_shared<SimpleCommand<MyClass>>(receiver1, &MyClass::action);

    std::shared_ptr<Command> command2 =
        std::make_shared<ComplexCommand>(receiver2);

    command1->execute();
    command2->execute();
}
