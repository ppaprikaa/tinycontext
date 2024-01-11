#include <ctx/context.hpp>
#include <ctx/stack/stack.hpp>
#include <ctx/trampoline.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>

class Trampoline : public ITrampoline {
	public:
	std::function<void()> Routine;

	void Run() noexcept override {
		Routine();
	}
};

int main(int argc, char* argv[]) {
	Stack stack1 = Stack::AllocateBytes(4096);
	Stack stack2 = Stack::AllocateBytes(4096);
	Context current;
	Context target1;
	Context target2;

	Trampoline* core1 = new Trampoline();
	Trampoline* core2 = new Trampoline();
	core1->Routine = [&target1, &target2](){
		std::cout << "Switched from main to target 1" << std::endl;
		std::cout << "Switching to target2" << std::endl;
		target1.SwitchTo(target2);
	};
	core2->Routine = [&target2, &current](){
		std::cout << "Switched from target1" << std::endl;
		std::cout << "Switching to main" << std::endl;
		target2.SwitchTo(current);
	};

	target1.Setup(stack1.MutableView(), core1);
	target2.Setup(stack2.MutableView(), core2);

	std::cout << "Switching to target1" << std::endl;
	current.SwitchTo(target1);
	std::cout << "Switched from target2" << std::endl;

	delete core1;
	delete core2;
	return EXIT_SUCCESS;
}
