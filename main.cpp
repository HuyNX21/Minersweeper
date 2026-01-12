#include <QApplication>
#include "View/MineView.h"
#include "Controller/MineController.h"
#include "Model/minemodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MineView view;
    MineModel model;
    MineController controller(&view, &model);

    view.show();
    return app.exec();
}
