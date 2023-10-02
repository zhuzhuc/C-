#include <stdio.h>
#include <iostream>
using namespace std;
/*int mian()
{
    std::cout << "hello" << std::endl;
    return 0;
}
//分别使用两个命名空间写print函数打印命名空间
int main(){
//使用命名空间中的标识符；方法1.通过作用域运算符（：：）
    intel::myprint();
    intel::myprint();
    intel::myprint();
    //方法2.using 声明一个标识符
    {   using huawei::myprint;
        myorint();
        myorint();
        myorint();
    
    }
    //方法3.using 编译方式， 吧指定命名空间中的所有标识符全部编译到当前源文件中
    using namespace zhongxin
    myprint();
    myprint2();

    return 0;

}*/
//结构体完成以下功能
struct Person{
    char name[20];
    int age;
    bool isMale;//布尔类型， true和false

};
void show(Person *person){
    cout << "name:" << person->name << endl;
    cout << "age:" << person->age << endl;
    if (person->isMale)
    {
        cout << "sex:boy" << endl;
    }
    else{
        cout << "sex:girl" <<endl;
    }
    
}
//类的方式实现以上功能
//在类的声明中
//成员默认是private私有的，不能通过类的对象来访问
//可以通过使用public关键字把成员定义成公有的，就可以通过类的对象来访问
//类中成员大多数情况下是私有的，只能通过类中提供的共有方法来操作类中成员
//在类中添加方法/函数 
//成员的访问限制符：public private
//接口隔离：给每个属性成员提供独立 的接口，实现对内存的存取操作
//在类的接口方法中可以访问私有成员
class Human
{
    private:
        char name[20];
        bool isMale;
        int age;
    public:
        void setName(char *name);
        char *getName();

        void setIsMale(bool m);
        bool getIsMale();

        void setAge(int a);
        int getAge();

        void show();
};
void Human::setName(char *n){
    strcpy(name,n);
}
char *Human::getName(){
    return name;
}

void Human::show(){
    cout << "name:" << name << endl;
    cout << "age:" << age << endl;
    if (isMale)
    {
        cout << "sex:boy" << endl;
    }
    else{
        cout << "sex:girl" <<endl;
    }
    
}
int main(){
    //struct Person person = {"zhangsan",20,true};
    //show(&person);
    //Person person2 = {"wangwu",23,false};
    //show(&person2);

    Human human = {"wangwu", 23,false};
    human.show();
    Human human2 = {"xiaoming", 23,false};
    human2.show();
    return 0;
}