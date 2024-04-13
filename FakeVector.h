#pragma once

#include <iostream>
#include <random>


namespace qts
{
    template<typename T>
    class FakeVector
    {
    private:
        T* arr = nullptr;
        size_t size = 0;


    public:
        FakeVector();
        // Constructors and destructor
        FakeVector(size_t size);
        FakeVector(const FakeVector<T>& other);
        FakeVector(const FakeVector<T>&& other);
        ~FakeVector();

        // Member methods
        void reverse();
        void push_back(T val);
        void push_front(T val);
        void pop_back();
        void pop_front();
        void insert(T val, T index);
        void clear() const { delete[] arr; };
        // Getting a value by index with handling out-of-bounds
        T at(T index);
        // Getting the first element of the vector
        size_t Size() const { return size; };
        void resize(size_t new_size);

        // Operators;
        T& operator[](T index);
        FakeVector<T>& operator=(const FakeVector<T>& other);
        FakeVector<T>& operator=(const FakeVector<T>&& other);
        FakeVector<T>& operator+=(const FakeVector<T>& other);
        // Overloaded ampersand is used to get a reference to the real array
        T* operator&() { return arr; }
        // Overloaded std::cout 
        template <typename T1> friend std::ostream& operator<<(std::ostream&, const FakeVector<T1>&);

    private:
        // Utility methods
        void smartCopy(const T* copyFrom, T* copyIn, size_t copyFrom_EndIndex, size_t copyFrom_StartIndex = 0);
        void smartCopy(FakeVector<T>& copyFrom, T* copyIn, size_t copyFrom_EndIndex, size_t copyFrom_StartIndex = 0);
        void smartCopy(const T* copyFrom, FakeVector<T>& copyIn, size_t copyFrom_EndIndex, size_t copyFrom_StartIndex = 0);
    };

}


namespace qts
{
    template<typename T>
    FakeVector<T>::FakeVector()
    {
        this->arr = new T[this->size = 0];
    }
    // Constructor with random values of a specified length
    template<typename T>
    FakeVector<T>::FakeVector(size_t size)
    {
        if (size <= 0)
        {
            this->arr = new T[this->size = 0];
            throw std::logic_error("WARNING: zero rows in Array!");
        }
        else if (size >= 0)
        {
            this->size = size;
            this->arr = new T[this->size];
        }
    }

    // Copy constructor
    template<typename T>
    FakeVector<T>::FakeVector(const FakeVector<T>& other) : size(other.size)
    {
        arr = new T[size];
        smartCopy(other.arr, arr, size);
    }

    template<typename T>
    inline FakeVector<T>::FakeVector(const FakeVector<T>&& other)
    {
        arr = new T[size];
        smartCopy(other.arr, arr, size);
        other.clear();
    }

    // Destructor
    template<typename T>
    FakeVector<T>::~FakeVector()
    {
        if (arr != nullptr)
        {
            delete[] arr;
            arr = nullptr;
            size = 0;
        }
    }

    template<typename T>
    void FakeVector<T>::reverse()
    {
        for (size_t i = 0, j = Size() - 1; i < j; i++, j--)
            std::swap(arr[i], arr[j]);
    }

    // Adding an element to the end of the vector
    template<typename T>
    void FakeVector<T>::push_back(T val)
    {
        if (Size() <= 0)
        {
            delete[] arr; // Free memory from the old buffer
            ++size; // Increase the number of rows
            arr = new T[size]; // Allocate a new buffer with size rows

            arr[0] = val; // Add a new element to the vector
        }
        else if (Size() == 1)
        {
            T* temp = new T[size]; // Allocate a new buffer with size rows
            temp[0] = arr[0];

            delete[] arr; // Free memory from the old buffer
            ++size; // Increase the number of rows
            arr = new T[size]; // Allocate a new buffer with size rows
            arr[0] = temp[0];

            delete[] temp; // Free memory from the temporary buffer

            arr[1] = val; // Add a new element to the vector
        }
        else
        {
            ++size; // Increase the number of rows

            T* temp = new T[size]; // Allocate a new buffer with size rows
            smartCopy(arr, temp, size);

            delete[] arr; // Free memory from the old buffer
            arr = new T[size]; // Allocate a new buffer with size rows
            smartCopy(temp, arr, size);

            delete[] temp; // Free memory from the temporary buffer
            size_t tmp = size - 1;
            arr[tmp] = val; // Add a new element to the vector
        }
    }

    template<typename T>
    void FakeVector<T>::push_front(T val)
    {
        if (size <= 0)
        {
            delete[] arr; // Free memory from the old buffer
            ++size; // Increase the number of rows
            arr = new T[size]; // Allocate a new buffer with size rows

            arr[0] = val; // Add a new element to the vector
        }
        else if (size == 1)
        {
            T* temp = new T[size]; // Allocate a new buffer with size rows
            temp[0] = arr[0];

            delete[] arr; // Free memory from the old buffer
            ++size; // Increase the number of rows
            arr = new T[size]; // Allocate a new buffer with size rows
            arr[1] = temp[0];

            delete[] temp; // Free memory from the temporary buffer

            arr[0] = val; // Add a new element to the vector
        }
        else
        {
            ++size; // Increase the number of rows

            T* temp = new T[size]; // Allocate a new buffer with size rows
            smartCopy(arr, temp, size, 1);

            delete[] arr; // Free memory from the old buffer
            arr = new T[size]; // Allocate a new buffer with size rows
            smartCopy(temp, arr, size);

            delete[] temp; // Free memory from the temporary buffer

            arr[0] = val; // Add a new element to the vector
        }   
    }

