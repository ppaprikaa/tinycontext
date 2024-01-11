.global SetHardwareContext
.global SwitchHardwareContext

SetHardwareContext:
	// temp = rsp
	// rdi = to_rsp
	// rsi = trampoline
	// rdx = arg 7
	movq %rsp, %r11
	movq %rdi, %rsp

	// for safety
	subq $64, %rsp

	andq $-16, %rsp
	addq $8, %rsp

	movq %rdx, 8(%rsp)

	pushq %rsi

	pushq $0
	pushq $0
	pushq $0
	pushq $0
	pushq $0
	pushq $0

	movq %rsp, %rax

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

