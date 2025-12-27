#include <QApplication>
#include "View/MineView.h"
#include "Controller/MineController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MineView view;
    MineController controller(&view);

    view.show();
    return app.exec();
}
