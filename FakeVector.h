#pragma once

#include <iostream>
#include <random>
#include <string>
#include <cstring>



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
        // Конструктори та деструктор
        FakeVector(size_t rows);
        FakeVector(const FakeVector<T>& other);
        ~FakeVector();

        // Методи-члени
        void sort();
        void reverse();
        void push_back(T val);
        void pop_back(T val);
        void insert(T val, T index);
        T randint(T a, T b) const;
        void clear() { arr = {}; };
        // Отримання значення за індексом з обробкою виходу за межі
        T at(T index);
        // Отримання першого елемента вектора
        T front() const { return arr[0]; };
        T choice() { return arr[randint(0, rows - 1)]; };
        // Отримання останнього елемента вектора
        T back() const { return  arr[rows - 1]; };
        size_t size() const { return rows; };
        size_t real_size() const { return rows - 1; };
        void resize(size_t new_size) { rows = (new_size < 1 ? 1 : new_size); };


        // Оператори
        T& operator[](const T index) const;
        // Перезавантажені логічні оператори використовуються переважно для-
        // сортуваннь,  юзер теж може це юзати для кастомних сортувань
        bool operator<(const FakeVector<T>& other) const { return (arr < other.arr) ? true : false; };
        bool operator>(const FakeVector<T>& other) const { return (arr > other.arr) ? true : false; };
        bool operator<=(const FakeVector<T>& other) const { return (arr <= other.arr) ? true : false; };
        bool operator>=(const FakeVector<T>& other) const { return (arr >= other.arr) ? true : false; };
        bool operator==(const FakeVector<T>& other) const { return (arr == other.arr) ? true : false; };
        bool operator!=(const FakeVector<T>& other) const { return (arr != other.arr) ? true : false; };
        // Перезавантажені математичні оператори використовуються переважно для-
        // сортуваннь, юзер теж може це юзати для кастомних сортувань
        FakeVector<T>& operator+(const FakeVector<T>& other);
        FakeVector<T>& operator-(const FakeVector<T>& other);
        // Перезавантажені математичні оператори використовуються переважно для реалізації швидких-
        // сортуваннь, юзер теж може це юзати для кастомних сортувань
        FakeVector<T>& operator=(const FakeVector<T>& other);
        FakeVector<T>& operator+=(const FakeVector<T>& other);
        // Перезавантажений амперсант використовуюється для получення посилання на реальний массив
        T* operator&() { return arr; }
        // Дружня функція
        // Перезавантажений std::cout 
        template <typename T1> friend std::ostream& operator<<(std::ostream&, const FakeVector<T1>&);

    private:
        // Методи-утиліти
        void swap(const T* copyFrom, T* copyIn, T copyFrom_EndIndex, T copyFrom_StartIndex = 0);
        void swap(FakeVector<T>& copyFrom, T* copyIn, T copyFrom_EndIndex, T copyFrom_StartIndex = 0);
        void swap(const T* copyFrom, FakeVector<T>& copyIn, T copyFrom_EndIndex, T copyFrom_StartIndex = 0);
                                               
    };
}


namespace qts
{
    // Конструктор з випадковими значеннями вказаної довжини
    template<typename T>
    FakeVector<T>::FakeVector(size_t rows)
    {
        if (rows <= 0)
        {
            this->rows = 1;
            this->arr = new T[this->rows]{};
            std::cout << "WARNING: zero rows in Array!\nRows size change to: "
                << this->rows << std::endl;
        }
        else if (rows >= 1)
        {
            this->rows = rows;
            this->arr = new T[this->rows]{};
        }
    }

    // Конструктор копіювання
    template<typename T>
    FakeVector<T>::FakeVector(const FakeVector<T>& other) : rows(other.rows)
    {
        arr = new T[rows];
        swap(other.arr, arr, rows);
        
    }

    // Деструктор
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

    // Додавання елементу в кінець вектора
    template<typename T>
    void FakeVector<T>::push_back(T val)
    {
        rows += 1;
        T* temp = new T[rows]{ };
        temp[rows] = val;
        rows -= 1;
        swap(arr, temp, rows);
        delete[] arr;
        arr = nullptr;
        rows += 1;
        arr = new T[rows]{ };
        swap(temp, arr, rows);
        delete[] temp;
        temp = nullptr;
    }

