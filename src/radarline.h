#pragma once

#include <QHash>
#include <QList>
#include <QImage>
#include <QQuickItem>

class RadarLine : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(uint index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(QList<QString> sources READ sources WRITE setSources NOTIFY sourcesChanged)

public:
    explicit RadarLine(QQuickItem *parent = 0);
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

    void setIndex(const uint &index);
    uint index() const { return m_index; }

    QList<QString> sources() const { return m_sources; }
    void setSources(const QList<QString> &sources);

signals:
    void indexChanged(uint);
    void sourcesChanged(QList<QString>);

private:
    uint m_index = 0;

    QList<QString> m_sources;
    QHash<uint, QImage> m_sourceImages;
};
