//万用的Hash Function
//! 不完整


#include<functional>
class Customer {

        //...
};

class Customer {

public:
    std::size_t operator()(const Customer& c) const {
        return ...

    }
};

unordered_set<Customer, CustomerHash> custset;


// from boost(function/hash):
template <typename T>
inline void hash_combine (size_t& seed, const T& val)
{
    seed ^= hash<T>()(val) + 
            0x9e3779b9 +
            (seed<<6) + 
            (seed>>2);
}co

//auxitiary generic  functions to create a hash value using a seed
template <typename T>
inline void hash_val(size_t& seed, const T& val)
{
    hash_combine(seed, val);
}

template <typename T, typename... Types>
inline void hash_val(size_t& seed, const T& val, const Types&...args)
{
    hash_combine(seed, val);
    hash_val(seed, args...);
}


//auxitiary generic  functions to create a hash value using a seed
template <typename... Types>
inline size_t hash_val(const Types&... args)
{
    size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

class CustomerHash{
public:
    size_t operator()(const Customer& c) const {
        return hash_val(c.fname, c.lname, c.xxx)
    }
};

