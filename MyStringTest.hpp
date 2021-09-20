#include<typeinfo>  // typeid()
#include<stdio.h>
#include<iostream>
using namespace std;
template<typename T>
void output_static_data(const T& myStr)
{
    char buf[10];
}


template<typename M, typename NM>
void test_moveable(M c1, NM c2, long& value)
{
    char buf[10];
    typedef typename iterator_traits<typename M::iterator>::value_type V1type;
    clock_t timeStart =clock();
    for (long i = 0; i < value; i++)
    {
        snprintf(buf, 10, "%d", rand());
        auto ite = c1.end();
        c1.insert(ite, V1type(buf));
    }
    cout << "construction, milli-seconds:" << (clock()- timeStart) << endl;
    cout << "size() = " << c1.size() << endl;
    output_static_data(*(c1.begin()));

    M cl1(c1);
    M cl2(std::move(c1));  // c1不能在用了
    cl1.swap(cl2);

    // 测试 non-moveable
    // ...

}
