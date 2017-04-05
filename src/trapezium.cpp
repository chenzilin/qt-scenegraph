#include "trapezium.h"
#include <QSGNode>
#include <QQuickWindow>
#include <QSGFlatColorMaterial>
#include <QSGTextureMaterial>
#include <QSGGeometryNode>

Trapezium::Trapezium(QQuickItem*parent):QQuickItem(parent)
{
    m_rate=1;//初始值比例设成1
    m_partNum=50;//初始值四等分
    rateWholeHeight=0;//初始下降程度
    m_vertexCnt=(m_partNum+1)*2;//一半部分需要绘制的顶点数

    m_direction="None";

    setFlag(ItemHasContents,true);

}
Trapezium::~Trapezium()
{
}
void Trapezium::setRate(const qreal &rate)
{
    qreal tmp = rate;
    if (tmp == m_rate) return ;
    m_rate = tmp;
    update();
    emit rateChanged(m_rate);
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
    int tmpNum=partNum;
    if(tmpNum==m_partNum)return;
    m_partNum=tmpNum;
    update();
    emit partNumChanged(m_partNum);
}
void Trapezium::setDirection(const QString &direction)
{
    QString tmpStr = direction;

    if (tmpStr == m_direction) return ;

    m_direction = tmpStr;
    update();
    emit directionChanged(m_direction);
}



QSGNode*Trapezium::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = Q_NULLPTR;
    QSGGeometry *geometry = Q_NULLPTR;
    m_vertexCnt=(m_partNum+1)*2;

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), m_vertexCnt);
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


    QSGGeometry::TexturedPoint2D* vertices = geometry->vertexDataAsTexturedPoint2D();

    qreal myy=0.0;//自定义相对位置
    qreal myx=0.0;
    qreal mywidth=this->width();
    qreal myheight=this->height();
    qreal d1=0;
    qreal d2=0;
    qreal d=0;
    QPointF myPoint1[m_vertexCnt+1];


    if(m_direction=="left")
    {
        //设置下降幅度
        rateWholeHeight=(1-m_rate)/2*myheight;
        for(int i=0;i<=m_vertexCnt-1;i++)//bug是数组越界导致
        {

                d1=rateWholeHeight*(m_partNum-((i-1)/2))/m_partNum;//变化程度
                d2=rateWholeHeight*(m_partNum-(i/2))/m_partNum;

            if(i%2==0)
            {
                myPoint1[i]=QPointF(myx+mywidth/m_partNum*i/2,myy+d2);
                vertices[i].set(myPoint1[i].x(),myPoint1[i].y(),1.0/m_partNum*i/2,0.0);
            }else
            {
                myPoint1[i]=QPointF(myx+mywidth/m_partNum*(i-1)/2,myy+myheight-d1);
                vertices[i].set(myPoint1[i].x(),myPoint1[i].y(),1.0/m_partNum*(i-1)/2,1.0);
            }
        }

    }
    else if(m_direction=="right")
    {
        rateWholeHeight=(1-m_rate)/2*myheight;
        for(int i=0;i<=m_vertexCnt-1;i++)
        {
            d=rateWholeHeight*(i/2)/m_partNum;

            if(i%2==0)
            {
                myPoint1[i]=QPointF(myx+mywidth/m_partNum*i/2,myy+d);
                vertices[i].set(myPoint1[i].x(),myPoint1[i].y(),1.0/m_partNum*i/2,0.0);
            }else
            {
                myPoint1[i]=QPointF(myx+mywidth/m_partNum*(i-1)/2,myy+myheight-d);
                vertices[i].set(myPoint1[i].x(),myPoint1[i].y(),1.0/m_partNum*(i-1)/2,1.0);

            }
        }


    }
    else if(m_direction=="top")
    {
        rateWholeWidth=(1-m_rate)/2*mywidth;
        for(int i=0;i<=m_vertexCnt-1;i++)
        {

                d1=rateWholeWidth*(m_partNum-((i-1)/2))/m_partNum;
                d2=rateWholeWidth*(m_partNum-(i/2))/m_partNum;

            if(i%2==0)
            {
                myPoint1[i]=QPointF(myx+mywidth-d2,myy+myheight/m_partNum*i/2);
                vertices[i].set(myPoint1[i].x(),myPoint1[i].y(),1.0,1.0/m_partNum*i/2);
            }else
            {
                myPoint1[i]=QPointF(myx+d1,myy+myheight/m_partNum*(i-1)/2);
                vertices[i].set(myPoint1[i].x(),myPoint1[i].y(),0.0,1.0/m_partNum*(i-1)/2);
            }
        }

    }
    else {
        rateWholeWidth=(1-m_rate)/2*mywidth;

        for(int i=0;i<=m_vertexCnt-1;i++)
        {
            d=rateWholeWidth*(i/2)/m_partNum;
            if(i%2==0)
            {
                myPoint1[i]=QPointF(myx+d,myy+myheight/m_partNum*i/2);
                vertices[i].set(myPoint1[i].x(),myPoint1[i].y(),0.0,1.0/m_partNum*i/2);
            }else
            {
                myPoint1[i]=QPointF(myx+mywidth-d,myy+myheight/m_partNum*(i-1)/2);
                vertices[i].set(myPoint1[i].x(),myPoint1[i].y(),1.0,1.0/m_partNum*(i-1)/2);
            }
        }
    }


    node->markDirty(QSGNode::DirtyGeometry);

    return node;
}
