/*
    C++的第三个特性 多态
    多态（动态多态）的成立基础是建立于继承之上的
    有动态多态，自然有静态duo tai ，静态多态是指函数重载
    一个函数名，参数不同功能不同

    动态多态：对本身能够跨过多层层级结构，进行各种其他类当中的方法的调用
    由继承，可以构成多层结构
    而多态就是在这样的多层结构当中，穿越调用其他层级当中的类的方法
*/
/*
#include <iostream>
class Base{
public:
    void func(){
        std::cout << "基类" << std::endl;
    }

};
class Dervied1:public Base{
public:
    void func(){
        std::cout << "派生类1" << std::endl;
    }
};
class Dervied2:public Base{
public:
    void func(){
        std::cout << "派生类2" << std::endl;
    }
};
using namespace std;
int main(){
    Dervied1 d;
    Base* p1 = &d;//基类指针指向派生类对象地址（栈空间）
    Base* p2 = new Dervied2;//基类指针指向派生类对象地址（堆空间）
    p1->func();
    p2->func();


    p1,p2调用func到底是调用Base Dervied1 Dervied2中的哪一个func取决于P1和P2的数据类型
    p1,p2现在都是Base*类型的，所以这两处的func调用的都是Base中的func
    所谓的动态多态，就是指：我们希望，当p1指向Derived1地址的时候，p1->func() 调用的是Derived1中的func，
    当p1改变指向，指向Derived2对象地址的时候，p1->func() 调用的几十Derived2中的func

    所以，即使基类指针指向了派生类对象的地址后，想要调用派生类重写后的基类方法也是失败
    原因在于到底调用什么取决于调用他的变量的类型
    那么到底要如何产生多态的效果呢（通过基类指针调用派生类的方法）？
    把想要多态的函数声明称虚函数
    多态的好处在于：简单，好用
    return 0;
}
*/
//下面多态好处的例子
/*
#include <iostream>

using namespace std;
//发工资系统为例
//讲师：1000 教授；3000 系主任：5000 院长：7000 
//C语言中使用多重判断循环
class Human{
public:
    int salary;
    virtual void setSalary(){}
    void show(){
        cout << "当前工资:" << salary << endl;
    }
};
class Teacher:public Human{
public:
    Teacher(){salary = 0;}
    void setSalary(){
        this->salary += 1000;
    }
};
class Professor:public Human{
public:
    Professor(){salary = 0;}
    void setSalary(){
        this->salary += 3000;
    }
};
class Dean:public Human{
public:
    Dean(){salary = 0;}
    void setSalary(){
        this->salary += 5000;
    }
};
class President:public Human{
public:
    President(){salary = 0;}
    void setSalary(){
        this->salary += 7000;
    }
};
void setSalary(Human** arr){
    int i = 0;
    //arr[0] == &t
    for ( i = 0; i < 4; i++)
    {
        arr[i] ->setSalary();
        //arr数据类型为Human** arr[i]数据类型为Human* ，基类指针、
        //假设多态成立的条件下当arr[i]指向不同对象地址的时候，所谓用的setSalary就会执行不同的逻辑（发放不同的工资）
    }
    
}
int main(){
    Teacher t;
    Professor p;
    Dean d;
    President pre;
    Human* arr[4] = {&t,&p,&d,&pre};

    int buf[20] = {0};//buf就是int*类型，该数组名指向了该数组首元素的地址
    setSalary(arr);

    int i = 0;
    for(i=0;i<4;i++){
        arr[i]->show();
    }
    return 0;
}
*/
//下面进入第三部分
/*
#include <iostream>
using namespace std;
class Base{
public:
    virtual void func(){
        cout << "基类" << endl;
    }
};
class Dervied:public Base{
public:
    void func(){
        cout << "派生类" << endl;
    }
};
int main(){
    cout << "Base类的大小为:" << sizeof(Base) << endl;
    //运行结果为：1个字节
    //1个不包含属性的类，无论写了多少种方法，他的大小永远为一个字节
    //函数存放于代码段，不在内存中
    //当我们为Base类中的func声明成virtual方法之后，再次查看Base类的大小为8个字节
    //8个字节为指针类型
    //当类当中出现虚函数之后，类当中就会多出一个指针
    //关键在于指针指向哪里
    //为什么多出了这样一个指针之后就是调用派生类的重新方法呢
    //该指针指向了虚函数列表，虚函数列表中存放了所以该类的虚函数
    //同理，当Base类派生出Derived类的时候，这个指向了虚函数列表的指针被Derived类确实的继承过来了
    //当Derived类重写了基类当中的虚函数之后，本质上就是将继承过来的虚函数列表当中的某个虚函数进行重写
    //当类中存在函数列表的话，基类指针再指向派生类对象地址后，调用方法会首先去虚函数列表中进行调用
    //如果此时派生类中的虚函数列表中的某个函数被改写了，自然调用的就是改写后的方法
    return 0;
}
*/
/*
#include <iostream>
using namespace std;
class Base{
public:
    Base(){
        cout << "基类构造" << endl;
    }
    ~Base(){
        cout << "基类析构" << endl;
    }
};
class Dervied:public Base{
public:
    Dervied(){
        cout << "派生类构造" << endl;
    }
    ~Dervied(){
        cout << "派生类析构" << endl;
    }
};
int main(){
    Base* p = new Dervied;
    delete p;

//  基类构造，派生类构造，这一套构造函数调用并不是由Base* p产生调用的，而是由new Derived产生调用的
//但是，在析构的时候，析构函数却是由delete p产生调用的，本质就是p ->析构函数，由于p是Base* 类型，所以delete p本质就是 p—>Base（），而不是p—>Dervied()
//p->Dervied(),才会先调用~Dervied(),再调用~Base()
//我们的目的是让p在delete的时候，调用派生类的析构函数，用多态就能达到这个目的
//需要注意：当有基类指针指向派生类对象地址的时候，一定要将基类的析构函数写成虚函数，否则派生类无法析构
    return 0;
}
*/
/*
#include <iostream>
using namespace std;
class Base{
public:
    Base(){
        cout << "基类构造" << endl;
    }
    ~Base(){
        cout << "基类析构" << endl;
    }
};
class Dervied:public Base{
public:
    Dervied(){
        cout << "派生类构造" << endl;
    }
    ~Dervied(){
        cout << "派生类析构" << endl;
    }
};
int main(){
//严格来说，由于C++对于数据类型的管控比较严格，基类指针指向派生类对象地址，严格上来说需要进行类型转换
//只不过在这件事情上，C++不多管

    Base* p = (Base*)(new Dervied);//强制数据累哦行转换，这个是C语言风格

    Base* p2 = static_cast<Base*>(new Dervied);//上行转换，也就是基类指针向下指指向派生类，C++风格
     
    //同理，派生类指针也哭呀指向基类,c++风格中关键字变了，上行转换使用关键字 dynamic_cast
    Dervied* d = dynamic_cast<Dervied*>(p2);
    Dervied* d2 = dynamic_cast<Dervied>(new Base); 
//222,223行代码在语法上没有问题，但是在实际运行过程中有区别
//d的话虽然指向p2(Base*类型)，但是p2本质上由指向了派生类的空间，此时如果派生类有额外拓展的属性的话，d所指向的就是派生类所指向的空间
//d2完完全全指向了基类的空间，也就是如果派生类有额外拓展属性的话，d2指向确实拓展之前的内存空间
//那么此时，d2如果去操作派生类的属性的话，就会报段错误
    return 0;
}
*/ 
/*
    多态的运用：设计模式
    通过对多态采用不用形式的应用，会产生不同的设计模式
        注意：虽然单例模式也属于设计模式，但是单例模式显然不是多态
    下面所写的是简单工厂模式，
    简单工厂模式运作方式：
        首先有一个工厂类，他专门创建不同的生产工具
        不同的生产工具可以制造不同的产品
    简单工厂类中，写一个创建不同生产工具的方法
        折柳说的生产工具其实其实就是一个基类，他底下可以有不同的派生类
        创建不同的生产工具，本质上就是说，构建不同的派生类对象
        不同的生产工具可以制造不同的产品，本质上就是说，不同的派生类对象可以通过同一个函数执行不同的逻辑
        所以，这里就是一个多态
            生产攻击基类指针 工厂类创建生产工具的函数(){
                 return 不同的生产工具的地址
            }
        外部调用吧生产工具函数，根据实参的不同，获取到不同的生产工具（也就是不同派生类地址），当然都是有基类指针去指向的
        通过该基类指针（实际上已经指向了不同的生产工具地址），直接生产方法，会生产相互不同的产品
            至于生产出什么样的产品，完全取决于基类指针指向什么生产工具（也就是创建生产工具函数到底返回来那个派生类对象的地址）
    很多设计模式当中，基类的作业就是为了有一个基类指针指向各种各样的派生类，基类根本不会去用到
        此时，我们最好将这个基类声明成纯虚类，纯虚类的特点就是：不能创建对象
        如何将一个类声明成纯虚类呢？只需在类当中写一个纯虚函数即可
        那么怎么讲一个虚函数变成纯虚函数呢？虚函数不用定义，只需要声明，并且在声明的最后写上 = 0；该虚函数就变成了纯虚函数
        有纯虚函数的类，就是纯虚类，无法创建对象，纯虚类无法创建对象
            所以，当有派生类继承自一个纯虚类的时候，注意一定一定重写纯虚函数，重写成一个普通函数

*/
/*
#include <iostream>
using namespace std;
class Base{
public:
    virtual void func() = 0;//纯虚函数

};
class Dervied:public Base{
public:
    void func(){}
};
int main(){
    Dervied d;
    return 0;
}
*/
//使用简单工厂模式，编写一个简易的 + — * / 计算机
//分析：计算机是工厂类，加减乘除类是生产工具类
//加法类的生产方式为：为两个数做加法
//减法类的生产方式为：为两个数做减法。这两个数可以保存在计算机类里面
//工厂类的创建生产工具函数：
//  返回值为：四则运算类的运算指针，形参为'+' '-' '*' '/'根据形参的不同返回不同的地址
//      形参为'+'，返回 new 加法类
//      形参为'-', 返回new 减法类

