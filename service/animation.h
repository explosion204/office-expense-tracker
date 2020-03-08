#ifndef ANIMATION_H
#define ANIMATION_H

#include <QWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

class Animation
{
public:
    static void fadeIn(QWidget* widget, int duration);
    static void fadeOut(QWidget* widget, int duration);
};

#endif // ANIMATION_H
