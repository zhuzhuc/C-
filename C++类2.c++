//使用已经存在的一个对象去初始化一个心创建的对象
//有三种情况会自动调用 但这三种情况本质是一样的
//1；使用一个对象去创建另一个对象
//2:当函数的参数是一个对象时
//3：当函数的返回值是一个对象时，此时理论上会调用拷贝构造函数，但是如果返回的是一个局部对象，
//则编译器会优化为将局部对象的地址和函数表达式的返回地址一致
//如果函数调用出现在等号右侧（右值），会把函数的返回地址赋值给等号左侧的变量（左值）

#include <iostream>
#include <cstring>
using namespace std;
class Myclass{
    public:
        Myclass();
        Myclass(const Myclass *myclass);
        Myclass(Myclass &myclass);
};
Myclass::Myclass(){
    cout << "Myclass()" << endl;
};
Myclass::Myclass(const Myclass *myclass){
    cout << "Myclass(const Myclass *myclass)" << endl;
};
Myclass::Myclass(Myclass &myclass){
    cout << "Myclass(Myclass myclass)" << endl;
};

void test1(Myclass myclass){
    cout << "test1" << endl;
    return ;
}
Myclass test2(){
    cout << "test2" << endl;
    Myclass myclass;
    cout << &myclass << endl;
    return myclass;
}

int main(){
    Myclass my1;
    Myclass my2(&my1);
    Myclass my3(my1);
    cout << "**************\n";
    test1(my1);
    cout << "**************\n";
    Myclass my4 = test2();
    cout << "&my4:" << &my4 << endl;
    cout << "**************\n";

    return 0;
}
//创建mystring类
/*
    C++中字符串类string类的使用方法
    1.获取字符串长度的方法：size()length()
    2.给当前字符串追加新的字符串：append()
    3.将string类的字符串转换成const char*类型
        方法1：data()
        方法2：c_str()
    4.清空字符串：clear()
        memset(str,NULL,strlen(str)
    5.判断一个字符串是否为空：empty
        当字符串为空时结果为1，否则为0
    以上为字符串方法

    与字符串相关的函数
    1.字符串转整型:stoi是C11标准C98无法使用
        函数原型：int stoi(const string & str,size_t *idx=0,int base=10)
        第一参数必须 第二和第三参数可以省略   
    2.整型数据转换字符串
        函数原型：string to_string(整数数据)
*/
#include <iostream>
#include <string.h>
using namespace std;
int main(){
    string str = "hello wortld";
    string str2 = "hello world-strd2";
    cout << str << endl;
    cout << str2 << endl;

    cout << str.size() << endl;
    cout << str2.length() <<endl;

    str.append("China");
    cout << str << endl;

    const char *pstr = str.data();
    cout << pstr << endl;
    cout << pstr[13] << endl;

    str.clear();
    memset((void *)pstr,NULL,strlen(pstr));
    cout << str <<endl;
    cout << pstr <<endl;

    cout << str.empty() << endl;
    cout << str2.empty() << endl;

    str = "789";
    cout << stoi(str) * 2 << endl;
    str = "123";
    cout << stoi(str) * 2 << endl;
    cout << stoi(str,0,8) *2 << endl;
    cout << stoi(str,0,16) *2 << endl;
    cout << stoi(str,0,4) *2 << endl;
    cout << stoi(str,0,3) *2 << endl;

    str = "1abcd";
    cout << stoi(str) *2 << endl;
    cout << stoi(str,0,16) *2 << endl;

    str = "0xab"
    cout << stoi(str,0,16) << endl;
    cout << stoi(str,0,8) << endl;//自动识别是几进制

    int x= 678;
    str = to_string(x);
    cout << str << endl;
    cout << str.length() << endl;
    return 0;
}
#include <iostream>
#include <cstring>

using namespace std;
class MyString
{
    private:
        char *str;//用指针保存字符串的首地址，不用数组
        int len;//用来保存字符串的长度

    public:
        MyString();
        MyString(const char *);
        MyString(const MyString &);
        ~MyString();
        void show(){//内联函数
            cout << str << endl;
        }
        int size(){
            return len;
        }
        const char *data(){
            return str;
        }
        void clear();
        bool empty();
        int toInt;
        void append(const MyString &);

};
MyString::~MyString(){
    free(str);
    cout << "释放了当前对象\n";
}
MyString::MyString(){
    //初始化一个空字符串，长度为0
    len = 0;
    //为空字符串分配一个字节，存放'\0' 意味着str确定指向某个空间，当释放时不用再判断str指针是否为空指针
    str = (char *)malloc(1);
    str[0] = '\0';
}
MyString::MyString(const char * s){
    len = strlen(s);
    str = (char *)malloc(len);
    memset(str,0,len+1);
    strcpy(str,s);
}
MyString::MyString(const MyString & s){
    len = s.len;
    str = (char *)malloc(len);
    memset(str,0,len+1);
    strcpy(str,s.str); 
}
void MyString::append(const MyString & s){
    len = len + s.len;
    char *temp = str;
    this->str = (char *)malloc(len + 1);
    memset(str,0,len+1);
    strcpy(str,temp);
    strcat(str,s);
    free(temp);
}
void MyString::clear(){
    free(str);
    len = 0;
    str = (char *)malloc(1);
    str[0] = '\0';
}
bool MyString::empty(){
    if (len == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}    

int main(){
    MyString str1;
    str1.show();
    cout << str1.size() << endl;
    cout << "**************\n";

    MyString str2("hello world");
    str2.show();
    cout << str2.size() << endl;
    cout << "**************\n";

    
    MyString str3(str2);
    str3.show();
    cout << str3.size() << endl;
    cout << "**************\n";

    str3.append("CHINA");
    str3.show();
    cout << str3.size() << endl;
    cout << str3.empty() << endl;
    cout << "**************\n";
    
    
    str3.clear();
    str3.show();
    cout << str3.size() << endl;
    cout << str3.empty() << endl;
    
    return 0;
}