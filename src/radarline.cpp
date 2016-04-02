#include <QSGNode>
#include <QQuickWindow>
#include <QSGSimpleRectNode>

#include <radarline.h>


RadarLine::RadarLine(QQuickItem *parent)
    : QQuickItem(parent)
{
    m_vertexCnt = 2;
    setFlag(ItemHasContents, true);
}

void RadarLine::setColor(const QColor &color)
{
    if (color == m_color) return ;

    m_color = color;
    update();
    emit colorChanged(m_color);
}

void RadarLine::setBeginVertex(const QPoint &beginVertex)
{
    if (beginVertex == m_beginVertex) return ;

    m_beginVertex = beginVertex;
    update();
    emit beginVertexChanged(m_beginVertex);
}

void RadarLine::setEndVertex(const QPoint &endVertex)
{
    if (endVertex == m_endVertex) return ;

    m_endVertex = endVertex;
    update();
    emit beginVertexChanged(m_endVertex);
}

QSGNode *RadarLine::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = Q_NULLPTR;
    QSGGeometry *geometry = Q_NULLPTR;

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), m_vertexCnt);
        geometry->setLineWidth(2);
        geometry->setDrawingMode(GL_LINES);
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

    vertices[0].set(m_beginVertex.x(), m_beginVertex.y());
    vertices[1].set(m_endVertex.x(), m_endVertex.y());

    node->markDirty(QSGNode::DirtyGeometry);

    return node;
}
