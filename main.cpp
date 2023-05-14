#include "applogic.h"

#include <QApplication>
#include <QQmlContext>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QUrl url{"qrc:/qt/qml/Countdown/Main.qml"};
    QQuickView view;
    AppLogic logic;
    view.rootContext()->setContextProperty("_appLogic", &logic);
    view.setSource(url);
    view.show();
    return app.exec();
}
