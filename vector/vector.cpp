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
    int pop_back();
    void shrink_to_fit();
    bool clear();
    
    
    unsigned int vec_size;
    unsigned int vec_capacity;
    T* arr; //vector is dynamic array
    
    T& operator [](unsigned int index);
};

template <class T> Subvector<T>::Subvector()
{
    vec_capacity = 0;
    vec_size = 0;
    arr = 0;
}

template <class T> unsigned int Subvector<T>::size() const{
    return vec_size;
}

template <class T> unsigned int Subvector<T>::capacity() const{
    return vec_capacity;
}

template <class T> Subvector<T>::Subvector(unsigned int size){
    vec_capacity = size;
    vec_size = size;
    arr = new T[size];                       //allocates a new array of type T 
}

template <class T> Subvector<T>::Subvector(unsigned int size, const T& init){
    vec_size = size;
    vec_capacity - size;
    arr = new T[size];  //vector is implemented using array
    for (int i = 0; i < size; ++i){
        arr[i] = init;
    }
}

template <class T> Subvector<T>::Subvector(const Subvector<T>& v){ //Note that T is here same since explicit type conversion is not defined 
    vec_size = v.vec_size;
    vec_capacity = v.vec_capacity;
    arr = new T[vec_size];
    for (int i =0; i < vec_size; ++i ){
        arr[i] = v.arr[i];
    }
}

template <class T> void Subvector<T>::push_back(const T& value){
    if (vec_size < vec_capacity){
        arr[size] = value;
        vec_size += 1;
    }
    else if (vec_size = vec_capacity){
        unsigned int new_capacity = vec_capacity*2;
        T* new_arr = new T[new_capacity];
        for (int i = 0; i < size; ++i){
            new_arr[i] = arr[i];
        }
        delete arr;  
        
        arr = new_arr;
        vec_capacity = new_capacity;
        vec_size += 1;
    }
}

template <class T> int Subvector<T>::pop_back(){
    T* temp;
    temp ->arr[vec_size - 1];
    T temp_value = *temp;
    free(temp);
    vec_size -= 1;
    return temp_value;
}

template <class T> void Subvector<T>::shrink_to_fit(){
    for (int i = vec_size - 1; i < vec_capacity; ++i){
        delete arr[i];
    }
    vec_capacity = vec_size;
}

template<class T> bool Subvector<T>::clear(){
    for (int i =0; i < vec_size; ++i){
        arr[i] = NULL; 
    }
    vec_size = 0;
}

template <class T> Subvector<T>::~Subvector(){
    T* temp = arr;
    for (int i =0; i < vec_capacity; ++i){
        delete temp;
        ++temp;
    }
    vec_size = NULL;
    vec_capacity = NULL;
}

template<class T> T& Subvector<T>::operator [](unsigned int index){
    T& value = arr[index];
    return value;
}

int main(){
    Subvector<int> v(4,1);
    for(int i = 0; i < v.size(); ++i){
        cout << v[i] << " ";
    }
    return 0;
}




