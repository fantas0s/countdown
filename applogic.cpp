#include "applogic.h"

#include <QUrl>
#include <QRandomGenerator>

AppLogic::AppLogic(QObject *parent)
    : QObject{parent}
{
    connect(this, &AppLogic::infoTextTextChanged, this, &AppLogic::displayTextChanged);
    connect(this, &AppLogic::timeOutInfoTextChanged, this, &AppLogic::displayTextChanged);
    startTimer(1000, Qt::TimerType::VeryCoarseTimer);
    setExpiryTime(); /* Use current 00:00 */
    connect(&m_offsetTimer, &QTimer::timeout, this, &AppLogic::updateOffset);
    m_offsetTimer.start(std::chrono::seconds(60));
}

QString AppLogic::backgroundImageFileName() const
{
    if (m_backgroundImageFile.isEmpty())
    {
        return qtTrId("textfield_default_background_before_timeout");
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
        return qtTrId("textfield_default_background_after_timeout");
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

int AppLogic::windowHeight() const
{
    return m_windowHeight;
}

int AppLogic::windowWidth() const
{
    return m_windowWidth;
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
        return qtTrId("button_to_window");
    }
    else
    {
        return qtTrId("button_to_fullscreen");
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
{
    return m_expiryTime.toString(qtTrId("textfield_expiry_datetime_format"));
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
    return qtTrId("label_timer_3parameter_time").arg(hours, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
}

bool AppLogic::defaultBackgroundImage() const
{
    return m_backgroundImageFile.isEmpty();
}

bool AppLogic::defaultTimeoutBackgroundImage() const
{
    return m_timeoutBackgroundImageFile.isEmpty();
}

int AppLogic::margin() const
{
    return m_margin;
}

int AppLogic::offsetX() const
{
    return m_offsetX;
}

int AppLogic::offsetY() const
{
    return m_offsetY;
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
    if (newValue > 23)
        newValue = 23;
    else if (newValue < 0)
        newValue = 0;
    if (m_hour != newValue)
    {
        m_hour = newValue;
        setExpiryTime();
    }
}

void AppLogic::setTargetMinute(int newValue)
{
    if (newValue > 59)
        newValue = 59;
    else if (newValue < 0)
        newValue = 0;
    if (m_minute != newValue)
    {
        m_minute = newValue;
        setExpiryTime();
    }
}

void AppLogic::setWindowHeight(int newValue)
{
    if (m_windowHeight != newValue)
    {
        m_windowHeight = newValue;
        emit windowHeightChanged();
        refreshMargin();
    }
}

void AppLogic::setWindowWidth(int newValue)
{
    if (m_windowWidth != newValue)
    {
        m_windowWidth = newValue;
        emit windowWidthChanged();
        refreshMargin();
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

void AppLogic::updateOffset()
{
    const int newOffsetX = QRandomGenerator::global()->bounded(m_margin);
    const int newOffsetY = QRandomGenerator::global()->bounded(m_margin);
    m_offsetX = -1 * newOffsetX;
    m_offsetY = -1 * newOffsetY;
    emit offsetsChanged();
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

void AppLogic::refreshMargin()
{
    qreal newMargin = qMin(m_windowHeight, m_windowWidth);
    newMargin = newMargin / 40;
    int intMargin = qFloor(newMargin);
    if (m_margin != intMargin)
    {
        m_margin = intMargin;
        emit marginChanged();
        updateOffset();
    }
}
