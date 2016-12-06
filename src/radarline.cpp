#include <QSGNode>
#include <QQuickWindow>
#include <QtConcurrent>
#include <QSGSimpleTextureNode>

#include <radarline.h>


RadarLine::RadarLine(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
}

void RadarLine::setIndex(const uint &index)
{
    if (index != m_index) {
        m_index = index;
        update();
        emit indexChanged(m_index);
    }
}

void RadarLine::setSources(const QList<QString> &sources) {

    m_sources.clear();
    m_sourceImages.clear();

    auto createImages = [this](const QList<QString> &sources) {
        int sourcesSize = sources.size();
        for (uint index = 0; index < (uint)sourcesSize; ++index) {
            this->m_sources.push_back(sources[index].mid(3));
            this->m_sourceImages.insert(index, QImage(sources[index].mid(3)));
        }

    };

    QtConcurrent::run(createImages, sources);

    update();
    emit sourcesChanged(m_sources);
}

QSGNode *RadarLine::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    if (m_sourceImages.isEmpty() || m_index >= (uint)m_sourceImages.size())
        return nullptr;

    QSGSimpleTextureNode *node = static_cast<QSGSimpleTextureNode *>(oldNode);
    if (!node) {
        node = new QSGSimpleTextureNode();
        node->setTexture(window()->createTextureFromImage(m_sourceImages[m_index]));
        node->setOwnsTexture(true);
        node->setFiltering(QSGTexture::Linear);
    }
    else {
        node->setTexture(window()->createTextureFromImage(m_sourceImages[m_index]));
    }

    node->setRect(boundingRect());
    return node;
}
