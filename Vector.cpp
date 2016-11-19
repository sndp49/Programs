#include <iostream>
#include <cassert>
#include <string>
using namespace std;

const int _DEFAULT_VECTOR_SIZE = 4;

template <typename T>
class Vector
{
    T *ptr;
    size_t e, _reserve;    // size and reserved size

    void allocate()                     {   ptr = new T[_reserve];   }          // contiguos memory accolocation

public:
    Vector() : e(0), _reserve(_DEFAULT_VECTOR_SIZE)       {   allocate();   }
    Vector(int, const T);
    Vector(const Vector<T>&);

    ~Vector()                           {   delete[] ptr;   }

    size_t size() const                 {   return e;   }

    size_t getSize()    const           {   return sizeof(T);   }

    void resize(int sz);

    T& operator[](const int);
    T& operator[](const int) const;

    T* begin() const                    {   return ptr;     }
    T* end() const                      {   return ptr + e; }                   // since we are not dereferencing the pointer. Its ok

    void push_back(const T&);
    void pop_back();

    T&   front();
    T&   back();

    bool empty() const                  { return (e == 0);  }
    void clear();
};


template <typename T>
Vector<T> :: Vector(int sz, const T val) : e(sz), _reserve(sz)
{
    allocate();

    for (int i=0; i<e; i++)
        ptr[i] = val;
}


template <typename T>
Vector<T> :: Vector(const Vector<T>& other)
{
    this->e   = other.size();
    _reserve  = other.size() + _DEFAULT_VECTOR_SIZE;

    allocate();

    for (int i=0; i<other.size(); i++)
        this->ptr[i] = other[i];
}


template <typename T>
T& Vector<T> :: operator[] (const int i)
{
    if (i < e)
        return ptr[i];
    else
    {
        cout << "Error: Out of index" << endl;
        assert(0);
    }
}


template <typename T>
T& Vector<T> :: operator[] (const int i) const
{
    if (i < e)
        return ptr[i];
    else
    {
        cout << "Error: Out of index" << endl;
        assert(0);
    }
}


template <typename T>
void Vector<T> :: resize(int sz)
{
    _reserve = sz;

    T* new_array = new T[_reserve];

    for (int i = 0; i<e; i++)
        new_array[i] = ptr[i];

    delete[] ptr;

    ptr = new_array;
}


template <typename T>
void Vector<T> :: push_back(const T& val)
{
    if (e == _reserve)
        resize(_reserve + _DEFAULT_VECTOR_SIZE);

    ptr[e++] = val;
}


template <typename T>
void Vector<T> :: pop_back()
{
    if (e < 0)  return;

    --e;

    if (_reserve - e > _DEFAULT_VECTOR_SIZE)
    {
        ptr = (T*)realloc(ptr, (_reserve - _DEFAULT_VECTOR_SIZE) * sizeof(T));  // realloc: New size for the memory block in bytes
        _reserve -= _DEFAULT_VECTOR_SIZE;
    }
}


template <typename T>
void Vector<T> :: clear()
{
    delete[] ptr;

    e = 0;
    _reserve = _DEFAULT_VECTOR_SIZE;
    ptr = new T[_reserve];
}


template <typename T>
T& Vector<T> :: front()
{
    if (e>0)
        return ptr[0];
    else
        cout << "Error: Out of index" << endl;
        assert(0);
}


template <typename T>
T& Vector<T> :: back()
{
    if (e>0)
        return ptr[e-1];
    else
        cout << "Error: Out of index" << endl;
        assert(0);
}


int main()
{
    Vector<int> nums(10, 2);

    for (int i=0; i<nums.size(); i++)
    {
        if (i&1)
            nums[i] = 3;
    }

    cout << "Printing nums vector: ";
    for (auto it = nums.begin(); it != nums.end(); it++)
        cout << *it << ", ";
    cout << endl;

    Vector<int> duplicate = nums;   duplicate.push_back(numeric_limits<int>::max());

    nums.clear();   cout << "Clearing vector nums and nums is " << (nums.empty() ? "Empty" : "Not Empty") << endl;

    cout << "\nPrinting duplicate vector: ";
    for (auto it = duplicate.begin(); it != duplicate.end(); it++)
        cout << *it << ", ";
    cout << endl;

    duplicate.clear();


    cout << "\nUsing vector class as a char array : ";
    Vector<char> word;
    word.push_back('s'); word.push_back('a'); word.push_back('n'); word.push_back('d'); word.push_back('e'); word.push_back('e'); word.push_back('p');

    for (auto it = word.begin(); it != word.end(); it++)
        cout << *it;
    cout << endl;

    word.clear();


    cout << "\nUsing vector class as a string array : \t";
    Vector<string> words;
    words.push_back("sandeep "); words.push_back("mallela "); words.push_back("loves to "); words.push_back("code ");

    for (auto it = words.begin(); it != words.end(); it++)
        cout << *it;
    cout << endl;

    words.pop_back();
    words.pop_back();

    Vector<string> dict = words;
    words.clear();
    dict.push_back("loves "); dict.push_back("to "); dict.push_back("code "); dict.push_back("much more ");

    cout << "\nCalling Copy Constructor : \t";

    for (auto it = dict.begin(); it != dict.end(); it++)
        cout << *it;
    cout << endl;

    dict.clear();

    return 0;
}


/*

Vector.cpp:59:24: error: no viable overloaded operator[] for type 'const Vector<int>'
        this->ptr[i] = other[i];
                       ^~~~~ ~
Vector.cpp:139:29: note: in instantiation of member function 'Vector<int>::Vector' requested here
    Vector<int> duplicate = nums;
                            ^
Vector.cpp:24:8: note: candidate function not viable: 'this' argument has type 'const Vector<int>', but method is not marked const
    T& operator[](const int);
*/
