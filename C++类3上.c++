/*
C++的动态内存分配
    1.在C++中如何给类的对象申请堆内存空间
    2.在C中申请堆内存使用alloc申请，free释放。C++中只能给变量在堆内存中申请空间不能给对象在对内存中申请空间
    3.在C++给对象在对内存中申请空间
        使用new申请，使用delete释放空间
        语法：new 类名 或者 new 类名（实参）
              获取一个堆空间的首地址
                new类名（实参）     
        创建对象数组：new 类名[n],其中n表示数组元素的个数
                    创建数组时，只能调用无参构造函数
        释放一个对象数组：delete [] 数组名

        new 和 delete 是运算符 不是函数
*/     

#include <iostream>
using namespace std;
//类的功能：复数：a+bi
class MyClass{
    public:
        MyClass();
        MyClass(float a,float b);
        ~MyClass();
        void print(){
            if(b < 0){
                cout << a << "-" << -b << "i" << endl;
            }
            else{
                cout << a << "+" << b << "i" << endl;
            } 
        }
    private:    
        float a,b;
};

MyClass::MyClass():a(1),b(1){//默认创建1+2i的一个复数

    cout << "MyClass::MyClass()" << endl;
}
MyClass::MyClass(float a,float b){
    this->a = a;
    this->b = b;
    cout << "MyClass::MyClass(float a,float b)" << endl;
}
MyClass::~MyClass(){
    cout << "MyClass::~MyClass()" << endl;
}



int main(){
    MyClass *p1 = new MyClass;
    p1->print();
    cout << "******" << endl;
    delete p1;

    MyClass *p3 = new MyClass(4,5,9.9);
    p3->print();
    delete p3;

    MyClass *P4 = new MyClass[5];
    P4[0].print();
    P4[1].print();


    cout << "***** 不使用malloc 和 free给对象申请堆空间" << endl;

    MyClass *p2 =(MyClass *)malloc(sizeof(MyClass));
    p2->print();
    free(p2);
    cout << "******" << endl;
    
    return 0;
}  