    template<typename T>
    inline void FakeVector<T>::pop_back()
    {
        if (size <= 0)
        {
            return;
        }
        else
        {
            T* tmp = new T[Size() - 1];
            smartCopy(arr, tmp, Size(), 1);
            delete[] arr;
            --size;
            arr = new T[Size()];
            smartCopy(tmp, arr, Size());
            delete[] tmp;
        }
    }

    template<typename T>
    inline void FakeVector<T>::pop_front()
    {
        if (size <= 0)
        {
            return;
        }
        else
        {
            T* tmp = new T[Size()];
            smartCopy(arr, tmp, Size());
            delete[] arr;
            --size;
            arr = new T[Size()];
            smartCopy(tmp, arr, Size());
            delete[] tmp;
        }
    }

    template<typename T>
    void FakeVector<T>::insert(T val, T index)
    {
        if (index < Size() or index > NULL)
        {
            arr[index - 1] = val;
        }
        else
        {
            throw std::out_of_range("Incorect index");
        }
    }

    template<typename T>
    inline void FakeVector<T>::resize(size_t new_size)
    {
        if (size <= 0)
        {
            delete[] arr;
            arr = new T[new_size]{ };
            size = new_size;
        }
        else if (new_size < 0)
        {
            throw std::logic_error("Logic ERROR");
        }
        else
        {
            T* tmp = new T[Size()];
            smartCopy(arr, tmp, Size());
            delete[] arr;
            arr = new T[new_size] { };
            smartCopy(tmp, arr, Size());
            delete[] tmp;
            size = new_size;
        }
    }

    template<typename T>
    T& FakeVector<T>::operator[](T index)
    {
        if (index > Size() || index < NULL)
        {
            throw std::out_of_range("operator[] error: out of range");
        }
        else if (index < Size() || index > NULL)
        {
            return arr[index];
        }
    }

    template<typename T>
    T FakeVector<T>::at(T index)
    {
        if (index < Size() or index > NULL)
        {
            return arr[index - 1];
        }
        else
        {
            throw std::out_of_range("Incorect index");
        }
    }

    // Overloaded assignment operator
    template<typename T>
    FakeVector<T>& FakeVector<T>::operator=(const FakeVector<T>& other)
    {
        size = other.size;
        smartCopy(other.arr, arr, size);
        return *this;
    }

    template<typename T>
    inline FakeVector<T>& FakeVector<T>::operator=(const FakeVector<T>&& other)
    {
        size = other.size;
        smartCopy(other.arr, arr, size);
        other.clear();
        return *this;
    }

    // Overloaded addition assignment operator
    template<typename T>
    FakeVector<T>& FakeVector<T>::operator+=(const FakeVector<T>& other)
    {
        T* temp = new T[size + other.size];
        smartCopy(arr, temp, size);
        smartCopy(other.arr, temp, size + other.size, size);

        delete[] arr;

        size = size + other.size;

        smartCopy(temp, arr, size);

        delete[] temp;

        return *this;
    }

    // Overloaded output operator for streams
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const FakeVector<T>& obj)
    {
        for (T i = 0; i < obj.size; i++)
            os << obj.arr[i] << " ";
        return os;
    }


    // Function to copy from one array to another
    template<typename T>
    void FakeVector<T>::smartCopy(const T* copyFrom, T* copyIn,
        size_t copyFrom_EndIndex, size_t copyFrom_StartIndex)
    {
        for (size_t i = copyFrom_StartIndex, j = 0; i < copyFrom_EndIndex; i++, j++)
        {
            T tmp = copyFrom[i];
            copyIn[j] = tmp;
        }
    }

    // Function to copy from an array to an object
    template<typename T>
    void FakeVector<T>::smartCopy(const T* copyFrom, FakeVector& copyIn,
        size_t copyFrom_EndIndex, size_t copyFrom_StartIndex)
    {
        for (size_t i = copyFrom_StartIndex, j = 0; i < copyFrom_EndIndex; i++, j++)
        {
            T tmp = copyFrom[i];
            copyIn[j] = tmp;
        }
    }

    // Function to copy from an object to an array
    template<typename T>
    void FakeVector<T>::smartCopy(FakeVector<T>& copyFrom, T* copyIn,
        size_t copyFrom_EndIndex, size_t copyFrom_StartIndex)
    {
        for (size_t i = copyFrom_StartIndex, j = 0; i < copyFrom_EndIndex; i++, j++)
        {
            T tmp = copyFrom[i];
            copyIn[j] = tmp;
        }
    }
}
