include(FetchContent)

FetchContent_Declare(
	"mmap-allocator"
	GIT_REPOSITORY https://github.com/shotowon/mmap-allocator
	GIT_TAG master
	)

FetchContent_MakeAvailable("mmap-allocator")
