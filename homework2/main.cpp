#include "exer01widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    exer01Widget w;
    w.show();

    return a.exec();
}
