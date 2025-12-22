#include "View/mineview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MineView view;
    view.show();
    return a.exec();
}
