#ifndef BOARDSELECT_H
#define BOARDSELECT_H

#include <QWidget>

/**
 * @brief Widget for selecting the game board size.
 *
 * BoardSelect presents available board size options
 * and emits a corresponding signal when the user
 * makes a selection.
 */
class BoardSelect : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Constructs the board selection widget.
     */
    explicit BoardSelect(QWidget* parent = nullptr);

signals:
    /**
     * @brief Emitted when the user selects an 8x8 board.
     */
    void mode8Requested();

    /**
     * @brief Emitted when the user selects a 16x16 board.
     */
    void mode16Requested();

    /**
     * @brief Emitted when the user selects a 32x32 board.
     */
    void mode32Requested();
};

#endif // BOARDSELECT_H
