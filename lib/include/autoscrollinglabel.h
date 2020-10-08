#ifndef AUTOSCROLLINGLABEL_H
#define AUTOSCROLLINGLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QTimer>

namespace XB
{

class AutoScrollingLabel : public QLabel
{
    Q_OBJECT
private:
    Q_DISABLE_COPY(AutoScrollingLabel)

    bool    animateOnMouseOver = true;
    bool    mouseOverLabel     = false;
    QTimer  animationTimer;
    int     animationTimeout = 0;
    int     timerShift       = 0;
    QString textSpacer       = " - ";

    int textWidth() const;

protected:
    virtual void paintEvent(QPaintEvent*) override;
    virtual void enterEvent(QEvent*) override;
    virtual void leaveEvent(QEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;

public:
    AutoScrollingLabel(QString const& text, QWidget* parent = nullptr);
    AutoScrollingLabel(QWidget* parent = nullptr);

    void setAnimationTimeout(int msec);
    void setAnimateOnMouseOver(bool);
    void setTextSpacer(QString const&);
};

} // namespace XB

#endif // AUTOSCROLLINGLABEL_H
