class Foo
{
private:
    int _i;
public:
    Foo(int i) : _i(i) {}
    Foo() = default;

    Foo(const Foo& x) : _i(x._i) {}
    // Foo(const Foo& x) = default; //[Error] 'Foo::Foo(const Foo&)' cannot be overloaded
    // Foo(const Foo& x) = delete; //[Error] 'Foo::Foo(const Foo&)' cannot be overloaded
    
    Foo& operator=(const Foo& x)  { _i = x._i; }
    // Foo& operator=(const Foo& x) = default; //[Error] 'Foo& operator=(const Foo& x)' cannot be overloaded
    // Foo& operator=(const Foo& x) = delete; //[Error] 'Foo& operator=(const Foo& x)' cannot be overloaded

    //void func1() = default; // [Error] 'Foo::Foo(const Foo&)'
    void func2() =delete;    // ok
    //~Foo = delete; //这会造成使用Foo object时出错=》[Error] use of deleted function 'Foo::~Foo()'
    ~Foo() = default;
};

int main(){
    Foo f1(5);
    Foo f2; // 如果没有写出=defualt版本 =》 [Error] no matching function for call to 'Foo:Foo()'
    Foo f3(f1);  //如果copy ctor = delete； [Error] use of deleted function 'Foo:Foo(const Foo&)'
    f3 = f2;  // 如果copy assign = delete; [Error] use of deleted function 'Foo& operator=(const Foo& x)'
}

// =defualt; 用于Big-Five之外是何意？无意义，编译报错。
// =delete;可用任何函数身上。（=0只能于virtual函数）