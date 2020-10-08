#include "autoscrollinglabel.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOption>

#include <QDebug>

namespace XB
{

int AutoScrollingLabel::textWidth() const
{
    return QFontMetrics(this->font()).boundingRect(this->text()).width();
}

void AutoScrollingLabel::paintEvent(QPaintEvent* event)
{
    if (!this->text().isEmpty())
    {
        if (!this->animateOnMouseOver || this->mouseOverLabel)
        {
            if (this->rect().width() < this->textWidth())
            {
                QPainter painter(this);
                this->drawFrame(&painter);

                QStyleOption opt;
                opt.initFrom(this);

                auto textDirection = this->text().isRightToLeft() ? Qt::RightToLeft : Qt::LeftToRight;

                int align = QStyle::visualAlignment(textDirection, QFlag(this->alignment()));
                int flags =
                    align | (textDirection == Qt::LeftToRight ? Qt::TextForceLeftToRight : Qt::TextForceRightToLeft);

                auto rect = this->rect();
                if (textDirection == Qt::LeftToRight)
                    rect.adjust(-this->timerShift, 0, 0, 0);
                else
                    rect.adjust(this->timerShift, 0, 0, 0);

                this->style()->drawItemText(&painter,
                                            rect,
                                            flags,
                                            opt.palette,
                                            this->isEnabled(),
                                            this->text() + this->textSpacer + this->text(),
                                            this->foregroundRole());

                return;
            }
        }
    }

    QLabel::paintEvent(event);
}

void AutoScrollingLabel::enterEvent(QEvent* event)
{
    this->mouseOverLabel = true;
    QLabel::leaveEvent(event);
}

void AutoScrollingLabel::leaveEvent(QEvent* event)
{
    this->mouseOverLabel = false;
    if (this->animateOnMouseOver)
        this->timerShift = 0;
    QLabel::leaveEvent(event);
}

AutoScrollingLabel::AutoScrollingLabel(QString const& text, QWidget* parent) : QLabel(text, parent)
{
    setMouseTracking(true);
    connect(&this->animationTimer, &QTimer::timeout, this, [this]() {
        this->timerShift = (this->timerShift + 1) %
                           (this->textWidth() + QFontMetrics(this->font()).boundingRect(this->textSpacer).width());
        this->update();
    });
    this->animationTimer.start(50);
}

AutoScrollingLabel::AutoScrollingLabel(QWidget* parent) : AutoScrollingLabel(QString(), parent)
{
}

void AutoScrollingLabel::setAnimationTimeout(int msec)
{
    this->animationTimer.start(msec);
}

void AutoScrollingLabel::setAnimateOnMouseOver(bool b)
{
    this->animateOnMouseOver = b;
}

void AutoScrollingLabel::setTextSpacer(QString const& str)
{
    this->textSpacer = str;
}

} // namespace XB