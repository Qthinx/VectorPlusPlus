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
        void clear() const { delete[] arr; };
        // Getting a value by index with handling out-of-bounds
        T at(T index);
        // Getting the first element of the vector
        T front() const { return arr[0]; };
        T choice() { return arr[rand(0, rows - 1)]; };
        // Getting the last element of the vector
        T back() const { arr[rows - 1]; };
        size_t size() const { return rows; };
        size_t real_size() { return rows = (rows > 0) ? size() - 1 : 0; };
        void resize(size_t new_size);

        // Operators;
        T& FakeVector<T>::operator[](T index) const;
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
        T rand(T a, T b) const;
        void smartCopy(const T* copyFrom, T* copyIn, T copyFrom_EndIndex, T copyFrom_StartIndex = 0);
        void smartCopy(FakeVector<T>& copyFrom, T* copyIn, T copyFrom_EndIndex, T copyFrom_StartIndex = 0);
        void smartCopy(const T* copyFrom, FakeVector<T>& copyIn, T copyFrom_EndIndex, T copyFrom_StartIndex = 0);
    };

}


namespace qts
{
    // Constructor with random values of a specified length
    template<typename T>
    FakeVector<T>::FakeVector(size_t rows)
    {
        try
        {
            if (rows <= 0)
            {
                this->arr = new T[this->rows = 0];
                throw std::logic_error("WARNING: zero rows in Array!");
            }
            else if (rows >= 0)
            {
                this->rows = rows;
                this->arr = new T[this->rows];
            }
        }
        catch (const std::logic_error& exc)
        {
            std::cout << exc.what() << std::endl;
        }
    }

    // Copy constructor
    template<typename T>
    FakeVector<T>::FakeVector(const FakeVector<T>& other) : rows(other.rows)
    {
        arr = new T[rows];
        smartCopy(other.arr, arr, rows);
    }

    // Destructor
    template<typename T>
    FakeVector<T>::~FakeVector()
    {
        if (arr != nullptr)
        {
            delete[] arr;
            arr = nullptr;
            rows = 0;
        }
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
        smartCopy(arr, temp, rows);

        delete[] arr; // Free memory from the old buffer
        arr = new T[rows]; // Allocate a new buffer with size rows
        smartCopy(temp, arr, rows);

        delete[] temp; // Free memory from the temporary buffer

        arr[real_size()] = val; // Add a new element to the vector
    }
    
    template<typename T>
    void FakeVector<T>::pop_back(T val) 
    {
        rows++; // Increase the number of rows

        T* temp = new T[rows]; // Allocate a new buffer with size rows
        smartCopy(arr, temp, rows, 1);

        delete[] arr; // Free memory from the old buffer
        arr = new T[rows]; // Allocate a new buffer with size rows
        smartCopy(temp, arr, rows);

        delete[] temp; // Free memory from the temporary buffer

        arr[0] = val; // Add a new element to the vector
    }

    template<typename T>
    void FakeVector<T>::insert(T val, T index)
    {
        try
        {
            if (index < size() or index > NULL)
            {
                arr[index - 1] = val;
            }
            else
            {
                throw std::out_of_range("Incorect index");
            }
        }
        catch (const std::out_of_range& exc)
        {
            std::cout << exc.what() << "\n";
        }
    }

    template<typename T>
    T FakeVector<T>::at(T index)
    {
        try
        {
            if (index < size() or index > NULL)
            {
                return arr[index - 1];
            }
            else
            {
                throw std::out_of_range("Incorect index");
            }
        }
        catch (const std::out_of_range& exc)
        {
            std::cout << exc.what() << "\n";
        }
    }

    template<typename T>
    void resize(size_t new_size) 
    { 
        try
        {
            if (new_size < 0 )
                throw std::logic_error("Logic ERROR");
            else
            {
                T* tmp = new T[rows];
                Smart
            }
        }
        catch (const std::logic_error& exc)
        {
            std::cout << exc.what() << std::endl;
        }
    }

    // Overloaded addition operator
    template<typename T>
    FakeVector<T>& FakeVector<T>::operator+(const FakeVector<T>& other)
    {
        FakeVector <T> tmp_result(std::max(rows, other.rows));
        for (size_t i = 0; i < tmp_result.size(); i++)
            tmp_result[i] = (arr[i] + other.arr[i]);
        //if (i < std::min(rows, other.rows))
        //{
        //    if (std::min(rows, other.rows) < rows)
        //        result.push_back(arr[i] + 0);
        //    else
        //        result.push_back(other.arr[i] + 0);
        //}
        //else
        return tmp_result;
    }

    template<typename T>
    FakeVector<T>& FakeVector<T>::operator-(const FakeVector<T>& other)
    {
        FakeVector <T> result(std::max(rows, other.rows));

        for (T i = 0; i < result.size(); i++)
            result[i] = (i < rows ? arr[i] : 0) - (i < other.rows ? other.arr[i] : 0);
        return result;
    }

    

    // Overloaded assignment operator
    template<typename T>
    FakeVector<T>& FakeVector<T>::operator=(const FakeVector<T>& other)
    {
        rows = other.rows;
        smartCopy(other.arr, arr, rows);
        return *this;
    }

    // Overloaded addition assignment operator
    template<typename T>
    FakeVector<T>& FakeVector<T>::operator+=(const FakeVector<T>& other)
    {
        T* temp = new T[rows + other.rows];
        smartCopy(arr, temp, rows);
        smartCopy(other.arr, temp, rows + other.rows, rows);

        delete[] arr;

        rows = rows + other.rows;

        smartCopy(temp, arr, rows);

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

    // Function to generate a random number in a specified range
    template<typename T>
    T FakeVector<T>::rand(T a, T b) const
    {
        std::random_device rd;   // Non-deterministic generator
        std::mt19937 gen(rd());  // Initialization of Mersenne twister.
        std::uniform_int_distribution<T> dist(a, b); // Distribution of results between a and b inclusive.
        return dist(gen);
    }

    // Function to copy from one array to another
    template<typename T>
    void FakeVector<T>::smartCopy(const T* copyFrom, T* copyIn,
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
    void FakeVector<T>::smartCopy(const T* copyFrom, FakeVector& copyIn,
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
    void FakeVector<T>::smartCopy(FakeVector<T>& copyFrom, T* copyIn,
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
