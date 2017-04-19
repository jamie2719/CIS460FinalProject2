#include "mainwindow.h"
#include <QApplication>
#include "jsonparser.h"

int main(int argc, char *argv[])
{





    JsonParser parser = JsonParser();
    scene_t scene = parser.parse(argv[1]);
    float width = atof(argv[2]);
    float height = atof(argv[3]);
    parser.render(width, height, scene);



    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

//ADDED THIS COMMENT


}
