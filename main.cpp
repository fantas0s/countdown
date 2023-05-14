#include <QApplication>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQuickView view;
    QUrl url{"qrc:/qt/qml/Countdown/Main.qml"};
    view.setSource(url);
    view.show();
    return app.exec();
}
