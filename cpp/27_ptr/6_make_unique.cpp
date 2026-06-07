#include <iostream>
using namespace std;

template<class T>
class WeakPtr;

// 控制块里面两个计数器。
struct ControlBlock
{
    int _strong;
    int _weak;

    ControlBlock()
        : _strong(1)
        , _weak(0)
    {}
};

template<class T>
class SharedPtr
{
private:
    T* _ptr;
    ControlBlock* _cb;
    friend class WeakPtr<T>;

public:
    // 构造函数
    explicit SharedPtr(T* ptr = nullptr)
        : _ptr(ptr)
        , _cb(nullptr)
    {
        // 真正存在资源需要管理的时候，创建一个控制块。
        // 控制块的强引用计数，初始化的时候变成：1
        if (_ptr)
        {
            _cb = new ControlBlock;
        }
    }

    // 拷贝构造：强引用计数 +1
    SharedPtr(const SharedPtr<T>& sp)
        : _ptr(sp._ptr)
        , _cb(sp._cb)
    {
        if (_cb)
        {
            ++_cb->_strong;
        }
    }

    // 赋值重载
    // 1.Release会释放资源一次的。
    // 2.真正的资源来临的时候，强引用计数会 加一
    SharedPtr<T>& operator=(const SharedPtr<T>& sp)
    {
        if (this != &sp)
        {
            Release();

            _ptr = sp._ptr;
            _cb = sp._cb;

            if (_cb)
            {
                ++_cb->_strong;
            }
        }

        return *this;
    }

    // 析构
    ~SharedPtr()
    {
        Release();
    }

    T& operator*()
    {
        return *_ptr;
    }

    T* operator->()
    {
        return _ptr;
    }

    T* get() const
    {
        return _ptr;
    }

    int use_count() const
    {
        return _cb ? _cb->_strong : 0;
    }

private:
    // 给 WeakPtr::lock() 使用的构造函数
    SharedPtr(T* ptr, ControlBlock* cb)
        : _ptr(ptr)
        , _cb(cb)
    {
        if (_cb)
        {
            ++_cb->_strong;
        }
    }

    void Release()
    {
        if (_cb)
        {
            --_cb->_strong;

            // 强引用计数为 0，释放资源
            if (_cb->_strong == 0)
            {
                delete _ptr;
                _ptr = nullptr;

                // 如果弱引用计数也为 0，释放控制块
                if (_cb->_weak == 0)
                {
                    delete _cb;
                    _cb = nullptr;
                }
            }
        }
    }

};

template<class T>
class WeakPtr
{
public:
    // 默认构造
    WeakPtr()
        : _ptr(nullptr)
        , _cb(nullptr)
    {}

    // 用 SharedPtr 构造 WeakPtr
    WeakPtr(const SharedPtr<T>& sp)
        : _ptr(sp._ptr)
        , _cb(sp._cb)
    {
        if (_cb)
        {
            ++_cb->_weak;
        }
    }

    // 拷贝构造
    WeakPtr(const WeakPtr<T>& wp)
        : _ptr(wp._ptr)
        , _cb(wp._cb)
    {
        if (_cb)
        {
            ++_cb->_weak;
        }
    }

    // 用 SharedPtr 赋值
    WeakPtr<T>& operator=(const SharedPtr<T>& sp)
    {
        Release();

        _ptr = sp._ptr;
        _cb = sp._cb;

        if (_cb)
        {
            ++_cb->_weak;
        }

        return *this;
    }

    // WeakPtr 之间赋值
    WeakPtr<T>& operator=(const WeakPtr<T>& wp)
    {
        if (this != &wp)
        {
            Release();

            _ptr = wp._ptr;
            _cb = wp._cb;

            if (_cb)
            {
                ++_cb->_weak;
            }
        }

        return *this;
    }

    // 析构
    ~WeakPtr()
    {
        Release();
    }

    // 判断资源是否已经释放
    bool expired() const
    {
        return _cb == nullptr || _cb->_strong == 0;
    }

    // 获取强引用计数
    int use_count() const
    {
        return _cb ? _cb->_strong : 0;
    }

    // 尝试提升为 SharedPtr
    SharedPtr<T> lock() const
    {
        if (expired())
        {
            return SharedPtr<T>();
        }

        return SharedPtr<T>(_ptr, _cb);
    }

private:
    void Release()
    {
        if (_cb)
        {
            --_cb->_weak;

            // 如果强引用和弱引用都为 0，释放控制块
            if (_cb->_strong == 0 && _cb->_weak == 0)
            {
                delete _cb;
            }

            _ptr = nullptr;
            _cb = nullptr;
        }
    }

private:
    T* _ptr;
    ControlBlock* _cb;
};
