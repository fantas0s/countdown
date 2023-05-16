#include "applogic.h"

#include <QApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;
    if (!translator.load(QLocale("fi_FI"), QString("translations"), QLatin1String("_"), QLatin1String(":/qt/qml/Countdown/"))) {
        qWarning() << "No translation for locale" << QLocale() << "using en_US instead";
        if(!translator.load(QStringLiteral(":/qt/qml/Countdown/translations_en_US.qm")))
            qWarning() << "Failed to load any translation!";
    }
    QCoreApplication::installTranslator(&translator);

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
