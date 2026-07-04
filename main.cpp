#include "entry_window.h"
#include "game_answers.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    configureGameAnswers();

    Entry_Window w;
    w.show();
    return QCoreApplication::exec();
}
