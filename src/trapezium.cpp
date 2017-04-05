#include <QSGNode>
#include <QQuickWindow>
#include <QSGGeometryNode>
#include <QSGTextureMaterial>
#include <QSGFlatColorMaterial>

#include "trapezium.h"

Trapezium::Trapezium(QQuickItem*parent):QQuickItem(parent)
{
    m_rate = 1;                        // 初始值比例设成1
    m_partNum = 50;                    // 初始值四等分
    m_rateWholeHeight = 0;             // 初始下降程度
    m_rateWholeWidth = 0;              // 初始缩短程度
    m_vertexCnt = (m_partNum + 1) * 2; // 一半部分需要绘制的顶点数

    m_direction = Left;

    setFlag(ItemHasContents, true);
}

void Trapezium::setRate(const qreal &rate)
{
    if (rate != m_rate) {
        m_rate = rate;
        update();
        emit rateChanged(m_rate);
    }
}

void Trapezium::setSrc(const QString &src)
{
    QString tmpStr = src;
    tmpStr.remove(0, 3);

    if (tmpStr == m_src) return ;
    m_src = tmpStr;
    update();
    emit srcChanged(m_src);
}

void Trapezium::setPartNum(const int &partNum)
{
    int tmpNum = partNum;
    if(tmpNum == m_partNum)return;
    m_partNum = tmpNum;
    update();
    emit partNumChanged(m_partNum);
}

void Trapezium::setDirection(const Direction &direction)
{
    if(direction != m_direction){
        m_direction = direction;
        update();
        emit directionChanged(m_direction);
    }
}

void Trapezium::dealWith(Direction direction,QSGGeometry::TexturedPoint2D*vertices)
{
    qreal degree = 0;
    QPointF myPoint1[m_vertexCnt+1];
    m_rateWholeHeight = (1-m_rate)/2*height();
    m_rateWholeWidth = (1-m_rate)/2*width();

    if (direction == Left || direction == Right) {
        for (int i = 0; i <= m_vertexCnt - 1; ++i) { // bug是数组越界导致
            if(direction == Left ){
                degree = m_rateWholeHeight * (m_partNum - (i / 2)) / m_partNum;
            }
            else {
                degree = m_rateWholeHeight * (i / 2) / m_partNum;
            }
            if (i % 2 == 0) {
                myPoint1[i]=QPointF(width() / m_partNum * i / 2, degree);
                vertices[i].set(myPoint1[i].x(), myPoint1[i].y(), 1.0 / m_partNum * i / 2, 0.0);
            }
            else {
                myPoint1[i]=QPointF(width() / m_partNum * (i - 1) / 2,height() - degree);
                vertices[i].set(myPoint1[i].x(),myPoint1[i].y(),1.0 / m_partNum*(i - 1) / 2,1.0);
            }
        }
    }
    else {
        for (int i = 0; i <= m_vertexCnt - 1; ++i) {
            if (direction == Top) {
                degree = m_rateWholeWidth * (m_partNum - (i/2)) / m_partNum;
            }
            else {
                degree = m_rateWholeWidth * (i / 2) / m_partNum;
            }
            if (i % 2 == 0) {
                myPoint1[i]=QPointF(width()-degree,height()/m_partNum*i/2);
                vertices[i].set(myPoint1[i].x(),myPoint1[i].y(),1.0,1.0/m_partNum*i/2);
            }
            else {
                myPoint1[i]=QPointF(degree,height()/m_partNum*(i-1)/2);
                vertices[i].set(myPoint1[i].x(),myPoint1[i].y(),0.0,1.0/m_partNum*(i-1)/2);
            }
        }
    }
}

QSGNode*Trapezium::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = Q_NULLPTR;
    QSGGeometry *geometry = Q_NULLPTR;
    m_vertexCnt = (m_partNum+1)*2;

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), m_vertexCnt);
        geometry -> setDrawingMode(GL_TRIANGLE_STRIP);
        node -> setGeometry(geometry);
        node -> setFlag(QSGNode::OwnsGeometry);

        QSGTextureMaterial *material = new QSGTextureMaterial;
        QSGTexture *texture = window()->createTextureFromImage(QImage(m_src));
        texture -> setFiltering(QSGTexture::None);
        texture -> setHorizontalWrapMode(QSGTexture::ClampToEdge);
        texture -> setVerticalWrapMode(QSGTexture::ClampToEdge);
        material -> setTexture(texture);
        node -> setMaterial(material);
        node -> setFlag(QSGNode::OwnsMaterial);
    }
    else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry -> allocate(m_vertexCnt);
    }
    QSGGeometry::TexturedPoint2D* vertices = geometry->vertexDataAsTexturedPoint2D();

    dealWith(m_direction,vertices);

    node->markDirty(QSGNode::DirtyGeometry);

    return node;
}
