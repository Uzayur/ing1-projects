#pragma once

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

template <class T>
class Singleton
{
public:
    Singleton(Singleton& try_other) = delete;
    void operator=(Singleton&) = delete;

    static T* getInstance()
    {
        if (!instance_)
            instance_ = new T();
        return instance_;
    }

    void open_log_file(const std::string& file);
    void write_to_log_file();
    void close_log_file();

protected:
    Singleton()
    {}

private:
    inline static T* instance_ = nullptr;
};

class Logger : public Singleton<Logger>
{
    friend class Singleton<Logger>;

private:
    Logger()
    {}

public:
    static Singleton* instance()
    {
        return Singleton::getInstance();
        ;
    }
};
