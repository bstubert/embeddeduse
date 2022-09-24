#include "xxl_interpreter.h"
#include "xxl_interpreter_impl.h"

XxlInterpreter::XxlInterpreter()
    : Interpreter{new XxlInterpreterImpl{}}
{
}

QString XxlInterpreter::info() const
{
    return u"%1 %2"_qs.arg(impl()->m_info, impl()->m_extraInfo);
}

XxlInterpreter::~XxlInterpreter()
{
}
