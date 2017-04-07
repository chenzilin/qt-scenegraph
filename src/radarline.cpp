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

//    // x正轴(右)平移100
//    QMatrix4x4 matrix(1, 0, 0, 100,
//                      0, 1, 0, 0,
//                      0, 0, 1, 0,
//                      0, 0, 0, 1);
//    node->setMatrix(matrix);

//    // y正轴(下)平移100
//    QMatrix4x4 matrix(1, 0, 0, 0,
//                      0, 1, 0, 100,
//                      0, 0, 1, 0,
//                      0, 0, 0, 1);
//    node->setMatrix(matrix);

//    // 缩小一半变换
//    QMatrix4x4 matrix(1, 0, 0, 0,
//                      0, 1, 0, 0,
//                      0, 0, 1, 0,
//                      0, 0, 0, 1.5);
//    node->setMatrix(matrix);

//    // x正轴(右)平移100, y正轴(下)平移100
//    QMatrix4x4 matrix;
//    matrix.translate(100, 100);
//    node->setMatrix(matrix);

//    // 缩小一半变换
//    QMatrix4x4 matrix;
//    matrix.scale(0.5);
//    node->setMatrix(matrix);

//    // 绕着中心旋转45度
    QMatrix4x4 matrix;
    matrix.translate(width()/2, width()/2);
    matrix.rotate(45, 0, 0, 1);
    matrix.translate(-width()/2, -width()/2);
    node->setMatrix(matrix);

    node->markDirty(QSGNode::DirtyNodeAdded);

    return node;
}



