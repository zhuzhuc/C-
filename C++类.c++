/*
    构造函数：
    1.属于类中一个函数
    2.构造函数名与类名相同
    3.当由类创建对象时，构造函数会被自动调用
    4.构造函数没有返回值类型也没有返回值
    5.当提供了一个构造函数时，则必须把需要的构造函数全部提供。如果没有提供任何一个构造函数，则系统会自动生成一个无参的构造函数。
*/
#include <iostream>
#include <cstring>
using namespace std;

class Human
{
    private:
        char name[20];
        bool isMale;
        int age;
    public:
        void show();
        //函数重载：函数名相同参数个数或者参数类型不同
        Human(const char *name,bool isMale, int age);
        Human();

        void setName(const char *name);
        char *getName();

        void setIsMale(bool m);
        bool getIsMale();

        void setAge(int a);
        int getAge();

};
Human::Human(){
    cout << "调用了无参数的构造函数\n";
    //增加 设置默认属性成员的值的 代码
}
Human::Human(const char *name,bool isMale, int age){
    cout << "有三个参数的构造函数被自动调用了" <<endl;
    strcpy(this->name,name);//this保存由类生成的对象的地址
    this->isMale = isMale;
    this->age = age;
    printf("%p\n", this);
}
void Human::show(){
    cout <<"name:" << name << endl;
    cout <<"sex:" << (isMale?"nan":"nu:")<< endl;
    cout <<"age:" << age << endl;
}
void Human::setName(const char *n){
    strcpy(name,n);
}
char *Human::getName(){
    return name;
}
void Human::setIsMale(bool m){
    isMale = m;
}
bool Human::getIsMale(){
    return isMale;
}
void Human::setAge(int a){
    age = a;
}
int main()
{
    /*
    Human zhangsan ("zhangsan", true,22);
    zhangsan.show();
    printf("%p\n", &zhangsan);
    zhangsan.setAge(23);
    zhangsan.show();
    Human lisi("lisi",false,33);
    lisi.show();
    printf("%p\n", &lisi);
    lisi.setName("liwu");
    lisi.show();
    */
    Human zhangsan;//自动调用无参构造函数
    zhangsan.setName("张三");
    zhangsan.setAge(19);
    zhangsan.setIsMale(true);

    zhangsan.show();

    Human lisi("lisi", true,40);//调用有三个参数的构造函数
    lisi.show();
    return 0;
}
/*
    析构函数
    1.与构造函数类似
    2.析构函数的函数名是用类名前面添加~
    3.析构函数没有参数
    4.析构函数是当对象销毁时自动调用，但是也可以手动调用。一般不手动调用
    5.析构函数的自动调用顺序：先创建的对象后析构，后创建对象
*/
#include <iostream>
#include <cstring>
using namespace std;

class Human
{
    private:
        char name[20];
        bool isMale;
        int age;
    public:
        void show();
        //函数重载：函数名相同参数个数或者参数类型不同
        Human(const char *name,bool isMale, int age);
        Human();

        ~Human();
        void setName(const char *name);
        char *getName();

        void setIsMale(bool m);
        bool getIsMale();

        void setAge(int a);
        int getAge();

};
Human::~Human(){
    cout << "析构函数被调用了。\n";\
    printf("%p\n",this);
}
Human::Human(){
    cout << "调用了无参数的构造函数\n";
    //增加 设置默认属性成员的值的 代码
}
Human::Human(const char *name,bool isMale, int age){
    cout << "有三个参数的构造函数被自动调用了" <<endl;
    strcpy(this->name,name);//this保存由类生成的对象的地址
    this->isMale = isMale;
    this->age = age;
    printf("%p\n", this);
}
void Human::show(){
    cout <<"name:" << name << endl;
    cout <<"sex:" << (isMale?"nan":"nu:")<< endl;
    cout <<"age:" << age << endl;
}
void Human::setName(const char *n){
    strcpy(name,n);
}
char *Human::getName(){
    return name;
}
void Human::setIsMale(bool m){
    isMale = m;
}
bool Human::getIsMale(){
    return isMale;
}
void Human::setAge(int a){
    age = a;
}
int main()
{
    Human zhangsan;//自动调用无参构造函数
    zhangsan.setName("张三");
    zhangsan.setAge(19);
    zhangsan.setIsMale(true);
    zhangsan.~Human();
    zhangsan.show();

    Human lisi("lisi", true,40);//调用有三个参数的构造函数
    lisi.show(); 
    return 0;
}


