//#include <iostream>
//using namespace std;
/*
int mian(){
    int *pa = new int;
    cout << *pa << endl;
    *pa = 100;
    cout << *pa << endl;
    delete pa;
    int *pb = new int[100];
    //自动初始化为0
    for (int  i = 0; i < 100; i++)
    {
        cout << pb[i] << " ";
    }
    cout << endl;
    delete [] pb;//与new创建时配对使用

    return 0;
}*/
//先回顾C语言中的函数调用
/*#include <stdio.h>
void test(){
    int i = 0;//在栈内存中分配空间
    i++;
    printf("%d\n", i);

}
void test2(){
    static int i = 0;//在静态内存中分配空间不会随函数的调用结束而释放
    i++;
    printf("%d\n", i);
}
int main(){
    test();
    test();
    test();
    printf("***************\\n");
    test2();
    test2();
    test2();
    return 0;
}*/
//C++中的静态内存
/*
    静态变量/静态数据成员/静态属性
    类的成员如果有static修饰，此成员在所有该类的对象中共享
*/
/*class Myclass{
    public:
        int a;
        static int b;
};
//静态成员变量使用之前必须先初始化
int Myclass::b = 200;
int main(){
    Myclass a,b,c;
    a.a = 100;
    cout << "a.a:" << endl << a.a << endl;
    cout << b.a << endl << c.a << endl;
    cout << "***********\n";
    cout <<a.b << endl << b.b << endl << c.b << endl;
    a.b = 300;
    cout << "a.b:" << endl << a.b << endl;
    cout << b.b << endl << c.b << endl;
  
    return 0;
}
*/
//C++中的静态函数
/*
    静态方法/函数
    在类的方法成员前面加上static修饰，此方法成为静态方法。
    静态方法只能访问静态成员，不能访问非静态成员
*/
/*#include <iostream>
using namespace std;
class myclass{
    public:
        int a;
        static int b;
        static void fun();
};
int myclass::b = 100;
void myclass::fun(){
    //a = 200;//不能在静态成员函数中使用非静态成员 不能在类里面直接初始化静态成员
    b = 300;
}
int main(){
    myclass A,B;
    cout << A.b << endl << B.b << endl;
    A.fun();
    cout << A.b << endl << B.b << endl;

    //不通过类的对象  直接通过类来操作静态成员
    myclass::b = 500;
    cout << myclass::b << endl;
    myclass::fun();
    cout << A.b << endl << B.b << endl;
    return 0;
}
/*
    单例模式：只能创建唯一对象的特殊类
    优点：
        1.保证单一性，避免同时操作类的多个对象
        2.避免重复创建对象时造成的时间开销
    缺点：
        1.会长期占用内存
        2.只有程序结束时才会释放内存
    创建此特殊类的条件：
        1.构造函数私有化，规避创建对象
        2.通过静态方法创建对象
*/
#include <iostream>
using namespace std;
class singleton
{
    public:
        static singleton * getInstance();//返回静态对象的方法
    private:
        singleton();//构造函数私有化
        static singleton *instance;//静态属性
};
singleton *singleton::instance = NULL;//初始化静态成员为空
//在静态方法中，判断静态变量成员是否为控，为空时才创建
singleton * singleton::getInstance(){
    if (instance == NULL)
    {
        instance = new singleton;
    }
    return instance;
}
singleton::singleton(){

}

int main(){
   // singleton *obj1 = new singleton;//因为构造函数私有化了，不能再通过这种方式创建对象
    singleton *obj2 = singleton::getInstance();
    singleton *obj3 = singleton::getInstance();
    singleton *obj4 = singleton::getInstance();

    cout << obj2 << endl;
    cout << obj3 << endl;
    cout << obj4 << endl;

    return 0;
}
/*
    1.以上单列模式称为懒汉模式,通过if判断决定是否创建对象
    2.当再多线程同时执行getInstance()创建对象时，会出现内存泄漏
    3.如果使用饿汉模式，则可以避免以上情况
*/
//饿汉模式:初识化静态成员时，就先创建此类的对象
class singleton
{
    public:
        static singleton * getInstance();//返回静态对象的方法
    private:
        singleton();//构造函数私有化
        static singleton *instance;//静态属性
};
singleton *singleton::instance = new singleton;//初始化静态成员为类的对象
//在静态方法中，直接返回此对象
singleton * singleton::getInstance(){
    return instance;
}
singleton::singleton(){

}

int main(){
   // singleton *obj1 = new singleton;//因为构造函数私有化了，不能再通过这种方式创建对象
    singleton *obj2 = singleton::getInstance();
    singleton *obj3 = singleton::getInstance();
    singleton *obj4 = singleton::getInstance();

    cout << obj2 << endl;
    cout << obj3 << endl;
    cout << obj4 << endl;

    return 0;
}
/*
    饿汉模式是线程安全的
    与懒汉优缺点的比较：
    懒汉：在访问量较小时采用，以时间换空间
    饿汉：在访问量较大时或者访问线程比较多时采用，性能好。以空间换时间
    内存释放问题：一直占用内存到程序结束 
*/
//构造函数中的初始化人员
/*#include <iostream>
using namespace std;
class myclass{ 
    public:
        myclass(){},
        myclass(int a,int b, int c);
    private:
        int a,
        int b,
        int c
};
myclass::myclass(int a,int b,int c)
*/