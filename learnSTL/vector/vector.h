#pragma once
#include <iostream>

namespace wstl
{
template<typename T>
class vector
{
public:
    //构造函数：初始化为空状态
    vector()
    {
        data = nullptr;
        _size = 0;
        _capacity = 0;
    }
    // vector(int capacity):_capacity(capacity)
    // {
    //     data = nullptr;
    //     _size = 0;
    // }
    ~vector()
    {
        delete [] data;
    }

    //迭代器
    using iterator = T*;
    using const_iterator = const T*;

    iterator begin()
    {
        return data;
    }
    iterator end()
    {
        return data + _size;
    }

    const_iterator begin() const
    {
        return data;
    }

    const_iterator end() const
    {
        return data + _size;
    }
    size_t size() {return _size;}
    size_t capacity() {return _capacity;}

    void push_back(const T& value)
    {
        if(_size == _capacity)
        {
            size_t newCapacity = (_capacity == 0)? 1 : _capacity*2;
            //开辟新空间
            T* newData = new T[newCapacity];

            //搬移旧数据
            if (data != nullptr)
            {
                for (size_t i = 0; i < _size; i++)
                {
                    newData[i] = data[i];
                }
                delete [] data;
            }
            //更新指针和容量
            data = newData;
            _capacity = newCapacity;
        }
        data[_size] = value;
        _size++;
    }

    void pop_back()
    {
        //不需要清理那块内存，下次再写会覆盖
        if(_size > 0)
        {
            _size --;
        }
    }
    const T& operator[](size_t index) const
    {
        return data[index];
    }
    T& operator[](size_t index)
    {
        return data[index];
    }
private:
    T *data;
    size_t _size;
    size_t _capacity;
};//vector

}//wstl