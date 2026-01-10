#ifndef MODESELECTWIDGET_H
#define MODESELECTWIDGET_H

#include <QWidget>

class BoardSelect;

/**
 * @brief Widget responsible for selecting the game mode.
 *
 * ModeSelectWidget aggregates mode selection inputs
 * and emits a unified modeSelected() signal that
 * describes the selected board configuration.
 */
class ModeSelectWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Constructs the mode selection widget.
     */
    explicit ModeSelectWidget(QWidget* parent = nullptr);

protected:
    /**
     * @brief Handles resize events to keep the layout consistent.
     */
    void resizeEvent(QResizeEvent* event) override;

signals:
    /**
     * @brief Emitted when a game mode is selected.
     *
     * @param size  Board dimension.
     * @param mines Number of mines for the selected mode.
     */
    void modeSelected(int size, int mines);

private:
    BoardSelect* m_board; ///< Board size selection component
};

#endif // MODESELECTWIDGET_H
