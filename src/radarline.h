#pragma once

#include <QHash>
#include <QList>
#include <QImage>
#include <QQuickItem>

class RadarLine : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QList<QString> sources READ sources WRITE setSources NOTIFY sourcesChanged)

public:
    explicit RadarLine(QQuickItem *parent = 0);
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

    void setSource(const QString &source);
    QString source() const { return m_source; }

    QList<QString> sources() const { return m_sources; }
    void setSources(const QList<QString> &sources);

signals:
    void sourceChanged(QString);
    void sourcesChanged(QList<QString>);

private:
    QString m_source;

    QList<QString> m_sources;
    QHash<QString, QImage> m_sourceImages;
};
