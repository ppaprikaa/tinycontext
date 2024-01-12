#include <ctx/hardware_ctx/context.hpp>

extern "C" void *SetHardwareContext(void *stack, void *trampoline, void *arg);

void HardwareContextTrampoline(void *, void *, void *, void *, void *, void *,
                               void *arg7) {
    ITrampoline *t = (ITrampoline *)arg7;
    t->Run();
}

void HardwareContext::Setup(MutableMemView stack, ITrampoline *trampoline) {
    rsp_ = SetHardwareContext((void *)stack.End(),
                              (void *)HardwareContextTrampoline, trampoline);
}
