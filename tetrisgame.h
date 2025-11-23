#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>

class TetrisGame : public QWidget
{
    Q_OBJECT

public:
    TetrisGame(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateGame();

private:
    void drawBlock(QPainter &painter);
    void lockBlock();
    void spawnNewBlock();
    //완성된 줄검사와 제거 점수루적
    void checkLineComplete();
    void hardDrop();
    bool isGameOver();
    bool checkCollision(int newX, int newY, int newRotation);

    int score;

    int board[20][10];
    int currentX, currentY;
    int currentBlockType;
    int currentRotation;

    int blocks[7][4][4][4];
    QTimer *gameTimer;
    int gameSpeed;
};

#endif // TETRISGAME_H