//最后，外部调用一下返回的类指针中的运算方法
/*
    如果四则运算下的简单工厂模式不好搞理解的话
    游戏中，打怪掉落装备就是简单工厂模式
        怪物根据他的难度，等级掉落不同属性的装备，所谓的不停属性的装备其实就是不同的派生类
        在掉落的时候，只需要根据怪物的难度/等级/各种其他条件，就能决定到底掉落哪一件装备，甚至可以进行随机掉落
*/
#include <iostream>
using namespace std;

class Operator{
    double x;
    double y;
public:
    virtual ~Operator(){}
    virtual double calculate() = 0;
    void setX(double x){this->x = x;}
    void setY(double y){this->y = y;}
    double getX(){return x;}
    double getY(){return y;}
};
//计算工具类
class Operator_add:public Operator{
public:
    double calculate(){
        return getX() + getY();
    }
};
class Operator_sub:public Operator{
public:
    double calculate(){
        return getX() - getY();
    }
};
class Operator_mul:public Operator{
public:
    double calculate(){
        return getX() * getY();
    }
};
class Operator_div:public Operator{
public:
    double calculate(){
        return getX() / getY();
    }
};
//工厂类
class Calculator{
public:
    Operator* oper(char ch){
            switch(ch){
                case '+' :
                    return new Operator_add;
                case '-' :
                    return new Operator_sub;
                case '*' :
                    return new Operator_mul;
                case '/' :
                    return new Operator_div;
                default:
                    return NULL;
            }
    } 
};
int main(){
    Calculator cal;
    double x = 0,y = 0;
    char ch = 0;

    cout << "请输入计算表达式:" << endl;
    cin >> x >> ch >> y;
    Operator* p = cal.oper(ch);
    p->setX(x);
    p->setY(y);
    double res = p->calculate();

    cout << x << ch << y << "=" << res << endl;
    return 0;
}