#pragma once

#include <QColor>
#include <QPoint>
#include <QQuickItem>

class RadarLine : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QPoint beginVertex READ beginVertex WRITE setBeginVertex NOTIFY beginVertexChanged)
    Q_PROPERTY(QPoint endVertex READ endVertex WRITE setEndVertex NOTIFY endVertexChanged)

public:
    explicit RadarLine(QQuickItem *parent = 0);
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

    void setColor(const QColor &color);
    QColor color() const { return m_color; }

    void setBeginVertex(const QPoint &beginVertex);
    QPoint beginVertex() const { return m_beginVertex; }

    void setEndVertex(const QPoint &endVertex);
    QPoint endVertex() const { return m_endVertex; }

signals:
    void colorChanged(QColor);
    void beginVertexChanged(QPoint);
    void endVertexChanged(QPoint);

private:

    int m_vertexCnt;
    QColor m_color;

    QPoint m_beginVertex;
    QPoint m_endVertex;
};
