#include <QSGNode>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>

#include <radarline.h>


RadarLine::RadarLine(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
}

void RadarLine::setSource(const QString &source)
{

    if (source != m_source) {
        m_source = source;
        update();
        emit sourceChanged(m_source);
    }
}

void RadarLine::setSources(const QList<QString> &sources) {

    m_sources.clear();
    m_sourceImages.clear();

    for (const auto &source: sources) {
        m_sources.push_back(source.mid(3));
        m_sourceImages.insert(source.mid(3), QImage(source.mid(3)));
    }

    update();
    emit sourcesChanged(m_sources);
}

QSGNode *RadarLine::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGSimpleTextureNode *node = static_cast<QSGSimpleTextureNode *>(oldNode);
    if (!node) {
        node = new QSGSimpleTextureNode();
        node->setTexture(window()->createTextureFromImage(m_sourceImages[m_source]));
        node->setOwnsTexture(true);
        node->setFiltering(QSGTexture::Linear);
    }
    else {
        node->setTexture(window()->createTextureFromImage(m_sourceImages[m_source]));
    }

    node->setRect(boundingRect());
    return node;
}
