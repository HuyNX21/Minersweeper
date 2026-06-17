#include <QApplication>
#include "MineView.h"
#include "MineController.h"
#include "BLKC_ProxyManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MineView view;
    MineController::initInstance(&view);
    BLKC_ProxyManager::getInstance();
    QObject::connect(&app, &QCoreApplication::aboutToQuit, []() {
        MineController::deleteInstance();
    });
    view.show();

    return app.exec();
}

