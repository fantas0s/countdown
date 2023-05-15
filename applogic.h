#ifndef APPLOGIC_H
#define APPLOGIC_H

#include <QColor>
#include <QDateTime>
#include <QObject>
#include <QString>

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
    Q_PROPERTY(int targetHour READ targetHour WRITE setTargetHour NOTIFY timeoutChanged)
    Q_PROPERTY(int targetMinute READ targetMinute WRITE setTargetMinute NOTIFY timeoutChanged)

    /* logical outputs */
    /* name of background image */
    Q_PROPERTY(QString backgroundImageFileName READ backgroundImageFileName NOTIFY backgroundImageChanged)
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
public:
    explicit AppLogic(QObject *parent = nullptr);
    QString backgroundImageFileName() const;
    int targetHour() const;
    int targetMinute() const;
    QString backgroundImage() const;
    QString expandCollapseText() const;
    void setExpandedState(bool expanded);
    QString displayText() const;
    QString timeoutTimeString() const;
    QString timerText() const;
    bool defaultBackgroundImage() const;

    void setBackgroundImage(const QString& string);
    void setTargetHour(int newValue);
    void setTargetMinute(int newValue);

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
    void expandCollapse();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    void setExpiryTime();
    void updateExpired();
    QString m_titleText;
    QString m_infoText;
    QString m_timeOutInfoText;
    QColor m_titleColor{255,255,255};
    QColor m_infoColor{255,255,255};
    QColor m_timerColor{255,255,255};
    QString m_backgroundImageFile;
    int m_hour{0};
    int m_minute{0};
    QDateTime m_expiryTime;
    bool m_expanded{false};
    bool m_expired{false};
};

#endif // APPLOGIC_H
