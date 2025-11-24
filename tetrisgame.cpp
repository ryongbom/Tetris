#include "tetrisgame.h"

TetrisGame::TetrisGame(QWidget *parent) : QWidget(parent)
{
    //기본창크기와 제목
    setFixedSize(500, 600);
    setWindowTitle("My Tetris Game");

    //기본창의 격자처리후 매칸을 배렬로 정의한후 초기화처리
    for(int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            board[i][j] = 0;
        }
    }
    //블로크의 종류를 결정후 초기화처리
    currentBlockType = 0;
    //블로크의 회전상태초기화
    currentRotation = 0;
    currentX = 3;
    currentY = 0;

    //initialblocks[4][4]인 7가지의 블로크를 생성
    int initialblocks[7][4][4][4] = {
        {
            {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
            {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
            {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},
            {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}
        },
        {
            {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
            {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
            {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
            {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}
        },
        {
            {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},
            {{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}},
            {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}},
            {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}}
        },
        {
            {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
            {{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}},
            {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}},
            {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}},
        },
        {
            {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
            {{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}},
            {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}},
            {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}}
        },
        {
            {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},
            {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}},
            {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}},
            {{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}}
        },
        {
            {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},
            {{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}},
            {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}},
            {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}
        }
    };

    for(int i = 0; i < 7; i++) {
        for(int r = 0; r < 4; r++) {
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 4; k++) {
                    blocks[i][r][j][k] = initialblocks[i][r][j][k];
                }
            }
        }
    }

    srand(time(NULL));

    //gameTimer를 창조
    gameTimer = new QTimer(this);
    //신호련결
    connect(gameTimer, &QTimer::timeout, this, &TetrisGame::updateGame);
    //시간간격 0.5초
    gameSpeed = 500; // 0.5s

    score = 0;

    nextBlockType = rand() % 7;
    //시작 정지버튼 생성자에서 초기화
    isPaused = false;
    //시작 버튼 생성
    startButton = new QPushButton("start", this);
    startButton->setGeometry(320, 200, 160, 40);
    startButton->setFont(QFont("Arial", 14));
    startButton->setEnabled(true);
    //정지 버튼 생성
    pauseButton = new QPushButton("pause", this);
    pauseButton->setGeometry(320, 250, 160, 40);
    pauseButton->setFont(QFont("Arial", 14));
    pauseButton->setEnabled(false);

    connect(startButton, &QPushButton::clicked, this, &TetrisGame::startGame);
    connect(pauseButton, &QPushButton::clicked, this, &TetrisGame::pauseGame);
}
//updateGame이 호출시 블로크 1칸 떨구기
void TetrisGame::updateGame() {
    if(!checkCollision(currentX, currentY + 1, currentRotation)) {
        currentY++;
    }
    else {
        lockBlock();
        spawnNewBlock();
    }
    update();
}
//충돌검사함수구현
bool TetrisGame::checkCollision(int newX, int newY, int newRotation) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if (blocks[currentBlockType][newRotation][i][j] == 1) {
                int boardX = newX + j;
                int boardY = newY + i;

                if (boardX < 0 || boardX > 9) {
                    return true;
                }
                if (boardY > 19) {
                    return true;
                }
                if (boardY >= 0 && board[boardY][boardX] != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}
//블로크고정함수
void TetrisGame::lockBlock() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[currentBlockType][currentRotation][i][j] == 1) {
                int y = currentY + i;
                int x = currentX + j;
                if (y >= 0 && y < 20 && x >= 0 && x < 10) {
                    board[y][x] = currentBlockType + 1;
                }
            }
        }
    }
    checkLineComplete();

    if (isGameOver()) {
        gameTimer->stop();
        setWindowTitle("Game Over! Score: " + QString::number(score));
        startButton->setEnabled(true);
        pauseButton->setEnabled(false);
        return;
    }
    spawnNewBlock();
    update();
}
//오락종료함수
bool TetrisGame::isGameOver() {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 10; j++) {
            if (board[i][j] != 0) {
                return true;
            }
        }
    }
    return false;
}
//새 블로크생성함수
void TetrisGame::spawnNewBlock() {
    currentX = 3;
    currentY = 0;
    currentBlockType = nextBlockType;
    nextBlockType = rand() % 7;
    currentRotation = 0;

    if (checkCollision(currentX, currentY, currentRotation)) {
        gameTimer->stop();
        setWindowTitle("Game Over! Score: " + QString::number(score));
        startButton->setEnabled(true);
        pauseButton->setEnabled(false);
    }
}
//줄이 다 완성됐는지 검사하고 처리함수 중요!!!
void TetrisGame::checkLineComplete() {
    int linesRemoved = 0;
    bool foundLine;
    do {
        foundLine = false;
        for(int i = 19; i >= 0; i--) {
            bool lineComplete = true;

            for (int j = 0; j < 10; j++) {
                if (board[i][j] == 0) {
                    lineComplete = false;
                    break;
                }
            }

            if(lineComplete) {
                linesRemoved++;
                foundLine = true;
                for(int k = i; k > 0; k--) {
                    for (int j = 0; j < 10; j++) {
                        board[k][j] = board[k - 1][j];
                    }
                }

                for (int j = 0; j < 10; j++) {
                    board[0][j] = 0;
                }

                break;
            }
        }
    } while (foundLine);

    if(linesRemoved > 0) {
        score += 100 * linesRemoved;
    }
}
//공백을 누르면 블로크가 즉시 떨어지는 함수구현
void TetrisGame::hardDrop() {
    while (!checkCollision(currentX, currentY + 1, currentRotation)) {
        currentY++;
    }

    lockBlock();
}
//시작 정지함수 구현
void TetrisGame::startGame() {
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            board[i][j] = 0;
        }
    }

    score = 0;
    currentX = 3;
    currentY = 0;
    currentBlockType = rand() % 7;
    nextBlockType = rand() % 7;
    currentRotation = 0;

    gameTimer->start(gameSpeed);
    startButton->setEnabled(false);
    pauseButton->setEnabled(true);
    pauseButton->setText("Pause");
    isPaused = false;
    setWindowTitle("My Tetris Game");
    setFocus();
    update();
}
void TetrisGame::pauseGame() {
    if (isPaused) {
        gameTimer->start(gameSpeed);
        pauseButton->setText("Pause");
        isPaused = false;
    }
    else {
        gameTimer->stop();
        pauseButton->setText("Resume");
        isPaused = true;
    }
    setFocus();
}
//배경창그리기
void TetrisGame::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);

    painter.fillRect(0, 0, 300, 600, Qt::darkGray);
    painter.fillRect(300, 0, 200, 600, QColor(240, 240, 240));

    painter.fillRect(320, 40, 160, 120, Qt::black);
    painter.setPen(Qt::white);
    painter.drawRect(320, 40, 160, 120);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(345, 190, "NEXT BLOCK");

    bool gameOver = !gameTimer->isActive();
    bool gameNotStarted = (score == 0 && !gameTimer->isActive() && !isPaused);

    //점수표시
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 14));
    painter.drawText(10, 20, QString("Score: %1").arg(score));

    //바닥에 쌓인 블로크그리기
    for(int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[i][j] != 0) {
                painter.fillRect(j * 30, i * 30, 30, 30, QColor(80, 80, 80));
                painter.setPen(Qt::black);
                painter.drawRect(j * 30, i * 30, 30, 30);
            }
        }
    }

    painter.setPen(Qt::white);
    for(int x = 0; x <= 300; x += 30) {
        painter.drawLine(x, 0, x, 600);
    }
    for(int y = 0; y <= 600; y += 30) {
        painter.drawLine(0, y, 300, y);
    }
    if (gameNotStarted) {

    }
    if (gameNotStarted) {
        painter.fillRect(50, 250, 200, 100, QColor(0, 0, 0, 200));
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(95, 290, "READY?");

        painter.setFont(QFont("Arial", 12));
        painter.drawText(60, 320, "Click START Button");
    }
    else if (!gameOver && !isPaused) {
        drawBlock(painter);
        drawNextBlock(painter);
    }


    if (gameOver && score > 0) {
        painter.fillRect(30, 250, 240, 100, QColor(0, 0, 0, 200));
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(70, 290, "GAME OVER");

        painter.setFont(QFont("Arial", 12));
        painter.drawText(80, 320, "Final Score: " + QString::number(score));
        painter.drawText(75, 340, "Click button Start");
    }
}
//건반명령구현
void TetrisGame::keyPressEvent(QKeyEvent *event) {
    if (!gameTimer->isActive() && event->key() == Qt::Key_Space) {
        for(int i = 0; i < 20; i++) {
            for(int j = 0; j < 10; j++) {
                board[i][j] = 0;
            }
        }
        score = 0;
        currentX = 3;
        currentY = 0;
        currentBlockType = rand() % 7;
        nextBlockType = rand() % 7;
        currentRotation = 0;
        gameTimer->start(gameSpeed);

        startButton->setEnabled(false);
        pauseButton->setEnabled(true);
        pauseButton->setText("Pause");
        isPaused = false;
        setWindowTitle("My Tetris Game");
        update();
        return;
    }
    if (gameTimer->isActive()) {
        switch (event->key()) {
            case Qt::Key_Left:
                if(!checkCollision(currentX - 1, currentY, currentRotation))
                    currentX--;
                break;
            case Qt::Key_Right:
                if(!checkCollision(currentX + 1, currentY, currentRotation))
                    currentX++;
                break;
            case Qt::Key_Down:
                if(!checkCollision(currentX, currentY + 1, currentRotation))
                    currentY++;
                break;
            case Qt::Key_Up:
                //회전
                if (!checkCollision(currentX, currentY, (currentRotation + 1) % 4))
                    currentRotation = (currentRotation + 1) % 4;
                break;
            case Qt::Key_Space:
                hardDrop();
                break;
        }
        update();
    }
}
void TetrisGame::drawNextBlock(QPainter &painter) {
    QColor colors[7] = {
        Qt::cyan,
        Qt::yellow,
        Qt::magenta,
        Qt::green,
        Qt::red,
        Qt::blue,
        QColor(255, 165, 0)
    };
    int offsetX = 340 + 20;
    int offsetY = 40 + 20;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(blocks[nextBlockType][0][i][j] == 1) {
                int x = offsetX + j * 20;
                int y = offsetY + i * 20;

                painter.fillRect(x, y, 20, 20, colors[nextBlockType]);

                painter.setPen(Qt::black);
                painter.drawRect(x, y, 20, 20);
            }
        }
    }
}
//매 블로크색갈주고 그리기
void TetrisGame::drawBlock(QPainter &painter) {
    QColor colors[7] = {
        Qt::cyan,
        Qt::yellow,
        Qt::magenta,
        Qt::green,
        Qt::red,
        Qt::blue,
        QColor(255, 165, 0)
    };

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(blocks[currentBlockType][currentRotation][i][j] == 1) {
                int x = (currentX + j) * 30;
                int y = (currentY + i) * 30;

                painter.fillRect(x, y, 30, 30, colors[currentBlockType]);

                painter.setPen(Qt::black);
                painter.drawRect(x, y, 30, 30);
            }
        }
    }
}

