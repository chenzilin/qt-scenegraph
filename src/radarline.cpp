#include <QSGNode>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>

#include <radarline.h>

#include <stdio.h>

#include <QVector3D>
#include <QMatrix4x4>


RadarLine::RadarLine(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);

    startTimer(10);
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

/*
 * 实际旋转函数
 * 参数一: 旋转角度
 * 参数二: 旋转点
 * 参数三: 旋转方向
 */
QMatrix4x4 RadarLine::rotate(qreal angle, const QVector3D & origin, const QVector3D &  axis)
{
    QMatrix4x4 ret;
    if (angle  == 0 || axis.isNull() ) return ret;

    ret.translate(origin);
    QGraphicsRotation::projectedRotate(&ret, angle, axis.x(), axis.y(), axis.z());
    ret.translate(-origin);
    return ret;
}

QSGNode *RadarLine::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    auto node = static_cast<QSGTransformNode *>(oldNode);

    if (!node) {
        node = new QSGTransformNode();

        auto textureNode = new QSGSimpleTextureNode();
        textureNode->setTexture(window()->createTextureFromImage(QImage(m_src)));
        textureNode->setOwnsTexture(true);
        textureNode->setFiltering(QSGTexture::Linear);
        textureNode->setRect(boundingRect());

        node->appendChildNode(textureNode);
        textureNode->setFlag(QSGNode::OwnedByParent);
    }

    //node->setMatrix(rotate( mAngle, QVector3D(100, 100, 0), QVector3D(1, 1, 0)));
    //node->setMatrix(rotate( mAngle, QVector3D(100, 100, 0), QVector3D(0, 1, 0)));
    node->setMatrix(rotate( mAngle, QVector3D(100, 100, 0), QVector3D(1.0, 0, 0)));

    node->markDirty(QSGNode::DirtyNodeAdded);
    return node;
}

void RadarLine::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if (++mAngle >= 360) {
        mAngle = 0;
    }

    update();
}
