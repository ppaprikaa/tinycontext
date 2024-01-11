#pragma once

#include <mmap-allocator/mem-view.hpp>
#include <mmap-allocator/allocator.hpp>

class Stack {
	public:
		Stack() = delete;

		static Stack AllocateBytes(size_t bytes);

		void* LowerBound() const noexcept {
			return (void*)(mem_.Start() + MMapMemView::PageSize());
		}

		size_t Size() const noexcept {
			return mem_.Size();
		}

		MutableMemView MutableView() const noexcept {
			return mem_.MutableView();
		}

		MutableMemView Release() {
			return mem_.Release();
		}

		static Stack Acquire(MutableMemView view) {
			return {MMapMemView::Acquire(view)};
		}
	private:
		Stack(MMapMemView mem) : mem_(std::move(mem)) {};
		static Stack AllocatePages(size_t pages);
	private:
		MMapMemView mem_;	
};
