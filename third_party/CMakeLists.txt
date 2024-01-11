include(FetchContent)

FetchContent_Declare(
	"mmap-allocator"
	GIT_REPOSITORY https://github.com/ppaprikaa/mmap-allocator
	GIT_TAG master
	)

FetchContent_MakeAvailable("mmap-allocator")