//作业：使用指针和引用分别完成以上类似的功能
//使用指针
#include <iostream>
using namespace std;

int main(){
    int a = 100;
    int* p = &a; // 声明一个指针p，指向a的地址

    cout << "a=" << a << endl;
    cout << "a的地址:" << &a << endl;

    cout << "p=" << *p << " p的地址:" << p << endl;

    *p = 300;
    cout << "a=" << a << endl << "p=" << *p << endl;
    return 0;
}
//使用引用
#include <iostream>
using namespace std;

int main(){
    int a = 100;
    int& b = a; // 声明了一个引用变量b，它是a的别名
    //声明引用变量时，必须初始化

    cout << "a=" << a << endl;
    cout << "a的地址:" << &a << endl;

    cout << "b=" << b << " b的地址:" << &b << endl;

    b = 300;
    cout << "a=" << a << endl << "b=" << b << endl;
    return 0;
}
//变式
#include <iostream>
using namespace std;

int main(){
    int a = 100;
    int& b = a; // 声明了一个引用变量b，它是a的别名
    //声明引用变量时，必须初始化

    cout << "a=" << a << endl;
    cout << "a的地址:" << &a << endl;

    cout << "b=" << b << " b的地址:" << &b << endl;

    b = 300;
    cout << "a=" << a << endl << "b=" << b << endl;

    int x = 1;
//  int &y;//声明的引用变量Y必须初始化 否则error
//  y = x;
    int &y = x;//y是x的引用 永远表示x
    cout << y << endl << &y << endl;
    y = a;
    cout << y <<endl << &y << endl;
    cout << x <<endl << &x << endl;
    //&y = a;//error

    cout << "***************"<< endl;
    int s = 50;
    const int &t = s;
    //t = 60;
    return 0;
} 
#include <iostream>
int main(){
    int a = 100;
    a = 200;

    const int b = 10;
//  b = 20;//error

    int const c = 90;
//  c = 9;//error

    int *pa = &a;
    *pa = 300;
    cout << "a=" << a << endl;

    const int *pb = &a;
//  *pb = 400;//error

    int const *pc = &a;
//  *pc = 500;//error
    pc = &b;
    cout << "*pc:" << *pc << endl;

    const int * const pf = &a;
//  *pf = 10000;//error
//  pf = &b;//error

    int * const pd = &a;
//  pd = &b;//error
    *pd = 1000;
    cout << a << endl;

    const int s = 50;
    const int &t = s;
    //t = 60;//error :t是const类型的引用变量
    //s = 60;
    cout << t << endl;

    const int u = 999;
    const int &v = u;
//  u = 888;//error
//  v = 666;//error

    return 0;

}
/*
    拷贝函数构造
    1.是构造函数的一种
    2.形参是类的对象的const引用
    3.作用是：当创建对象时，实参是该类另一个对象，用此对象创建一个新对象
    4.也可以完成对象复制
*/
#include <iostream>
#include <cstring>
using namespace std;
class Person{
    private:
        int age;
        char name[20];
        bool isMale;
    public:
        Person();
        Person(int age,const char *name, bool  isMale);
        ~Person();
        void show();
        //拷贝构造函数
        Person(const Person &Person);
};
Person::Person(){
    age = 0;isMale = false;
    strcpy(name, "\0");
    cout << "Person()" << endl;

}
Person::Person(int age,const char *name, bool isMale){
    this->age = age;
    this->isMale = isMale;
    strcpy(this->name,name);
    cout << "Person(int age,char *name,bool isMale)\n";
}
Person::~Person(){
    cout << "~Person()" << endl;
}
Person::Person(const Person &person){
    this->age = person.age;
    this->isMale = person.isMale;
    strcpy(this->name,person.name);
}
Person::show(){
    cout << "姓名：" << name << endl;
    cout << "年龄；" << age << endl;
    cout << "性别：" << (isMale?"男":"女") << endl;
}
int main(){
    Person p1;//自动调用无参构造函数
    p1.show();
    cout << endl;

    Person p2(18,"wangwu",true);//自动调用有三个参数的构造函数
    p2.show();
    cout << endl;

    Person p3(p2);
    return 0;
}