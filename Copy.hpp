struct NoCopy
{
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;
    NoCopy &operator=(const NoCopy&) = delete;
    ~NoCopy() = default; 
};


struct NoDtor
{
    NoDtor() = default;
    ~NoDtor() = delete; 
};
void test()
{
    NoDtor nd;   // error： NoDtor destructor is deleted
    NoDtor *p = new NoDtor(); // ok:but we can't delete p
    delete p; //error:NoDtor destructor is deleted
}

struct PrivateCopy
{
private:
    // no access specifier, following members are private by defualt;
    // copy control is private and so is inaccessible to ordinary user code
    PrivateCopy(const PrivateCopy&) ;
    PrivateCopy &operator=(const PrivateCopy&) ;
    // other members
public:
    PrivateCopy() = default; // use the systhesized default constructor
    ~PrivateCopy() ; // users can define objects of this type but not them

};
// 此class不允许ordinary user code copy 
// 但仍可被friends 和 members copy。
// 若欲完全禁止，不但必须把copy controls放到private内且不可以定义之。

// boost::noncopyable
