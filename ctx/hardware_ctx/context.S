.global SetHardwareContext
.global SwitchHardwareContext

SetHardwareContext:
	// temp = current_stack
	// rdi = to_rsp
	// rsi = trampoline
	// rdx = arg 7
	movq %rsp, %r11
	movq %rdi, %rsp

	// for safety
	subq $64, %rsp

	// 16 byte stack alignment
	// don't ask me AMD64 ABI conventions, call stack must be 16 byte aligned
	// last 4 bits to 0
	// 4 bits max == 2^4 - 1 == 15
	// 4 bits <= 15	
	// => zeroing those bits allows us to get a number divisible by 16
	// it means that rsp addr will be divisible by 16
	// ensuring that stack is 16 byte aligned
	// bitwise and between rsp and 0xFFFFFFF0
	// 0xFFFFFFF0 == -16
	// example 4089 & -16 == 4080
	andq $-16, %rsp 

	// just deallocate 8 bytes and set arg as seventh argument
	// arguments after sixth one are pushed to the stack b4 call
	addq $8, %rsp
	movq %rdx, 8(%rsp)

	// push return address
	pushq %rsi

	// push values of callee-saved registers to be popped after
	pushq $0
	pushq $0
	pushq $0
	pushq $0
	pushq $0
	pushq $0

	// set return value as a top of the stack
	movq %rsp, %rax
	
	// return back stack current_stack = temp
	movq %r11, %rsp
	retq

SwitchHardwareContext:
	// push callee-saved registers
    pushq %r15
    pushq %r14
    pushq %r13
    pushq %r12
    pushq %rbx
    pushq %rbp
	
	// switch stacks
	movq %rsp, (%rdi)	
	movq (%rsi), %rsp

	popq %rbp
    popq %rbx
    popq %r12
    popq %r13
    popq %r14
    popq %r15
	// pop callee-saved ones
    retq

