//继承
/*
    C++的第二个特性：继承
    继承的概念：
        类通过继承的方式，构成了一系列的结构，一个类包含了另一个类，我们称为继承
        被包含的类，我们称为基类
        包含基类的类我们称为派生类
    如何继承呢？在类的类名后使用：进行继承
    举例 基类如下
    class Base{

    };
    派生类继承自基类，如下
    class Dervied:public Base{

    };
    Dervied 继承自Base类
    继承过后，Devied类拥有Base类当中的所有成员属性和方法
    但是中间又有很多变数

    那么，在构建派生类对象的时候，构造函数和析构函数是如何执行的那？
        派生类对象会现在内部构建基类，所以才会拥有基类的所有属性
        基类构建完成后，再去构建派生类自己的拓展部分

        day8项目现在是将所有的属性设置成了公开属性
        如果把这些输入设置私有之后，会发生什么
*/
/*
#include <iostream>
using namespace std;
class Base{
public:
    int a;
    char b;
    Base(){
        cout << "基类构建" << endl;
    }
    ~Base(){
        cout << "基类析构" << endl;
    }
};
class Dervied:public Base{

    double c;
    Dervied(){
        cout << "派生类构造" << endl;
    }
    ~Dervied(){
        cout << "派生类析构" << endl;
    }
};
int main(){
    Dervied d;
    return 0;
}*/
//下面将公开属性私有化
#include <iostream>
using namespace std;
class Base{
    int a;
    char b;
    
public:
    Base(){}
    Base()
        a(a),b(b)
    {
        cout << "基类构建" << endl;
    }
    ~Base(){
        cout << "基类析构" << endl;
    }
    int getA(){return a;}
    char getB(){return b;}

    void setA(int a){this->a = a;}
    void setB(int b){this->b = b;}
};
class Dervied:public Base{
public:
    Dervied(int a, char b):
    Base(a,b);
    {
        cout << "派生类构造" << endl;
    }
    ~Dervied(){
        cout << "派生类析构" << endl;
    }
    void show(){
        cout << "a = " << getA() << endl;
        cout << "b = " << getB() << endl;
    }
};
int main(){
    Dervied d(10, "x");
    d.show();
    return 0;
}
//当这段代码将公开属性私有化之后，派生类中的内部访问私有成员失效
//编译错误告诉我们：派生类正在试图访问基类的私有成员
//原因在于：派生类中的基类属性，并不是以单独的变量存在的，而是以基类对象中包含的成员属性的形式存在
//派生类和基类仅仅是继承关系，不是友缘关系，即使派生类包含了基类，但是他两就是不同的类
//类似于，在一个自定义类当中，存放另一个类，被存放的类他的私有成员因为同样的道理无法访问
//那怎么办？和之前同样的方法，私有成员应该如何访问，使用set get 接口
//  但是，这个set get接口应该写在基类当中
//  然后由派生类继承set get接口，继承过后的set get接口，由派生类调用的时候，会准确的访问基类的私有成员
//上面这个代码使用构造函数初始化数据的方式是很死板的
//我们总是希望通过传参的形式，去初始化我们的私有成员
//通过构造函数初始化属性的方法，有一个高效的方法；列表初始化
//问题在于，列表初始化的本质其实就是 this->a = 参数a
//但是派生类当中并没有属性叫a,a是属于基类的私有成员
//当然，派生类也可以使用列表初始化去初始化基类的私有成员
//但是直接使用列表初始化基类的私有成员不行
//方法：首先将基类的列表初始化完善好,然后在派生类的列表初始化的地方，直接调用基类的初始函数