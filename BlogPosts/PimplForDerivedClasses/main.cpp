#include <QtDebug>

#include "interpreter.h"
#include "xxl_interpreter.h"

int main(int argc, char *argv[])
{
    qDebug() << "Pimpl for derived classes";
    Interpreter interpreter;
    interpreter.printInfo();

    XxlInterpreter xxlInterpreter;
    xxlInterpreter.printInfo();
}
