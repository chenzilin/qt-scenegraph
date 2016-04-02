#pragma once

#include <QColor>
#include <QQuickItem>

class RadarLine : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

    Q_PROPERTY(qreal translate READ translate WRITE setTranslate NOTIFY translateChanged)

public:
    explicit RadarLine(QQuickItem *parent = 0);
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

    void setColor(const QColor &color);
    QColor color() const { return m_color; }

    void setTranslate(const qreal &translate);
    qreal translate() const { return m_translate; }

signals:
    void colorChanged(QColor);
    void translateChanged(qreal);

private:

    int m_vertexCnt;
    QColor m_color;

    qreal m_translate;
};
