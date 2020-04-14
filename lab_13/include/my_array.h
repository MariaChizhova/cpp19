#ifndef LAB_13_MY_ARRAY_H
#define LAB_13_MY_ARRAY_H

#include <cstddef>
#include <assert.h>
#include <cstdint>
#include <climits>

namespace lab_13 {
    template<typename T, std::size_t N>
    class my_array {
    private:
        T array_[N];
    public:
        const T &at(std::size_t index) const {
            assert(0 <= index && index < N);
            return array_[index];
        }

        T &at(std::size_t index) {
            assert(0 <= index && index < N);
            return array_[index];
        }

        T &operator[](std::size_t index) {
            return array_[index];
        }

        const T &operator[](std::size_t index) const {
            return array_[index];
        }

        bool empty() const {
            return !N;
        }

        std::size_t size() const {
            return N;
        }

        void fill(T val) {
            for (std::size_t i = 0; i < N; i++)
                array_[i] = val;
        }
    };

    template<std::size_t N>
    class my_array<bool, N> {
    private:
        class _proxy {
        public:
            _proxy(uint8_t *byte, std::size_t index) : byte(byte), index(index) {}

            _proxy &operator=(_proxy other) {
                return *this = bool(other);
            }

            _proxy &operator=(bool value) {
                *byte &= ~(1 << index);
                *byte |= ((int) value) << index;
                return *this;
            }

            operator bool() const {
                return bool((*byte >> index) & 1);
            }

            uint8_t *byte;
            std::size_t index;
        };

        static const std::size_t size_ = (N - 1 + CHAR_BIT) / CHAR_BIT;
        uint8_t array_[size_];

    public:
        my_array() {
            for (std::size_t i = 0; i < size_; i++)
                array_[i] = 0;
        }

        _proxy at(std::size_t index) {
            assert(0 <= index && index < N);
            return operator[](index);
        }

        bool at(std::size_t index) const {
            assert(0 <= index && index < N);
            return operator[](index);
        }

        _proxy operator[](std::size_t index) {
            return _proxy(array_ + (index / CHAR_BIT), index % CHAR_BIT);
        }

        bool operator[](std::size_t index) const {
            bool value = (array_[index / CHAR_BIT] >> (index % CHAR_BIT)) & 1;
            return value;
        }

        bool empty() const {
            return !N;
        }

        std::size_t size() const {
            return N;
        }

        void fill(const bool val) {
            for (std::size_t i = 0; i < size_; i++)
                array_[i] = val ? -1 : 0;
        }
    };

}  // namespace lab_13

#endif //LAB_13_MY_ARRAY_H
