# TinyContext

Execution context library for my own study purposes.

:warning:

Works only on `x86-64`.

Do not use this, there's no tests, there's no integration of address sanitizer and I barely can code in C++.

But if everything you want is to play, you're welcome

Build steps.
```sh
mkdir build
cmake -S . -B build
cmake --build build
```

Here's simple example
```C++

class Trampoline : public ITrampoline {
  public:
    std::function<void()> Routine;

    void Run() noexcept override { Routine(); }
};

int main(int argc, char *argv[]) {
    Stack stack1 = Stack::AllocateBytes(4096);
    Stack stack2 = Stack::AllocateBytes(4096);
    Context current;
    Context target1;
    Context target2;

    Trampoline *core1 = new Trampoline();
    Trampoline *core2 = new Trampoline();
    core1->Routine = [&target1, &target2]() {
        std::cout << "Switched from target1 to target2" << std::endl;
        target1.SwitchTo(target2);
    };
    core2->Routine = [&target2, &current]() {
        std::cout << "Switched from target2 to main" << std::endl;
        target2.SwitchTo(current);
    };

    target1.Setup(stack1.MutableView(), core1);
    target2.Setup(stack2.MutableView(), core2);

    std::cout << "Switched from main to target 1" << std::endl;
    current.SwitchTo(target1);
    std::cout << "END" << std::endl;

    delete core1;
    delete core2;
    return EXIT_SUCCESS;
}

```

output:
```
Switched from main to target 1
Switched from target1 to target2
Switched from target2 to main
END
```