#pragma once

template <typename T>
struct singleton_wrapper {
    T& get() noexcept {
        return T::instance();
    }

    const T& get() const noexcept {
        return T::instance();
    }

    T& operator*() noexcept {
        return get();
    }

    const T& operator*() const noexcept {
        return get();
    }

    T* operator->() noexcept {
        return &get();
    }

    const T* operator->() const noexcept {
        return &get();
    }
};
