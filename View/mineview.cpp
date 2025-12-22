#include "mineview.h"
#include "Scr1/modeselectwidget.h"
#include "Scr2/centralwidget.h"

#include <QStackedWidget>

MineView::MineView(QWidget* parent)
    : QMainWindow(parent)
{
    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);

    // ===== Screens =====
    m_selectScreen = new ModeSelectWidget(this);
    m_boardScreen  = new CentralWidget(this);

    m_stack->addWidget(m_selectScreen); // index 0
    m_stack->addWidget(m_boardScreen);  // index 1

    m_stack->setCurrentIndex(0);

    // ===== Select mode → Board =====
    connect(m_selectScreen, &ModeSelectWidget::modeSelected,
            this, [this](int size)
            {
                m_boardScreen->setBoardSize(size);
                m_stack->setCurrentIndex(1);
            });

    // ===== (Optional) Board → Back =====

    connect(m_boardScreen, &CentralWidget::backRequested,
            this, [this]()
            {
                m_stack->setCurrentIndex(0);
            });

}
