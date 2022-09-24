#include <QtDebug>

#include "interpreter.h"
#include "interpreter_impl.h"

Interpreter::Interpreter()
    : m_impl{new InterpreterImpl{}}
{
}

Interpreter::~Interpreter()
{
}


void Interpreter::printInfo()
{
    qDebug() << u"Device information: %1"_qs.arg(info());
}

Interpreter::Interpreter(InterpreterImpl *impl)
    : m_impl{impl}
{
}


QString Interpreter::info() const
{
    return impl()->m_info;
}
