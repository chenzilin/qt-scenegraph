#include <QSGNode>
#include <QSGSimpleRectNode>

#include <radarline.h>


RadarLine::RadarLine(QQuickItem *parent)
    : QQuickItem(parent)
{
    m_rectCnt = 255;
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
        node->setRect(boundingRect());

        for (int i = 0; i <= m_rectCnt; ++i) {
            node->appendChildNode(
                        new QSGSimpleRectNode(
                            QRectF(this->width()/m_rectCnt*i, 0, this->width()/m_rectCnt, this->height()),
                            QColor(i, 0, 0, i)));
        }
    }

    return node;
}
