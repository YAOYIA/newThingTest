#include <iostream>
#include "../vector/vector.h"

using wstl::vector;

int main()
{
    vector<int> vec;
    std::cout << "初始大小：" << vec.size() << std::endl;
    
    for (size_t i = 0; i < 5; i++)
    {
        vec.push_back(i*10);
        std::cout << "插入数据：" << i*10 << "后。大小：" << vec.size() << ", 容量: " << vec.capacity() << std::endl;
    }
    
    //读取
    std::cout <<"\n当前内容:";
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout<<std::endl;

    vec[0] = 999;
    std::cout << "修改第一个元素后: " << vec[0] << std::endl;

    for (wstl::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    

    // 测试 pop_back
    vec.pop_back();
    std::cout << "\n执行一次 pop_back 后 - 大小: " << vec.size() << ", 容量: " << vec.capacity() << std::endl;

    return 0; // 程序结束时，vec 的析构函数会自动调用 delete[] 释放堆内存！
    
}
