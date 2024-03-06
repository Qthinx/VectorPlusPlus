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
        size_t rows = 0;
        size_t capacity = 0;

    public:
        // Constructors and destructor
        FakeVector(size_t rows);
        FakeVector(const FakeVector<T>& other);
        ~FakeVector();

        // Member methods
        void sort();
        void reverse();
        void push_back(T val);
        void pop_back(T val);
        void insert(T val, T index);
        T randint(T a, T b) const;
        void clear() { arr = {}; };
        // Getting a value by index with handling out-of-bounds
        T at(T index);
        // Getting the first element of the vector
        T front() const { return arr[0]; };
        T choice() { return arr[randint(0, rows - 1)]; };
        // Getting the last element of the vector
        T back() const { arr[rows - 1]; };
        size_t size() const { return rows; };
        size_t real_size() const { return rows - 1; };
        void resize(size_t new_size) { rows = (new_size < 1 ? 1 : new_size); };

        // Operators
        T& operator[](const T index) const;
        // Overloaded logical operators are primarily used for sorting, and the user can use them for custom sorting
        bool operator<(const FakeVector<T>& other) const { return (arr < other.arr) ? true : false; };
        bool operator>(const FakeVector<T>& other) const { return (arr > other.arr) ? true : false; };
        bool operator<=(const FakeVector<T>& other) const { return (arr <= other.arr) ? true : false; };
        bool operator>=(const FakeVector<T>& other) const { return (arr >= other.arr) ? true : false; };
        bool operator==(const FakeVector<T>& other) const { return (arr == other.arr) ? true : false; };
        bool operator!=(const FakeVector<T>& other) const { return (arr != other.arr) ? true : false; };
        // Overloaded mathematical operators are primarily used for fast sorting, and the user can use them for custom sorting
        FakeVector<T>& operator+(const FakeVector<T>& other);
        FakeVector<T>& operator-(const FakeVector<T>& other);
        // Overloaded mathematical operators are primarily used for fast sorting, and the user can use them for custom sorting
        FakeVector<T>& operator=(const FakeVector<T>& other);
        FakeVector<T>& operator+=(const FakeVector<T>& other);
        // Overloaded ampersand is used to get a reference to the real array
        T* operator&() { return arr; }
        // Friend function
        // Overloaded std::cout 
        template <typename T1> friend std::ostream& operator<<(std::ostream&, const FakeVector<T1>&);

    private:
        // Utility methods
        void smartSwap(const T* copyFrom, T* copyIn, T copyFrom_EndIndex, T copyFrom_StartIndex = 0);
        void smartSwap(FakeVector<T>& copyFrom, T* copyIn, T copyFrom_EndIndex, T copyFrom_StartIndex = 0);
        void smartSwap(const T* copyFrom, FakeVector<T>& copyIn, T copyFrom_EndIndex, T copyFrom_StartIndex = 0);
    };

}


namespace qts
{
    // Constructor with random values of a specified length
    template<typename T>
    FakeVector<T>::FakeVector(size_t rows)
    {
        if (rows <= 0)
        {
            this->rows = 1;
            this->arr = new T[this->rows]{};
            std::cout << "WARNING: zero rows in Array!\nRows size changed to: "
                << this->rows << std::endl;
        }
        else if (rows >= 1)
        {
            this->rows = rows;
            this->arr = new T[this->rows]{};
        }
    }

    // Copy constructor
    template<typename T>
    FakeVector<T>::FakeVector(const FakeVector<T>& other) : rows(other.rows)
    {
        arr = new T[rows];
        smartSwap(other.arr, arr, rows);
    }

    // Destructor
    template<typename T>
    FakeVector<T>::~FakeVector()
    {
        delete[] arr;
        arr = nullptr;
        rows = 0;
    }

    template<typename T>
    void FakeVector<T>::sort()
    {
        for (int i = 1; i < rows; i++)
        {
            int j = i - 1;
            while (j >= 0 && arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                j--;
            }
        }
    }

    template<typename T>
    void FakeVector<T>::reverse()
    {
        for (size_t i = 0, j = real_size(); i < j; i++, j--)
            std::swap(arr[i], arr[j]);
    }

    // Adding an element to the end of the vector
    template<typename T>
    void FakeVector<T>::push_back(T val)
    {
        rows++; // Increase the number of rows

        T* temp = new T[rows]; // Allocate a new buffer with size rows
        smartSwap(arr, temp, rows);

        delete[] arr; // Free memory from the old buffer
        arr = new T[rows]; // Allocate a new buffer with size rows
        smartSwap(temp, arr, rows);

        delete[] temp; // Free memory from the temporary buffer

        arr[rows - 1] = val; // Add a new element to the vector
    }

