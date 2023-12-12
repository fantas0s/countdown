#ifndef APPLOGIC_H
#define APPLOGIC_H

#include <QColor>
#include <QDateTime>
#include <QObject>
#include <QString>
#include <QTimer>

class AppLogic : public QObject
{
    Q_OBJECT
    /* members */
    Q_PROPERTY(QString titleText MEMBER m_titleText NOTIFY titleTextChanged)
    Q_PROPERTY(QString infoText MEMBER m_infoText NOTIFY infoTextTextChanged)
    Q_PROPERTY(QString timeOutInfoText MEMBER m_timeOutInfoText NOTIFY timeOutInfoTextChanged)
    Q_PROPERTY(QColor titleColor MEMBER m_titleColor NOTIFY titleColorChanged)
    Q_PROPERTY(QColor infoColor MEMBER m_infoColor NOTIFY infoColorChanged)
    Q_PROPERTY(QColor timerColor MEMBER m_timerColor NOTIFY timerColorChanged)

    /* setter-enabled values */
    Q_PROPERTY(QString backgroundImage READ backgroundImage WRITE setBackgroundImage NOTIFY backgroundImageChanged)
    Q_PROPERTY(QString timeoutBackgroundImage READ timeoutBackgroundImage WRITE setTimeoutBackgroundImage NOTIFY backgroundImageChanged)
    Q_PROPERTY(int targetHour READ targetHour WRITE setTargetHour NOTIFY timeoutChanged)
    Q_PROPERTY(int targetMinute READ targetMinute WRITE setTargetMinute NOTIFY timeoutChanged)
    Q_PROPERTY(int windowHeight READ windowHeight WRITE setWindowHeight NOTIFY windowHeightChanged)
    Q_PROPERTY(int windowWidth READ windowWidth WRITE setWindowWidth NOTIFY windowWidthChanged)

    /* logical outputs */
    /* name of background image */
    Q_PROPERTY(QString backgroundImageFileName READ backgroundImageFileName NOTIFY backgroundImageChanged)
    Q_PROPERTY(QString timeoutBackgroundImageFileName READ timeoutBackgroundImageFileName NOTIFY backgroundImageChanged)
    /* Expand or Collapse, depending on window state */
    Q_PROPERTY(QString expandCollapseText READ expandCollapseText NOTIFY expandCollapseTextChanged)
    /* Either infoText or timeOutInfoText */
    Q_PROPERTY(QString displayText READ displayText NOTIFY displayTextChanged)
    /* Text representation of set hour and minute */
    Q_PROPERTY(QString timeoutTimeString READ timeoutTimeString NOTIFY timeoutChanged)
    /* Text representation of current timer reading */
    Q_PROPERTY(QString timerText READ timerText NOTIFY timerTextChanged)
    /* True or false, depending if image file has been selected */
    Q_PROPERTY(bool defaultBackgroundImage READ defaultBackgroundImage NOTIFY backgroundImageChanged)
    Q_PROPERTY(bool defaultTimeoutBackgroundImage READ defaultTimeoutBackgroundImage NOTIFY backgroundImageChanged)
    /* random offset to prevent screen burn */
    Q_PROPERTY(int margin READ margin NOTIFY marginChanged)
    Q_PROPERTY(int offsetX READ offsetX NOTIFY offsetsChanged)
    Q_PROPERTY(int offsetY READ offsetY NOTIFY offsetsChanged)

public:
    explicit AppLogic(QObject *parent = nullptr);
    QString backgroundImageFileName() const;
    QString timeoutBackgroundImageFileName() const;
    int targetHour() const;
    int targetMinute() const;
    int windowHeight() const;
    int windowWidth() const;
    QString backgroundImage() const;
    QString timeoutBackgroundImage() const;
    QString expandCollapseText() const;
    void setExpandedState(bool expanded);
    QString displayText() const;
    QString timeoutTimeString() const;
    QString timerText() const;
    bool defaultBackgroundImage() const;
    bool defaultTimeoutBackgroundImage() const;
    int margin() const;
    int offsetX() const;
    int offsetY() const;

    void setBackgroundImage(const QString& string);
    void setTimeoutBackgroundImage(const QString& string);
    void setTargetHour(int newValue);
    void setTargetMinute(int newValue);
    void setWindowHeight(int newValue);
    void setWindowWidth(int newValue);

signals:
    void titleTextChanged();
    void infoTextTextChanged();
    void timeOutInfoTextChanged();
    void expandCollapseTextChanged();
    void displayTextChanged();
    void timerTextChanged();
    void titleColorChanged();
    void infoColorChanged();
    void timerColorChanged();
    void backgroundImageChanged();
    void timeoutChanged();
    void windowHeightChanged();
    void windowWidthChanged();
    void expandCollapse();
    void marginChanged();
    void offsetsChanged();

protected:
    void timerEvent(QTimerEvent *event) override;

private slots:
    void updateOffset();

private:
    void setExpiryTime();
    void updateExpired();
    void refreshMargin();
    QTimer m_offsetTimer;
    QString m_titleText;
    QString m_infoText = qtTrId("label_info_before_timeout");
    QString m_timeOutInfoText = qtTrId("label_info_after_timeout");
    QColor m_titleColor{255,255,255};
    QColor m_infoColor{255,255,255};
    QColor m_timerColor{255,255,255};
    QString m_backgroundImageFile;
    QString m_timeoutBackgroundImageFile;
    int m_hour{0};
    int m_minute{0};
    int m_windowWidth{0};
    int m_windowHeight{0};
    int m_margin{0};
    int m_offsetX{0};
    int m_offsetY{0};
    QDateTime m_expiryTime;
    bool m_expanded{false};
    bool m_expired{false};
};

#endif // APPLOGIC_H
