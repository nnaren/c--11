#include<stddef.h>  // size_t
#include<string.h>  // memcpy
class MyString
{
private:
    char* _data; // 指针成员需要拷贝构造，拷贝复制，析构
    size_t _len;
    void _init_data(const char *s) {
        _data = new char[_len+1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }
public:
    static size_t DCtor;    // 累计default-ctor呼叫次数
    static size_t Ctor;     // 累计ctor呼叫次数
    static size_t CCtor;    // 累计copy-ctor呼叫次数
    static size_t CAsgn;    // 累计copy-asgn呼叫次数
    static size_t MCtor;    // 累计move-ctor呼叫次数
    static size_t MAsgn;    // 累计move-asgn呼叫次数
    static size_t Dtor;     // 累计dtor呼叫次数
    //default constructor
    MyString() : _data(nullptr),_len(0)  { ++DCtor; }

    //constructor
    MyString(const char* p) : _data(nullptr),_len(0)  {
        ++Ctor;
        _init_data(p); 
    }
    //copy constructor
    MyString(const MyString& str) : _len(str._len)  {
        ++CCtor;
        _init_data(str._data); 
    }

    //move constructor, with "noexcept"
    MyString(MyString&& str)  noexcept 
        : _data(str._data), _len(str._len)  {
        ++MCtor;
        str._len = 0;
        str._data = nullptr; 
    }

    //copy assignment
    MyString& operator=(const MyString& str)   {
        ++CAsgn;
        if(this != &str) // 自我赋值检查
        {
            _len = str._len;
            _init_data(str._data); 
        } else {}
        return *this;
    }
    //move assignment
    MyString& operator=(MyString&& str)  noexcept  {
        ++MAsgn;
        if(this != &str) // 自我赋值检查
        {
            if (_data)  delete _data;
            _len = str._len;
            _data = str._data;  // MOVE!
            str._len = 0;
            str._data = nullptr;    //重要
        } 
        return *this;
    }
    //dtor  
    // destructor is noexcept by default.
    virtual ~MyString() {
        ++Dtor;
        if(_data) {
            delete _data;
        }
    }
};