    template<typename T>
    void FakeVector<T>::pop_back(T val)
    {
        rows += 1;
        T* temp = new T[rows];
        swap(arr, temp, rows, 1);
        temp[0] = val;
        delete[] arr;
        arr = nullptr;
        arr = new T[rows];
        std::swap(temp, arr);
        delete[] temp;
        temp = nullptr;
    }

    template<typename T>
    void FakeVector<T>::insert(T val, T index)
    {
        arr[index] = val;
    }

    // Функція генерації випадкового числа в заданому діапазоні
    template<typename T>
    T FakeVector<T>::randint(T a, T b) const
    {
        std::random_device rd;   // Недетермінований генератор
        std::mt19937 gen(rd());  // Ініціалізація Mersenne twister.
        std::uniform_int_distribution<T> dist(a, b); // Розподіл результатів між a та b включно.
        return dist(gen);
    }

    template<typename T>
    T FakeVector<T>::at(T index)
    {
        T result;
        return result = (index >= 0 && index < rows) ? arr[index] : 0;
    }

    // Перевантажений оператор додавання
    template<typename T>
    FakeVector<T>& FakeVector<T>::operator+(const FakeVector<T>& other)
    {
        FakeVector <T> result(std::max(rows, other.rows));

        for (T i = 0; i < result.size(); i++)
        {
            result[i] = (i < rows ? arr[i] : 0) + (i < other.rows ? other.arr[i] : 0);
        }
        return result;
    }

    template<typename T>
    FakeVector<T>& FakeVector<T>::operator-(const FakeVector<T>& other)
    {
        FakeVector <T> result(std::max(rows, other.rows));

        for (T i = 0; i < result.size(); i++)
        {
            result[i] = (i < rows ? arr[i] : 0) - (i < other.rows ? other.arr[i] : 0);
        }
        return result;
    }

    // Перевантажений оператор індексації з обробкою виходу за межі
    template<typename T>
    T& FakeVector<T>::operator[](T index) const
    {
        if (index >= 0 && index < rows)
        {
            return arr[index];
        }
        // Можна викинути виняток або повернути значення за замовчуванням.
        throw std::out_of_range("Index out of bounds");
    }

    // Перевантажений оператор присвоєння
    template<typename T>
    FakeVector<T>& FakeVector<T>::operator=(const FakeVector<T>& other)
    {
        rows = other.rows;
        swap(other.arr, arr, rows);
        return *this;
    }

    // Перевантажений оператор складання з присвоєнням
    template<typename T>
    FakeVector<T>& FakeVector<T>::operator+=(const FakeVector<T>& other)
    {
        T* temp = new T[rows + other.rows];
        swap(arr, temp, rows);
        swap(other.arr, temp, rows + other.rows, rows);

        delete[] arr;

        rows = rows + other.rows;


        swap(temp, arr, rows);

        delete[] temp;
        temp = nullptr;

        return *this;
    }

    // Перевантажений оператор виводу в потік
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const FakeVector<T>& obj)
    {
        for (T i = 0; i < obj.rows; i++)
        {
            os << obj.arr[i] << " ";
        }
        return os;
    }

    // Функція копіювання з одного масиву в інший
    template<typename T>
    void FakeVector<T>::swap(const T* copyFrom, T* copyIn, 
                            T copyFrom_EndIndex, T copyFrom_StartIndex)
    {
        T j = 0;
        for (T i = copyFrom_StartIndex; i < copyFrom_EndIndex; i++, j++)
        {
            T tmp = copyFrom[j];
            copyIn[i] = tmp;
        }

    }

    // Функція копіювання з одного масиву в об'єкт
    template<typename T>
    void FakeVector<T>::swap(const T* copyFrom, FakeVector& copyIn, 
                            T copyFrom_EndIndex, T copyFrom_StartIndex)
    {
        T j = 0;
        for (T i = copyFrom_StartIndex; i < copyFrom_EndIndex; i++, j++)
        {
            T tmp = copyFrom[j];
            copyIn[i] = tmp;
        }
    }

    // Функція копіювання з об'єкта в масив
    template<typename T>
    void FakeVector<T>::swap(FakeVector<T>& copyFrom, T* copyIn, 
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

