#pragma once

#include <QString>

#include "interpreter_impl.h"

struct XxlInterpreterImpl : public InterpreterImpl
{
    QString m_extraInfo{"XXL"};
};
