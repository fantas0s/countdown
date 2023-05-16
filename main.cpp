#include "applogic.h"

#include <QApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QUrl url{"qrc:/qt/qml/Countdown/Main.qml"};
    QUrl emptyPageUrl{"qrc:/qt/qml/Countdown/Empty.qml"};
    QQuickView view;
    AppLogic logic;
    view.setResizeMode(QQuickView::ResizeMode::SizeRootObjectToView);
    view.setMinimumSize(QSize{900, 700});
    view.rootContext()->setContextProperty("_appLogic", &logic);
    view.setSource(url);
    view.show();
    QObject::connect(&logic, &AppLogic::expandCollapse, &view, [&view, &logic](){
        if (view.visibility() == QWindow::Maximized || view.visibility() == QWindow::FullScreen)
        {
            view.setVisibility(QWindow::Windowed);
            logic.setExpandedState(false);
        }
        else
        {
            view.setVisibility(QWindow::FullScreen);
            logic.setExpandedState(true);
        }
    });
    QObject::connect(view.engine(), &QQmlEngine::quit, [&app](){app.quit();});
    int returnValue = app.exec();
    /* Place empty page to prevent nullptr reads during teardown. */
    view.setSource(emptyPageUrl);
    return returnValue;
}
