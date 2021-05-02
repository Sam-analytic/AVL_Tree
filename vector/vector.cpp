#include<iostream>

using namespace std;

template <class T>
class Subvector{   //classes are better to define complicated structures since they seperate public and private interfaces
    public:
    unsigned int size() const;
    unsigned int capacity() const;
    
    Subvector();
    Subvector(unsigned int size);
    Subvector(unsigned int size, const T& init);  //init here is a constant reference because it is not supposed to be change during implementation
    Subvector(const Subvector<T> & v);      
    ~Subvector();

    
    void push_back(const T& value);
    void pop_back();
    void shrink_to_fit();
    bool clear();
    
    private:
    unsigned int vec_size;
    unsigned int vec_capacity;
    T* arr; //vector is dynamic array
};

template <class T> Subvector<T>::Subvector()
{
    vec_capacity = 0;
    vec_size = 0;
    arr = 0;
}

template <class T> Subvector<T>::Subvector(unsigned int size){
    vec_capacity = size;
    vec_size = size;
    arr = new T[size];                       //allocates a new array of type T 
}

template <class T> Subvector<T>::Subvector(unsigned int size, const T& int){
    vec_size = size;
    vec_capacity - size;
    arr = new T[size];  //vector is implemented using array
    for (i = 0; i < size - 1; ++i){
        arr[i] = int;
    }
}











