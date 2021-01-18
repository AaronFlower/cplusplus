#include <memory>
#include <typeindex>

class Any {
public:
    Any(void) : m_type_index(typeid(void)) {}

    Any(const Any &that) :
        m_ptr(that.Clone()), m_type_index(that.m_type_index)
    {}

    Any(Any &&that) :
        m_ptr(std::move(that.m_ptr)), m_type_index(that.m_type_index)
    {}

    // 创建智能指针时，对于一般类型，通过 std::decay 来移除引用和 cv 符，从而获取原始类型。
    // 该构造函数的目的是保证该模版函数适用于所有非 Any 类型的模版。
    template<typename U,
        class = typename std::enable_if<!std::is_same<typename std::decay<U>::type, Any>::value, U>::type>
    Any(U &&value) :
        m_ptr(new Derived<typename std::decay<U>::type>(std::forward<U>(value))),
        m_type_index(std::type_index(typeid(typename std::decay<U>::type)))
    {}

    bool IsNull() const
    {
        return !bool(m_ptr);
    }

    template <class U>
    bool Is() const
    {
        return m_type_index == std::type_index(typeid(U));
    }


private:
    struct Base;
    typedef std::unique_ptr<Base> BasePtr;

    struct Base {
        virtual ~Base() {}
        virtual BasePtr Clone() const = 0;
    };

    template <typename T>
    struct Derived: Base {
        template <typename U>
        Derived(U &&value) : m_value(std::forward<U>(value)) {}

        BasePtr Clone() const override
        {
            return BasePtr(new Derived<T>(m_value));
        }

        T m_value;
    };

    BasePtr Clone() const
    {
        if (m_ptr != nullptr) {
            return m_ptr->Clone();
        }
        return nullptr;
    }

private:
    BasePtr m_ptr;
    std::type_index m_type_index;
};
