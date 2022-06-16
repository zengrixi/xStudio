#pragma once

#include <memory>

namespace xStudio
{
    template<typename T>
    class Singleton
    {
    public:
        static T& GetSingleton();

        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton) = delete;
        Singleton()                           = default;
    };

    template<typename T>
    inline T& Singleton<T>::GetSingleton()
    {
        static const std::unique_ptr<T> GetSingleton{ new T{} };
        return *GetSingleton;
    }
} // namespace xStudio