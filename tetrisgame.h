#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QPushButton>

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
    //시작 정지버튼추가
    QPushButton *startButton;
    QPushButton *pauseButton;
    bool isPaused;
    //블로크그리기함수
    void drawBlock(QPainter &painter);
    //충돌시 고정함수
    void lockBlock();
    //고정하고 새 블로크창조함수
    void spawnNewBlock();
    //완성된 줄검사와 제거 점수루적
    void checkLineComplete();
    //블로크 즉시락하 함수
    void hardDrop();
    //다음 블로크미리보기 함수
    void drawNextBlock(QPainter &painter);
    bool isGameOver();
    //충돌검사함수
    bool checkCollision(int newX, int newY, int newRotation);
    //시작 정지 함수
    void startGame();
    void pauseGame();

    int score;

    int board[20][10];
    int currentX, currentY;
    int currentBlockType;
    int currentRotation;
    int nextBlockType;

    int blocks[7][4][4][4];
    QTimer *gameTimer;
    int gameSpeed;
};

#endif // TETRISGAME_H
