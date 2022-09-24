#pragma once

#include "interpreter.h"

struct XxlInterpreterImpl;

class XxlInterpreter : public Interpreter
{
public:
    XxlInterpreter();
    virtual ~XxlInterpreter();
    XxlInterpreter(const XxlInterpreter &rhs) = delete;
    XxlInterpreter &operator=(const XxlInterpreter &rhs) = delete;

protected:
    QString info() const override;

private:
    inline XxlInterpreterImpl *impl()
    {
        return reinterpret_cast<XxlInterpreterImpl *>(Interpreter::impl());
    }
    inline const XxlInterpreterImpl *impl() const
    {
        return reinterpret_cast<const XxlInterpreterImpl *>(Interpreter::impl());
    }
};
