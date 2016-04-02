#include <QSGNode>
#include <QQuickWindow>
#include <QSGSimpleRectNode>

#include <radarline.h>

#define Pi 3.1415926


RadarLine::RadarLine(QQuickItem *parent)
    : QQuickItem(parent)
{
    m_vertexCnt = 100;
    setFlag(ItemHasContents, true);
}

void RadarLine::setColor(const QColor &color)
{
    if (color == m_color) return ;

    m_color = color;
    update();
    emit colorChanged(m_color);
}

QSGNode *RadarLine::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = Q_NULLPTR;
    QSGGeometry *geometry = Q_NULLPTR;

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), m_vertexCnt);
        geometry->setLineWidth(2);
        geometry->setDrawingMode(GL_LINE_STRIP);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);

        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(m_color);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    }
    else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(m_vertexCnt);
    }

    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    for (int i = 0; i < m_vertexCnt; ++i) {
        int x = i*this->width()/100;
        vertices[i].set(x, this->height()-this->height()*(1+sin(2*Pi*x/this->width()))/2);
    }

    node->markDirty(QSGNode::DirtyGeometry);

    return node;
}
