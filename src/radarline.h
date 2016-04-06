#pragma once

#include <QColor>
#include <QQuickItem>

class RadarLine : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit RadarLine(QQuickItem *parent = 0);
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

    void setColor(const QColor &color);
    QColor color() const { return m_color; }

signals:
    void colorChanged(QColor);

private:

    int m_rectCnt;
    QColor m_color;
};