    template<typename T>
    void FakeVector<T>::pop_back(T val)
    {
        rows++; // Increase the number of rows

        T* temp = new T[rows]; // Allocate a new buffer with size rows
        smartSwap(arr, temp, rows, 1);

        delete[] arr; // Free memory from the old buffer
        arr = new T[rows]; // Allocate a new buffer with size rows
        smartSwap(temp, arr, rows);

        delete[] temp; // Free memory from the temporary buffer

        arr[0] = val; // Add a new element to the vector
    }

    template<typename T>
    void FakeVector<T>::insert(T val, T index)
    {
        arr[index] = val;
    }

    // Function to generate a random number in a specified range
    template<typename T>
    T FakeVector<T>::randint(T a, T b) const
    {
        std::random_device rd;   // Non-deterministic generator
        std::mt19937 gen(rd());  // Initialization of Mersenne twister.
        std::uniform_int_distribution<T> dist(a, b); // Distribution of results between a and b inclusive.
        return dist(gen);
    }

    template<typename T>
    T FakeVector<T>::at(T index)
    {
        T result;
        return result = (index >= 0 && index < rows) ? arr[index] : 0;
    }

    // Overloaded addition operator
    template<typename T>
    FakeVector<T>& FakeVector<T>::operator+(const FakeVector<T>& other)
    {
        FakeVector <T> result(std::max(rows, other.rows));

        for (T i = 0; i < result.size(); i++)
            result[i] = (i < rows ? arr[i] : 0) + (i < other.rows ? other.arr[i] : 0);
        return result;
    }

    template<typename T>
    FakeVector<T>& FakeVector<T>::operator-(const FakeVector<T>& other)
    {
        FakeVector <T> result(std::max(rows, other.rows));

        for (T i = 0; i < result.size(); i++)
            result[i] = (i < rows ? arr[i] : 0) - (i < other.rows ? other.arr[i] : 0);
        return result;
    }

    // Overloaded indexing operator with handling out-of-bounds
    template<typename T>
    T& FakeVector<T>::operator[](T index) const
    {
        if (index >= 0 && index < rows)
            return arr[index];
        // You can throw an exception or return a default value.
        throw std::out_of_range("Index out of bounds");
    }

    // Overloaded assignment operator
    template<typename T>
    FakeVector<T>& FakeVector<T>::operator=(const FakeVector<T>& other)
    {
        rows = other.rows;
        smartSwap(other.arr, arr, rows);
        return *this;
    }

    // Overloaded addition assignment operator
    template<typename T>
    FakeVector<T>& FakeVector<T>::operator+=(const FakeVector<T>& other)
    {
        T* temp = new T[rows + other.rows];
        smartSwap(arr, temp, rows);
        smartSwap(other.arr, temp, rows + other.rows, rows);

        delete[] arr;

        rows = rows + other.rows;

        smartSwap(temp, arr, rows);

        delete[] temp;

        return *this;
    }

    // Overloaded output operator for streams
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const FakeVector<T>& obj)
    {
        for (T i = 0; i < obj.rows; i++)
            os << obj.arr[i] << " ";
        return os;
    }

    // Function to copy from one array to another
    template<typename T>
    void FakeVector<T>::smartSwap(const T* copyFrom, T* copyIn,
        T copyFrom_EndIndex, T copyFrom_StartIndex)
    {
        T j = 0;
        for (T i = copyFrom_StartIndex; i < copyFrom_EndIndex; i++, j++)
        {
            T tmp = copyFrom[j];
            copyIn[i] = tmp;
        }
    }

    // Function to copy from an array to an object
    template<typename T>
    void FakeVector<T>::smartSwap(const T* copyFrom, FakeVector& copyIn,
        T copyFrom_EndIndex, T copyFrom_StartIndex)
    {
        T j = 0;
        for (T i = copyFrom_StartIndex; i < copyFrom_EndIndex; i++, j++)
        {
            T tmp = copyFrom[j];
            copyIn[i] = tmp;
        }
    }

    // Function to copy from an object to an array
    template<typename T>
    void FakeVector<T>::smartSwap(FakeVector<T>& copyFrom, T* copyIn,
        T copyFrom_EndIndex, T copyFrom_StartIndex)
    {
        T j = 0;
        for (T i = copyFrom_StartIndex; i < copyFrom_EndIndex; i++, j++)
        {
            T tmp = copyFrom[j];
            copyIn[i] = tmp;
        }
    }
}
