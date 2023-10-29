/*
    函数重载
        1.在C++中可以存在多个相同函数名的函数
        2.函数名相同，参数列表必须不同，函数返回值类型可以相同也可以不相同
        3.当调用重载函数时，编译器会根据传参不同，找到合适的重载函数
*/
#include <iostream>
using namespace std;
int myfun(int a, int b){
    cout << "int myfun(int a,int b)\n";
    return a + b;
}
double myfun(double a, double b){
    cout << "double myfun(double a,double b)\n";
    return a + b;
}
int main(){
    int i1 = 10,i2 = 20;
    int i3 = myfun(i1, i2);//最佳匹配：实参与形参完全一致
    cout << i3 << endl;
    cout << "********" << endl;

    double d1 = 0.5,d2 = 9.9;
    double d3 = myfun(d1,d2);//最佳匹配：实参与形参完全一致

    cout << d3 << endl;

    string s1("abc"),s2("12345");
    //string s3 = myfun(s1, s2);//无匹配//error


    return 0;
}
int main(){
    double d1 = 0.5;
    int d2 = 9;
    //double d3 = myfun(d1,d2);//多重匹配//error
    //cout << d3 << endl;

    char c1 = 'a',c2 = 'b';
    int c3 = myfun(c1, c2);//提升匹配：实参与形参不一致，但可以自动类型转换到匹配的参数类型
    cout << c3 << endl;

    float f1 = 0.5, f2 = 9.8;
    double f3 = myfun(f1,f2);//提升匹配：实参与形参不一致，但可以自动类型转换到匹配的参数类型
    cout << f3 << endl;

    return 0;
}
//使用函数重载实现乘方功能
/*
    乘方
        x^n
    X可以是整型，也可以是浮点类型
*/
#include <iostream>
using namespace std;
int mypow(int x, int n){
    int temp = 1;
    for (int i = 0; i <= n; i++)
    {
        temp *= x;
    }
    return temp;
}
double mypow(double x, int n){
    double temp = 1.0;
    for (int i = 0; i <= n; i++)
    {
        temp *= x;
    }
    return temp;
}
int main(){
    cout << mypow(2,10) << endl;
    cout << mypow(2.1,10) << endl;
    return 0;
}
/*
    函数的默认参数
    当调用一个函数时，如果实参个数少于形参个数，则参数值会自动采用一个默认值，此默认值为默认参数

    声明一个函数时，给形参一个默认值，此默认值当实参没有提供时自动使用

    声明函数时，提供默认值时，必须从右到左顺序提供
*/
#include <iostream>
using namespace std;
int myfun(int a, int b, int c = 0,int d = 0){
    return a + b + c + d;
}
class car{
    public:
        car(){};
        car(const string &name,int weight, int wheel = 4):weight(weight),wheel(wheel),name(name){

        };
        ~car(){};
        void print(){cout << name << endl << weight << endl << wheel << endl;}
    private:
        string name;
        int weight;
        int wheel;
};
int mian(){
    cout << myfun(1,2,3,4) << endl;
    cout << myfun(1,2,3) << endl;
    //cout << myfun(1,2) << endl;

    car mycar("Audi", 10000);//没有给wheel形参值，会采用默认值
    mycar.print();
    return 0;
}
/*
    有默认参数的函数与重载函数
    有默认参数的函数与重载函数都声明时，要避免多重匹配产生的二义性

*/
int myfun(int a, int b, int c = 0,int d = 0){
    return a + b + c + d;
}
int myfun(int a, int b){
    return a + b;
}
int mian(){
    cout << myfun(1,2,3,4) << endl;
    cout << myfun(1,2,3) << endl;
    //cout << myfun(1,2) << endl;//多重匹配，产生二义性//error


    return 0;
}
//作业：提供两个参数且其中一个参数有默认值的函数，再提供一个有一个参数的重载还能输，尝试调用，并导致多重匹配
//要求参数为字符串string类型
#include <iostream>
#include <string>

// 函数重载，带一个参数的版本
void foo(std::string arg) {
    std::cout << "foo with one argument: " << arg << std::endl;
}

// 函数重载，带两个参数的版本
void foo(std::string arg1, std::string arg2 = "default") {
    std::cout << "foo with two arguments: " << arg1 << ", " << arg2 << std::endl;
}

int main() {
    std::string str1 = "Hello";
    std::string str2 = "World";

    // 调用带一个参数的函数重载
    foo(str1);

    // 调用带两个参数的函数重载
    foo(str1, str2);

    // 导致多重匹配错误，无法确定使用哪个重载
    foo(str1, "another");

    return 0;
}
/*
foo with one argument: Hello
foo with two arguments: Hello, World
error: call to 'foo' is ambiguous
*/
/*
    内联函数：
        普通函数声明时，前面加上关键字inline修饰，则此函数成为内联函数
        内联函数调用时，编译器会把内联函数对应的代码直接复制到主函数的调用处，类似于符号常量
        调用内联时，不会为内联分配运行内存，直接在主调函数中运行，节省分配空间及从参数传递时间
        内联函数并不是100%内联，是否在调用处展开内联函数代码，由编译器决定
        在类中，如果类的方法是在类的定义中直接实现的，则此方法编译器会自动加上inline关键字，并按内联函数进行处理
*/
#include <iostream>
using namespace std;
inline void print(){
    cout << "inline void print()" << endl;
}

