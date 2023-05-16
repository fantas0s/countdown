#include "applogic.h"

#include <QUrl>

AppLogic::AppLogic(QObject *parent)
    : QObject{parent}
{
    connect(this, &AppLogic::infoTextTextChanged, this, &AppLogic::displayTextChanged);
    connect(this, &AppLogic::timeOutInfoTextChanged, this, &AppLogic::displayTextChanged);
    startTimer(1000, Qt::TimerType::VeryCoarseTimer);
    setExpiryTime(); /* Use current 00:00 */
}

QString AppLogic::backgroundImageFileName() const
{
    if (m_backgroundImageFile.isEmpty())
    {
        return tr("Default background");
    }
    else
    {
        return QUrl(m_backgroundImageFile).fileName();
    }
}

QString AppLogic::timeoutBackgroundImageFileName() const
{
    if (m_timeoutBackgroundImageFile.isEmpty())
    {
        return tr("Default timeout background");
    }
    else
    {
        return QUrl(m_timeoutBackgroundImageFile).fileName();
    }
}

int AppLogic::targetHour() const
{
    return m_hour;
}

int AppLogic::targetMinute() const
{
    return m_minute;
}

QString AppLogic::backgroundImage() const
{
    if (m_expired)
    {
        return timeoutBackgroundImage();
    }
    else
    {
        if (m_backgroundImageFile.isEmpty())
        {
            return "qrc:/qt/qml/Countdown/background.jpg";
        }
        else
        {
            return m_backgroundImageFile;
        }
    }
}

QString AppLogic::timeoutBackgroundImage() const
{
    if (m_timeoutBackgroundImageFile.isEmpty())
    {
        return "qrc:/qt/qml/Countdown/timeoutbackground.jpg";
    }
    else
    {
        return m_timeoutBackgroundImageFile;
    }
}

QString AppLogic::expandCollapseText() const
{
    if (m_expanded)
    {
        return tr("To window");
    }
    else
    {
        return tr("To fullscreen");
    }
}

void AppLogic::setExpandedState(bool expanded)
{
    if (m_expanded != expanded)
    {
        m_expanded = expanded;
        emit expandCollapseTextChanged();
    }
}

QString AppLogic::displayText() const
{
    if (m_expired)
    {
        return m_timeOutInfoText;
    }
    else
    {
        return m_infoText;
    }
}

QString AppLogic::timeoutTimeString() const
{return m_expiryTime.toString(tr("hh:mm dd.MM.yyyy"));
}

QString AppLogic::timerText() const
{
    if (m_expired)
        return "";
    const auto currentTime = QDateTime::currentDateTime();
    qint64 seconds;
    if (m_expiryTime > currentTime)
    {
        seconds = currentTime.secsTo(m_expiryTime);
    }
    else
    {
        seconds = 0;
    }
    qint64 minutes = seconds / 60;
    qint64 hours = minutes / 60;
    seconds -= minutes * 60;
    minutes -= hours * 60;
    return tr("%1:%2:%3").arg(hours, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
}

bool AppLogic::defaultBackgroundImage() const
{
    return m_backgroundImageFile.isEmpty();
}

bool AppLogic::defaultTimeoutBackgroundImage() const
{
    return m_timeoutBackgroundImageFile.isEmpty();
}

void AppLogic::setBackgroundImage(const QString &string)
{
    if (m_backgroundImageFile != string)
    {
        m_backgroundImageFile = string;
        emit backgroundImageChanged();
    }
}

void AppLogic::setTimeoutBackgroundImage(const QString &string)
{
    if (m_timeoutBackgroundImageFile != string)
    {
        m_timeoutBackgroundImageFile = string;
        emit backgroundImageChanged();
    }
}

void AppLogic::setTargetHour(int newValue)
{
    if (m_hour != newValue)
    {
        m_hour = newValue;
        setExpiryTime();
    }
}

void AppLogic::setTargetMinute(int newValue)
{
    if (m_minute != newValue)
    {
        m_minute = newValue;
        setExpiryTime();
    }
}

void AppLogic::timerEvent(QTimerEvent *event)
{
    /* Only makes difference if not yet expired. */
    if (!m_expired) {
        emit timerTextChanged();
        updateExpired();
    }
}

void AppLogic::setExpiryTime()
{
    const auto currentTime = QDateTime::currentDateTime();
    QDateTime testExpiryTime{QDate::currentDate(), QTime{m_hour, m_minute}};
    if (testExpiryTime < currentTime)
    {
        testExpiryTime = testExpiryTime.addDays(1);
    }
    if (testExpiryTime != m_expiryTime)
    {
        m_expiryTime = testExpiryTime;
        emit timeoutChanged();
        emit timerTextChanged();
        updateExpired();
    }
}

void AppLogic::updateExpired()
{
    const auto currentTime = QDateTime::currentDateTime();
    const bool stillRunning = (m_expiryTime > currentTime);
    if (stillRunning == m_expired)
    {
        m_expired = !stillRunning;
        emit displayTextChanged();
        emit backgroundImageChanged();
        emit timerTextChanged();
    }
}
