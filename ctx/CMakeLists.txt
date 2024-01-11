get_filename_component(LIB_INCLUDE_PATH ".." ABSOLUTE)
get_filename_component(LIB_PATH "." ABSOLUTE)

enable_language(ASM)

add_library(${LIB_TARGET} STATIC 
	hardware_ctx/context.hpp 
	hardware_ctx/context.cpp
	hardware_ctx/context.S
	stack/stack.hpp
	stack/stack.cpp
	context.hpp
	context.cpp
	trampoline.hpp	
	)

target_link_libraries(${LIB_TARGET} PUBLIC "mmap-allocator")
target_include_directories(${LIB_TARGET} PUBLIC ${LIB_INCLUDE_PATH})
