#pragma once

#include <QHash>
#include <QList>
#include <QImage>
#include <QQuickItem>

class RadarLine : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(uint index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(QList<QUrl> sources READ sources WRITE setSources NOTIFY sourcesChanged)

public:
    explicit RadarLine(QQuickItem *parent = 0);
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

    void setIndex(const uint &index);
    uint index() const { return m_index; }

    QList<QUrl> sources() const { return m_sources; }
    void setSources(const QList<QUrl> &sources);

signals:
    void indexChanged(uint);
    void sourcesChanged(QList<QUrl>);

private:

    QString urlToPath(const QUrl &url);

    uint m_index = 0;

    QList<QUrl> m_sources;
    QList<QImage> m_sourceImages;
};
