#include <QApplication>
#include "MineView.h"
#include "MineController.h"
#include "BLKC_ProxyManager.h"
#include "SignalHandle.h"

int main(int argc, char *argv[])
{
    char cmd[64];
	struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = seg_handler;
    sigaction(SIGSEGV, &sa, NULL);

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

