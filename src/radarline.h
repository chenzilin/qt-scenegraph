#pragma once

#include <QImage>
#include <QQuickItem>

#include <QMatrix4x4>

class QGraphicsRotation {
public:
    static inline void projectedRotate(QMatrix4x4 *matrix, qreal angle, qreal x, qreal y, qreal z) {
        matrix->projectedRotate(angle, x, y, z);
    }
};

class RadarLine : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString src READ src WRITE setSrc NOTIFY srcChanged)

public:
    explicit RadarLine(QQuickItem *parent = 0);

    void timerEvent(QTimerEvent *event) override;

    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

    void setSrc(const QString &src);
    QString src() const { return m_src; }

    QMatrix4x4 rotate(qreal angle, const QVector3D & origin, const QVector3D &  axis);

signals:
    void srcChanged(QString);

private:
    QString m_src;
    int mAngle = 0;
};
