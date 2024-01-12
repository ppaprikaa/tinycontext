#include <ctx/stack/stack.hpp>

Stack Stack::AllocateBytes(size_t bytes) {
    size_t pages = bytes / MMapMemView::PageSize();
    if (bytes % MMapMemView::PageSize() != 0)
        pages++;

    return Stack::AllocatePages(pages);
}

Stack Stack::AllocatePages(size_t pages) {
    MMapMemView mem = MMapMemView::AllocatePages(pages + 1);
    mem.ProtectPages(0, 1);
    return {std::move(mem)};
}
