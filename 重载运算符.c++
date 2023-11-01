#include <iostream>

class Vector {
private:
    double x;
    double y;

public:
    Vector(double xVal = 0, double yVal = 0) : x(xVal), y(yVal) {}

    // 重载 "+" 运算符
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }

    // 重载 "<<" 运算符用于输出向量
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);

    // 重载 "==" 运算符用于比较向量是否相等
    bool operator==(const Vector& other) const {
        return (x == other.x && y == other.y);
    }
};

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

int main() {
    Vector vec1(1, 2);
    Vector vec2(3, 4);

    // 使用重载的 "+" 运算符对向量进行相加
    Vector result = vec1 + vec2;

    std::cout << "vec1 + vec2 = " << result << std::endl;

    // 使用重载的 "==" 运算符比较两个向量是否相等
    bool isEqual = (vec1 == vec2);

    if (isEqual) {
        std::cout << "vec1 and vec2 are equal." << std::endl;
    } else {
        std::cout << "vec1 and vec2 are not equal." << std::endl;
    }

    return 0;
}
```

在上面的代码中，我们创建了一个名为`Vector`的自定义类，其中包含了两个私有成员变量`x`和`y`，表示向量的坐标。然后，我们重载了 "+" 运算符，用于将两个向量相加并返回一个新的向量。我们还重载了 "<<" 运算符，使其适用于向量的输出。此外，我们还重载了 "==" 运算符，用于比较两个向量是否相等。

在`main()`函数中，我们创建了两个`Vector`对象`vec1`和`vec2`，然后使用重载的 "+" 运算符将它们相加，将结果存储在`result`变量中，并通过重载的 "<<" 运算符输出结果。接着，我们使用重载的 "==" 运算符比较`vec1`和`vec2`是否相等，并根据结果输出相应的信息。

这个例子展示了如何重载运算符来实现自定义类型的操作，可以根据实际需求重载其他运算符，并根据具体情况调整运算符的行为。