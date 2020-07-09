#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>

namespace linq {
    namespace impl {

        template<typename T, typename Iter>
        class range_enumerator;

        template<typename T>
        class drop_enumerator;

        template<typename T, typename U, typename F>
        class select_enumerator;

        template<typename T, typename F>
        class until_enumerator;

        template<typename T, typename F>
        class where_enumerator;

        template<typename T>
        class take_enumerator;

        template<typename T>
        class enumerator {
        public:
            virtual const T &operator*() = 0; // Получает текущий элемент.
            virtual enumerator &operator++() = 0;  // Переход к следующему элементу
            virtual operator bool() const = 0;  // Возвращает true, если есть текущий элемент

            auto drop(int count) {
                return drop_enumerator<T>(*this, count);
            }

            auto take(int count) {
                return take_enumerator<T>(*this, count);
            }

            template<typename U = T, typename F>
            auto select(F func) {
                return select_enumerator<U, T, F>(*this, func);
            }

            template<typename F>
            auto until(F func) {
                return until_enumerator<T, F>(*this, func);
            }

            auto until_eq(T value) {
                return until([value](T x) { return x == value; });
            }

            template<typename F>
            auto where(F func) {
                return where_enumerator<T, F>(*this, func);
            }

            auto where_neq(T value) {
                return where([value](T x) { return x != value; });
            }

            std::vector<T> to_vector() {
                std::vector<T> res;
                while (*this) {
                    res.push_back(**this);
                    ++*this;
                }
                return res;
            }

            template<typename Iter>
            void copy_to(Iter it) {
                while (*this) {
                    *it = **this;
                    ++it;
                    ++*this;
                }
            }
        };

        template<typename T, typename Iter>
        class range_enumerator : public enumerator<T> {
        public:
            range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

            const T &operator*() override {
                return *begin_;
            }

            enumerator<T> &operator++() override {
                ++begin_;
                return *this;
            }

            operator bool() const override {
                return begin_ != end_;
            }

        private:
            Iter begin_, end_;
        };

        template<typename T>
        class drop_enumerator : public enumerator<T> {
        public:
            drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
                while (parent_ && count) {
                    ++parent_;
                    --count;
                }
            }

            const T &operator*() override {
                return *parent_;
            }

            enumerator<T> &operator++() override {
                ++parent_;
                return *this;
            }

            operator bool() const override {
                return static_cast<bool>(parent_);
            }

        private:
            enumerator<T> &parent_;
        };

        template<typename T>
        class take_enumerator : public enumerator<T> {
        public:
            take_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}

            const T &operator*() override {
                return *parent_;
            }

            enumerator<T> &operator++() override {
                ++parent_;
                --count_;
                return *this;
            }

            operator bool() const override {
                return parent_ && count_ > 0;
            }

        private:
            enumerator<T> &parent_;
            int count_;
        };

        template<typename T, typename U, typename F>
        class select_enumerator : public enumerator<T> {
        public:
            select_enumerator(enumerator<U> &parent, F func) : parent_(parent), func_(func) {}

            const T &operator*() {
                return last_ = func_(*parent_);
            }

            select_enumerator &operator++() {
                ++parent_;
                return *this;
            }

            operator bool() const {
                return static_cast<bool>(parent_);
            }

        private:
            enumerator<U> &parent_;
            F func_;
            T last_;
        };

        template<typename T, typename F>
        class until_enumerator : public enumerator<T> {
        public:
            until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), predicate_(predicate) {}

            const T &operator*() override {
                return *parent_;
            }

            enumerator<T> &operator++() override {
                ++parent_;
                return *this;
            }

            operator bool() const override {
                return parent_ && !predicate_(*parent_);
            }

        private:
            enumerator<T> &parent_;
            F predicate_;
        };

        template<typename T, typename F>
        class where_enumerator : public enumerator<T> {
        public:
            where_enumerator(enumerator<T> &parent, F &predicate) : parent_(parent), predicate_(std::move(predicate)) {
                while (parent_ && !predicate_(*parent_))
                    ++parent_;
            }

            const T &operator*() override {
                return *parent_;
            }

            enumerator<T> &operator++() override {
                while (++parent_ && !predicate_(*parent_));
                return *this;
            }

            operator bool() const override {
                return static_cast<bool>(parent_);
            }

        private:
            enumerator<T> &parent_;
            F predicate_;
        };

    } // namespace impl

    template<typename T>
    auto from(T begin, T end) {
        return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
    }

} // namespace linq

#endif