int main(){
    print();
    return 0;
}
/*
    友元函数：
        一个特别的普通函数，不是类的成员，但是友元函数可以直接访问类的私有成员变量。
    在类中使用friend关键字声明类的友元函数，必须声明
    在友元函数中可以访问类的私有成员      
*/
#include <iostream>
using namespace std;

class car{
    friend void print(car c);
    public:
        car(){}; 
        car(string &name,int weight):name(name),weight(weight){};
        ~car(){};
    private:
        string name;
        int weight;
};
void print(car c){
    cout << c.name << endl << c.weight << endl;//直接操作私有成员
};
int mian(){
    car mycar("Audi",20000);
    car mycar2("Audi rs7 sportback",2000000);
    print(mycar);
    print(mycar2);
    return 0;
}
/*
    两个类把同一个函数声明为友元函数
*/
#include <iostream>
using namespace std;

//类的前置声明：当两个类相互包含的时候，必须前置声明
class A;
class B;

class A{
    friend void print(A &a,B &b);
    private:
        int a;
    public:
        A(int a = 0);
};
A::A(int a):a(a){}
class B{
    friend void print(A &a,B &b);
    private:
        int b;
    public:
        B(int b = 0);
};
B::B(int b):b(b){}
void print(A &a,B &b){
    cout << "a:" << a.a << endl;
    cout << "b:" << b.b << endl;
}
int main(){
    A a(1);
    B b(2);
    print(a,b);
    return 0;
}

#include <iostream>
using namespace std;
class A{
    friend class B;//类B是类A的友元类
    private:
        int a;
    public:
        A(int a = 0);
};
A::A(int a):a(){}
class B{
    private:
        int b;
    public:
        B(int b = 0);
        void print(A &a);
};
B::B(int b):b(){}
void B::print(A &a){
    cout << "a:" << a.a << endl;
    cout << "b:" << b << endl;

}
int main(){
    A a(10);
    B b(20);
    b.print(a);
    return 0;
}

/*
    一个类A把另一个类声B明为友元类
    则友元类B中的所有函数都可以直接通过类A的对象直接访问类A中的私有成员
*/
/*
    实现两个复数相加：例如 （10+2i） + （5+4i） = 15+6i
    a+bi     +     c+di

    对复数自增运算
    (a+bi)++
    或者
    ++(a+bi)
*/
#include <iostream>
using namespace std;
class Imag{
    private:
        int real,imag;
    public:
        Imag(int real = 0,int imag = 0);
        void print(){
            cout << "real:" << endl;
            cout << "imag:" << endl; 
        }
        int getReal(){return real;}
        int getImag(){return imag;}
        void setReal(int r){real = r;}
        void setImag(int i){imag = i;}
};
Imag::Imag(int real,int imag):real(real),imag(imag){}
//运算符重载，也是函数重载,只不过函数名比较特别
Imag operator+(Imag &left,Imag &right){
    int real = left.getReal() + right.getReal();
    int imag = left.getImag() + right.getImag();
    Imag temp(real,imag);
    return temp;
    //return Imag(real,imag);
}
//对复数自增运算
Imag operator++(Imag &right){//++在前，实现++(a+bi)
    right.setReal(right.getReal()+1);
    right.setImag(right.getImag()+1); 
    return right; 
}
Imag operator++(Imag &left){//++在后，实现(a+bi)++
    Imag temp(left);
    left.setReal(left.getReal()+1);
    left.setImag(left.getImag()+1);
    return temp;
}
int main(){
    //Imag i1(10,2), i2(5,4);
    //i1.print();
    //i2.print();
    //只有实现了针对Imag类的对象的加操作，加号才可以使用
    //Imag i3 = i1 + i2;
    //i3.print();此部分以下为复数自增运算
    Imag i1(10,2),i2(5,4);
    i1.print();
    i2.print();
    cout << "****************\n"
    ++i1;
    i1.print();
    i2++;
    i2.print();
    return 0;
}

//作业：参考以上功能，写出- * / < > == 
//实现减法运算符重载函数
Imag operator-(Imag &left, Imag &right){
    int real = left.getReal() - right.getReal();
    int imag = left.getImag() - right.getImag();
    Imag temp(real, imag);
    return temp;
}

//实现乘法运算符重载函数
Imag operator*(Imag &left, Imag &right){
    int real = left.getReal() * right.getReal() - left.getImag() * right.getImag();
    int imag = left.getImag() * right.getReal() + left.getReal() * right.getImag();
    Imag temp(real, imag);
    return temp;
}

//实现除法运算符重载函数
Imag operator/(Imag &left, Imag &right){
    int denominator = right.getReal() * right.getReal() + right.getImag() * right.getImag();
    int real = (left.getReal() * right.getReal() + left.getImag() * right.getImag()) / denominator;
    int imag = (left.getImag() * right.getReal() - left.getReal() * right.getImag()) / denominator;
    Imag temp(real, imag);
    return temp;
}

//实现小于运算符重载函数
bool operator<(Imag &left, Imag &right){
    if (left.getReal() < right.getReal())
        return true;
    else if (left.getReal() == right.getReal() && left.getImag() < right.getImag())
        return true;
    else
        return false;
}

//实现大于运算符重载函数
bool operator>(Imag &left, Imag &right){
    if (left.getReal() > right.getReal())
        return true;
    else if (left.getReal() == right.getReal() && left.getImag() > right.getImag())
        return true;
    else
        return false;
}

//实现等于运算符重载函数
bool operator==(Imag &left, Imag &right){
    return (left.getReal() == right.getReal()) && (left.getImag() == right.getImag());
}

