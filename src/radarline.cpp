#include <QSGNode>
#include <QQuickWindow>
#include <QSGGeometryNode>
#include <QSGTextureMaterial>

#include <radarline.h>

#define Pi 3.1415926


RadarLine::RadarLine(QQuickItem *parent)
    : QQuickItem(parent)
{
    //m_vertexCnt = 4;
    m_vertexCnt = 6;
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
    QSGGeometryNode *node = Q_NULLPTR;




    QSGGeometry *geometry = Q_NULLPTR;

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), m_vertexCnt);
        //geometry->setDrawingMode(GL_TRIANGLE_STRIP);
        geometry->setDrawingMode(GL_TRIANGLE_STRIP);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);

        QSGTextureMaterial *material = new QSGTextureMaterial;
        QSGTexture *texture = window()->createTextureFromImage(QImage(m_src));
        texture->setFiltering(QSGTexture::None);
        texture->setHorizontalWrapMode(QSGTexture::ClampToEdge);
        texture->setVerticalWrapMode(QSGTexture::ClampToEdge);
        material->setTexture(texture);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    }
    else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(m_vertexCnt);
    }

    QRectF bounds = boundingRect();
    QSGGeometry::TexturedPoint2D* vertices = geometry->vertexDataAsTexturedPoint2D();

    vertices[0].set(bounds.x(), bounds.y(), 0.0f, 0.0f);
    vertices[1].set(bounds.x(), bounds.y() + bounds.height(), 0.0f, 1.0f);
    vertices[2].set(bounds.x() + bounds.width()/2, bounds.y(), 0.5f, 0.0f);
    vertices[3].set(bounds.x() + bounds.width()/2, bounds.y(), 0.5f, 0.0f);
    vertices[4].set(bounds.x() + bounds.width(), bounds.y() + bounds.height(), 1.0f, 1.0f);
    vertices[5].set(bounds.x() + bounds.width(), bounds.y(), 1.0f, 0.0f);



    node->markDirty(QSGNode::DirtyGeometry);

    return node;
}
