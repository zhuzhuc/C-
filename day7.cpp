//string类的内部实现
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
/*
    C++中string类内部操作
    也就是说：我们要去写一个string类，能够完成string类的所有操作
    也就是要完成一下操作
        1.构造函数 希望能够直接使用  = 构造
            构造函数注意传入的参数为const char*类型
        2.拷贝构造函数  类中包含指针必须重写
        3.析构函数
        4.operator=
        5.operator+
        6.operator
        7.operator<<
        8.从string转换成const char* 类型 就是 data()方法
        9.讲string转换成int类型
        10.统计string的长度，也即是size（）方法
        11.清空字符串
        12.判断字符串是否为空
        13.追加 append 功能类似于+=
*/
/*
    注意：当myString对象没有保存任何字符串的时候，我们应该至少为该对象中的ptr申请1个字节的空间
    这样做的好处是：任何情况下，ptr都不为NULL，避免了判断ptr是否为NULL的情况
        也就是说：只要保证ptr任何时候都不为空的话，我们在随时访问ptr的时候，就无需考虑他是否为空的可能
        也就是说：无参构造函数需要认真重写
*/

class myString {
    char* ptr;  // 指向动态堆内存空间的指针，用于存储字符串
    int len;    // 存放字符串的实际长度，不包括结束符
    string name; // 用于存储对象的名称

public:
    // 构造函数，用于初始化对象
    myString(string name);
    myString(const char* r);
    myString(const myString& r);
    
    // 析构函数，用于释放动态分配的内存
    ~myString();

    // 成员函数

    // 打印字符串
    void show();

    // 获取字符串长度
    int size();

    // 清空字符串
    void clear();

    // 判断字符串是否为空
    bool empty();

    // 运算符重载

    // 赋值运算符重载
    myString operator=(const myString& r);

    // 字符串连接运算符重载
    myString operator+(const char* r);

    // 字符串连接运算符重载
    myString operator+(const myString& r);
};

// 构造函数实现
myString::myString(string name) : name(name) {
    ptr = (char*)malloc(1); // 为ptr申请一个字节的堆空间，用于存放字符串
    memset(ptr, 0, 1);
    len = 0;
}

myString::myString(const char* r) {
    len = strlen(r); // 获取字符串的长度
    ptr = (char*)malloc(len + 1); // 为ptr申请足够的堆空间，用于存放字符串和结束符
    memset(ptr, 0, len + 1);
    memmove(ptr, r, len); // 将字符串拷贝到ptr指向的内存空间
}

myString::myString(const myString& r) {
    len = r.len; // 获取字符串的长度
    ptr = (char*)malloc(len + 1); // 为ptr申请足够的堆空间，用于存放字符串和结束符
    memset(ptr, 0, len + 1);
    memmove(ptr, r.ptr, len); // 将r中的字符串拷贝到ptr指向的内存空间
}

// 析构函数实现
myString::~myString() {
    free(ptr); // 释放动态分配的内存
}

// 成员函数实现

// 打印字符串
void myString::show() {
    cout << ptr;//不添加换行符
}

// 获取字符串长度
int myString::size() {
    return len;
}

// 清空字符串
void myString::clear() {
    free(ptr); // 释放动态分配的内存
    ptr = (char*)malloc(1); // 重新为ptr申请一个字节的堆空间
    memset(ptr, 0, 1);
    len = 0;
}

// 判断字符串是否为空
bool myString::empty() {
    return !len; // 当len为0时，返回true，表示字符串为空；否则返回false，表示字符串不为空
}

// 赋值运算符重载实现
myString myString::operator=(const myString& r) {
    if (this != &r) {
        free(ptr); // 释放原有的内存空间
        len = r.len; // 获取字符串的长度
        ptr = (char*)malloc(len + 1); // 为ptr申请足够的堆空间，用于存放字符串和结束符
        memset(ptr, 0, len + 1);
        memmove(ptr, r.ptr, len); // 将r中的字符串拷贝到ptr指向的内存空间
    }
    return *this;
}

// 字符串连接运算符重载实现
myString myString::operator+(const char* r) {
    myString newStr = *this; // 创建新的对象，复制当前对象的内容
    free(newStr.ptr); // 释放新对象的原有内存空间
    newStr.len = len + strlen(r); // 计算新对象的长度
    newStr.ptr = (char*)malloc(newStr.len + 1); // 为新对象申请足够的堆空间，用于存放字符串和结束符
    memset(newStr.ptr, 0, newStr.len + 1);
    memmove(newStr.ptr, ptr, len); // 将当前对象的字符串拷贝到新对象的内存空间
    strcat(newStr.ptr, r); // 将r中的字符串连接到新对象的内存空间
    return newStr; // 返回新对象
}

// 字符串连接运算符重载实现
myString myString::operator+(const myString& r) {
    myString newStr = *this; // 创建新的对象，复制当前对象的内容
    free(newStr.ptr); // 释放新对象的原有内存空间
    newStr.len = len + r.len; // 计算新对象的长度
    newStr.ptr = (char*)malloc(newStr.len + 1); // 为新对象申请足够的堆空间，用于存放字符串和结束符
    memset(newStr.ptr, 0, newStr.len + 1);
    memmove(newStr.ptr, ptr, len); // 将当前对象的字符串拷贝到新对象的内存空间
    memmove(newStr.ptr + len, r.ptr, r.len); // 将r中的字符串拷贝到新对象的内存空间
    return newStr; // 返回新对象
}

// 主函数
int main() {
    myString str("hello "); // 创建一个myString对象，使用带参构造函数初始化
    myString atr("world");
    myString p = str; // 创建一个myString对象，使用拷贝构造函数初始化
    myString p2 = "123"; // 创建一个myString对象，使用带参构造函数初始化

    p2 = str; // 使用赋值运算符重载

    p2 = p2 + "hello"; // 使用字符串连接运算符重载
    p2 = p2 + "world"; // 使用字符串连接运算符重载
    str.show(); // 打印字符串
    atr.show();

    return 0;
}
