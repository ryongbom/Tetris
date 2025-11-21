#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TetrisGame; }
QT_END_NAMESPACE

class TetrisGame : public QMainWindow
{
    Q_OBJECT

public:
    TetrisGame(QWidget *parent = nullptr);
    ~TetrisGame();

private:
    Ui::TetrisGame *ui;
};
#endif // TETRISGAME_H
