#pragma once
#include <iterator>
#include <type_traits>

template <typename T>
class myArray final
{
public:
    myArray()
    {
        this->array_ = static_cast<T*>(malloc(sizeof(T) * this->capacity_));
        std::memset(this->array_, 0, sizeof(T) * this->capacity_);
    }

    myArray(int capacity)
    {
        this->capacity_ = capacity;
        this->array_ = static_cast<T*>(malloc(sizeof(T) * this->capacity_));
        std::memset(this->array_, 0, sizeof(T) * this->capacity_);
    }

    ~myArray()
    {
        for (int i = 0; i < this->size_; i++)
        {
            array_[i].~T();
        }
        std::memset(this->array_, 0, sizeof(T) * this->capacity_);
        free(this->array_);
    }

    int insert(const T& value)
    {
        return insert(this->size_, value);
    }

    int insert(int index, const T& value)
    {
        ///доделать проверку, ассерт мимо
        if (this->size_ == this->capacity_)
        {
            int new_capacity = this->capacity_ * 1.6f;
            T* new_array = static_cast<T*>(malloc(sizeof(T) * new_capacity));
            std::memset(new_array, 0, sizeof(T) * new_capacity);
            for (int i = 0; i < index; i++)
            {
                new(new_array + i) T(this->array_[i]);
                this->array_[i].~T();
            }
            new(new_array + index) T(value);
            for (int i = index; i < this->size_; i++)
            {
                new(new_array + i) T(this->array_[i]);
                this->array_[i].~T();
            }
            free(this->array_);
            this->capacity_ = new_capacity;
            this->array_ = new_array;
            ++this->size_;
            return index;
        }
        for (int i = this->size_; i > index; --i)
        {
            new(this->array_ + i) T(this->array_[i]);
        }
        new(this->array_ + index) T(value);
        ++this->size_;
        return index;
    }

    void remove(int index)
    {
        this->array_[index].~T();
        for (int i = index; i < this->size_ - 1; ++i)
        {
            new(this->array_ + i) T(this->array_[i + 1]);
            this->array_[i + 1].~T();
        }
        --this->size_;
    }

    void clear()
    {
        for (auto& i: *this)
        {
            i.~T();
        }
        this->size_ = 0;
    }

    const T& operator[](int index) const
    {
        return this->array_[index];
    }

    T& operator[](int index)
    {
        return this->array_[index];
    }

    int size() const
    {
        return this->size_;
    }

    int capacity() const
    {
        return this->capacity_;
    }

    T* data()
    {
        return this->array_;
    }

    [[nodiscard]] const T* data() const
    {
        return this->array_;
    }

#pragma region iterators

    template <bool IsConst, bool IsReverse = false>
    class Iterator
    {
    public:
        using Container = std::conditional_t<IsConst, const myArray*, myArray*>;
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::conditional_t<IsConst, const T, T>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
    
        Iterator(Container container, pointer ptr) : container_(container), ptr_(ptr)
        {
        }

        Iterator(const Iterator<false, IsReverse>& other) : container_(other.container_), ptr_(other.ptr_){}

        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }
        [[nodiscard]] const T& get() const { return *ptr_; }

        void set(const T& value) { *ptr_ = value; }

        void next()
        {
            if (hasNext())
            {
                if constexpr (IsReverse) --ptr_;
                else ++ptr_;
            }
        }

        [[nodiscard]] bool hasNext() const
        {
            if constexpr (IsReverse)
            {
                return ptr_ > container_->array_;
            }
            return ptr_ < container_->array_ + container_->size_;
        }


        Iterator& operator++()
        {
            if constexpr (IsReverse) --ptr_;
            else ++ptr_;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            if constexpr (IsReverse) --*this;
            else ++*this;
            return tmp;
        }

        Iterator& operator--()
        {
            if constexpr (IsReverse) ++ptr_;
            else --ptr_;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator tmp = *this;
            if constexpr (IsReverse) ++*this;
            else --*this;
            return tmp;
        }

        Iterator& operator+=(difference_type n)
        {
            ptr_ += n;
            return *this;
        }

        Iterator operator+(difference_type n) const { return Iterator(container_, ptr_ + n); }
        friend Iterator operator+(difference_type n, const Iterator& it) { return it.ptr_ + n; }

        Iterator& operator-=(difference_type n)
        {
            ptr_ -= n;
            return *this;
        }

        Iterator operator-(difference_type n) const { return Iterator(container_, ptr_ - n); }
        difference_type operator-(const Iterator& it) const { return ptr_ - it.ptr_; }

        bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const Iterator& other) const { return ptr_ != other.ptr_; }
        bool operator<(const Iterator& other) const { return ptr_ < other.ptr_; }

    private:
        Container container_;
        pointer ptr_;
    };


    using iter = Iterator<false>;
    [[nodiscard]] iter begin() { return iter(this, array_); }
    [[nodiscard]] iter end() { return iter(this, array_ + size_); }

    using const_iter = Iterator<true>;
    [[nodiscard]] const_iter cbegin() const { return const_iter(this, array_); }
    [[nodiscard]] const_iter begin() const { return const_iter(this, array_); }
    [[nodiscard]] const_iter cend() const { return const_iter(this, array_ + size_); }
    [[nodiscard]] const_iter end() const { return const_iter(this, array_ + size_); }

    using reverse_iter = Iterator<false, true>;
    [[nodiscard]] reverse_iter rbegin() { return reverse_iter(this, array_ + size_); }
    [[nodiscard]] reverse_iter rend() { return reverse_iter(this, array_); }

    using const_reverse_iter = Iterator<true, true>;
    [[nodiscard]] const_reverse_iter crbegin() const { return const_reverse_iter(this, array_ + size_); }
    [[nodiscard]] const_reverse_iter crend() const { return const_reverse_iter(this, array_); }


#pragma endregion iterators


    myArray& operator=(const myArray& other)
    {
        if (this == std::addressof(other))
            return *this;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->array_ = static_cast<T*>(malloc(sizeof(T) * this->capacity_));
        for (int i = 0; i < this->size_; i++)
            new(this->array_ + i) T(other.array_[i]);
        return *this;
    }

    // myArray& operator=(const myArray& other)
    // {
    //     if (this == &other)
    //         return *this;
    //     capacity_ = other.capacity_;
    //     size_ = other.size_;
    //     array_ = other.array_;
    //     return *this;
    // }

    //??????????????????????
    myArray& operator=(myArray&& other) noexcept
    {
        if (this == &other)
            return *this;
        capacity_ = other.capacity_;
        size_ = other.size_;
        array_ = other.array_;
        return *this;
    }

    //??????????????????????????
    myArray(const myArray& other)
    {
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->array_ = static_cast<T*>(malloc(sizeof(T) * this->capacity_));
        for (int i = 0; i < this->size_; i++)
            new(this->array_ + i) T(other.array_[i]);
    }

    myArray(myArray&& other) noexcept
        : capacity_(other.capacity_),
          size_(other.size_),
          array_(other.array_)
    {
    }

private:
    int capacity_ = 16;
    int size_ = 0;
    T* array_;
};
