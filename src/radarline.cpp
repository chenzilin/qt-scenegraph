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
    if (m_index >= (uint)m_sourceImages.size())
        m_index = 0;

    if (index != m_index) {
        m_index = index;
        update();
        emit indexChanged(m_index);
    }
}

void RadarLine::setSources(const QList<QUrl> &sources) {

    m_sources.clear();
    m_sourceImages.clear();

    auto createImages = [this](const QList<QUrl> &sources) {
        int sourcesSize = sources.size();
        for (uint index = 0; index < (uint)sourcesSize; ++index) {
            this->m_sources.push_back(sources[index]);
            this->m_sourceImages.push_back(QImage(urlToPath(sources[index])));
        }
        qDebug() << "Child Thread Id: " << QThread::currentThreadId();
    };

    QtConcurrent::run(createImages, sources).waitForFinished();
    qDebug() << "Parent Thread Id: " << QThread::currentThreadId();

    update();
    emit sourcesChanged(m_sources);
}

QSGNode *RadarLine::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    if (m_sourceImages.isEmpty())
        return nullptr;

    if (m_index >= (uint)m_sourceImages.size()) {
        m_index = 0;
        emit indexChanged(m_index);
    }

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

QString RadarLine::urlToPath(const QUrl &url)
{
    QString path;
    if (url.scheme() == "file")
        path = url.toLocalFile();
    else if (url.scheme() == "qrc")
        path = ':' + url.path();
    else {
        qWarning() << "invalide path: " << url;
    }
    return path;
}
