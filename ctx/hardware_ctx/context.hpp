#pragma once

#include <mmap-allocator/mem-view.hpp>
#include <ctx/trampoline.hpp>

extern "C" void SwitchHardwareContext(void* from, void* to);

struct HardwareContext {
	void* rsp_;
	void Setup(MutableMemView stack, ITrampoline* trampoline);

	void SwitchTo(HardwareContext& target) {
		SwitchHardwareContext(&rsp_, &target.rsp_);
	}

	void* StackPtr() const noexcept {
		return rsp_;
	}
};
