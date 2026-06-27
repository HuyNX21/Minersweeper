#ifndef MINECONTROLLER_H
#define MINECONTROLLER_H

#include <QObject>
#include <QDebug>

#include "BLKC_Common.h"
#include "proxy_APIC_MineModel.h"

#include "GameState.h"

class MineView;
class BestTimeEntry;

class MineController : public QObject
{
    Q_OBJECT
    public:
        static MineController* initInstance(MineView* view = nullptr, QObject* parent = nullptr);
        static MineController* getInstance();
        static void deleteInstance();

        // Callback functions for Model -> Controller communication
        static void ans_cellOpened(std::vector<PointCellOpened> openedCells, bool stateGameOver);
        static void ans_flagChanged(int row, int col, bool flagged, int flagUsed, int totalMines, bool b_result);

        // Observer for Model changes
        class MCC_MineControllerObserver : public Proxy_APIC_MineModelObserver
        {
            public:
                virtual void initClass();
                virtual void obs_gameStateChanged(GameState state);
                virtual void obs_minesRevealed(int rowMineTriggered, int colMineTriggered, std::vector<std::pair<int,int>> mines);
                virtual void obs_gameOver(bool win);
        };

        void setOldInfo(int size, int mines);

    private:
        explicit MineController(MineView* view, QObject* parent = nullptr);
        ~MineController() override;

        Q_DISABLE_COPY(MineController)

    private slots:
        void onModeSelected(int size, int mines);
        void onCellClicked(int row, int col);
        void onCellRightClicked(int row, int col);
        void onStartOverRequested();
        void onChangeDifficultyRequested();
        void onPauseRequested();
        void onBestTimeConfirmed(const BestTimeEntry entry);

    private:
        MineView*  m_view;   ///< View layer
        MCC_MineControllerObserver m_observer;
        static MineController* s_instance;
        int m_sizeOld;       ///< Size current mode
        int m_minesOld;      ///< Mines current mode
};

#endif