#include <QSGNode>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>

#include <radarline.h>


RadarLine::RadarLine(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
}

void RadarLine::setSrc(const QString &src)
{
    QString tmpStr = src;
    tmpStr.remove(0, 3);

    if (tmpStr == m_src) return ;

    m_src = tmpStr;
    update();
    emit srcChanged(m_src);
}

QSGNode *RadarLine::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGSimpleTextureNode *node = static_cast<QSGSimpleTextureNode *>(oldNode);
    if (!node) {
        node = new QSGSimpleTextureNode();
        node->setTexture(window()->createTextureFromImage(QImage(m_src)));
        node->setOwnsTexture(true);
        node->setFiltering(QSGTexture::Linear);
    }

    node->setRect(boundingRect());

    return node;
}
