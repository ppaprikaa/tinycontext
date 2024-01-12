#pragma once

#include <ctx/hardware_ctx/context.hpp>
#include <ctx/trampoline.hpp>
#include <mmap-allocator/mem-view.hpp>

class Context : public ITrampoline {
  public:
    Context(){};

    Context(const Context &) = delete;
    Context &operator=(const Context &) = delete;
    Context(Context &&) = delete;
    Context &operator=(Context &&) = delete;

    void Setup(MutableMemView stack, ITrampoline *trampoline);
    void SwitchTo(Context &target);

    void *StackPtr() const noexcept { return hw_.StackPtr(); }

  private:
    void Run() noexcept override { trampoline_->Run(); }

  private:
    ITrampoline *trampoline_;
    HardwareContext hw_;
};
