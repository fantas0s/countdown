#include "applogic.h"

#include <QApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickItem>
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
    QQuickView view;
    AppLogic logic;
    view.setResizeMode(QQuickView::ResizeMode::SizeRootObjectToView);
    view.setMinimumSize(QSize{900, 700});
    view.rootContext()->setContextProperty("_appLogic", &logic);
    view.setSource(url);
    view.setTitle(qtTrId("title_main_window"));
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
    QObject::connect(view.engine(), &QQmlEngine::quit, view.engine(), [&app](){app.quit();});

    /* Settings window */
    QUrl settingsUrl{"qrc:/qt/qml/Countdown/SettingsPopup.qml"};
    QQuickView settingsView;
    settingsView.setResizeMode(QQuickView::ResizeMode::SizeRootObjectToView);
    settingsView.setMinimumSize(QSize{450, 350});
    settingsView.rootContext()->setContextProperty("_appLogic", &logic);
    settingsView.setSource(settingsUrl);
    settingsView.setTitle(qtTrId("title_settings"));
    QObject::connect(view.rootObject(), SIGNAL(openSettings()), &settingsView, SLOT(show()));
    QObject::connect(settingsView.rootObject(), SIGNAL(close()), &settingsView, SLOT(hide()));
    int returnValue = app.exec();
    /* Place empty page to prevent nullptr reads during teardown. */
    QUrl emptyPageUrl{"qrc:/qt/qml/Countdown/Empty.qml"};
    view.setSource(emptyPageUrl);
    return returnValue;
}
