#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>

const int window_width = 320;
const int window_height = 480;
const int tile = 18;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene * scene = new QGraphicsScene();

    QGraphicsView * view = new QGraphicsView(scene);

    view->show();
    view->setFixedSize(window_width, window_height);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    return a.exec();
}
