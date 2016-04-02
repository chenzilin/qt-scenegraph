#include <QSGNode>
#include <QQuickWindow>
#include <QSGSimpleRectNode>

#include <radarline.h>


RadarLine::RadarLine(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
}

void RadarLine::setColor(const QColor &color)
{
    if (color == m_color) return ;

    m_color = color;
    update();
    emit colorChanged(m_color);
}

QSGNode *RadarLine::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGSimpleRectNode *node = static_cast<QSGSimpleRectNode *>(oldNode);
    if (!node) {
        node = new QSGSimpleRectNode();
        node->setColor(m_color);
    }

    node->setRect(boundingRect());

    return node;
}
