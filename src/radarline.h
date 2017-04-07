#pragma once

#include <QImage>
#include <QQuickItem>

class RadarLine : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString src READ src WRITE setSrc NOTIFY srcChanged)

public:
    explicit RadarLine(QQuickItem *parent = 0);
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

    void setSrc(const QString &src);
    QString src() const { return m_src; }
signals:
    void srcChanged(QString);

private:
    QString m_src;
};
