#include <string>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <memory>

using std::string;
using std::unordered_map;
using std::function;


// 本 IoC 有两个限制；1. 仅能创建无参对象；2. 只能创建一种接口类型的对象。

template <class T>
class IocContainer {
public:
    IocContainer() {}
    ~IocContainer() {}

    // 注册需要创建的构建函数，需要传入一个唯一标识。
    template <class Derived>
    void register_type(const string &key)
    {
        function<T*()> fn = []{return new Derived();};
        _register_type(key, fn);
    }

    // 根据唯一的标识去查找对应的构造器，并创建指针对象。
    T *resolve(const string &key)
    {
        auto it = m_creator_map.find(key);
        if (it == m_creator_map.end()) {
            return nullptr;
        }

        function<T *()> fn = m_creator_map[key];
        return fn();
    }

    std::shared_ptr<T> resolve_shared(const string &key)
    {
        T *ptr = resolve(key);
        return std::shared_ptr<T>(ptr);
    }

private:
    void _register_type(const string &key, function<T *()> &fn)
    {
        m_creator_map[key] = fn;
    }

private:
    unordered_map<string, function<T *()>> m_creator_map;

};

// base class should have one
// deleting object of abstract class type 'Animal' should have a virtual destructor.
struct Animal {
    virtual void say() = 0;
    virtual ~Animal() {};
};

struct Dog : public Animal {
    Dog()
    {
        std::cout << "dog ctor ...\n";
    }

    ~Dog()
    {
        std::cout << "dog dtor ...\n";
    }

    void say() override
    {
        std::cout << "Wang wang ...  \n";
    }
};

struct Cat : public Animal {
    Cat()
    {
        std::cout << "cat ctor ...\n";
    }

    ~Cat()
    {
        std::cout << "cat dtor ...\n";
    }

    void say() override
    {
        std::cout << "Miao miao ...\n";
    }
};


int main(void)
{
    IocContainer<Animal> ioc;

    ioc.register_type<Dog>("dog");
    ioc.register_type<Cat>("cat");

    std::shared_ptr<Animal> dog = ioc.resolve_shared("dog");
    dog->say();

    // release resource explicitly.
    dog.reset();

    Animal *cat = ioc.resolve("cat");
    cat->say();
    delete cat;

    return 0;
}
