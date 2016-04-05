#include <QSGNode>
#include <QQuickWindow>
#include <QSGSimpleRectNode>

#include <radarline.h>


RadarLine::RadarLine(QQuickItem *parent)
    : QQuickItem(parent)
{
    m_vertexCnt = 3;
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
        geometry->setDrawingMode(GL_TRIANGLE_STRIP);
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

    const QRectF rect = boundingRect();
    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    vertices[0].x = rect.left();
    vertices[0].y = rect.bottom();
    vertices[1].x = rect.left() + rect.width()/2;
    vertices[1].y = rect.top();
    vertices[2].x = rect.right();
    vertices[2].y = rect.bottom();

    node->markDirty(QSGNode::DirtyGeometry);

    return node;
}
