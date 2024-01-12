#pragma once

struct ITrampoline {
    virtual ~ITrampoline() = default;
    virtual void Run() noexcept = 0;
};
