#include "animation.h"

void Animation::fadeIn(QWidget *widget, int duration)
{
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(effect);
    QPropertyAnimation *a = new QPropertyAnimation(effect, "opacity");
    a->setDuration(duration);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
}

void Animation::fadeOut(QWidget *widget, int duration)
{
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(effect);
    QPropertyAnimation *a = new QPropertyAnimation(effect, "opacity");
    a->setDuration(duration);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
}
