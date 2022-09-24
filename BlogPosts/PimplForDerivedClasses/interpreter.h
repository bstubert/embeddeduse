#pragma once

#include <memory>

#include <QString>

struct InterpreterImpl;

class Interpreter
{
public:
    Interpreter();
    virtual ~Interpreter();
    Interpreter(const Interpreter &rhs) = delete;
    Interpreter &operator=(const Interpreter &rhs) = delete;

    void printInfo();

protected:
    Interpreter(InterpreterImpl *impl);
    inline InterpreterImpl *impl()
    {
        return reinterpret_cast<InterpreterImpl *>(m_impl.get());
    }
    inline const InterpreterImpl *impl() const
    {
        return reinterpret_cast<const InterpreterImpl *>(m_impl.get());
    }

    virtual QString info() const;

private:
    std::unique_ptr<InterpreterImpl> m_impl;
};
