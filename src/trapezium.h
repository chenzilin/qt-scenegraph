#ifndef TRAPEZIUM_H
#define TRAPEZIUM_H

#include <QQuickItem>

class Trapezium : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(int partNum READ partNum WRITE setPartNum NOTIFY partNumChanged)
    Q_PROPERTY(qreal rate READ rate WRITE setRate NOTIFY rateChanged)
    Q_PROPERTY(QString src READ src WRITE setSrc NOTIFY srcChanged)
    Q_PROPERTY(Direction direction READ direction WRITE setDirection NOTIFY directionChanged)


public:
    Trapezium(QQuickItem*parent=0);
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    enum Direction{ Left, Right, Top, Bottom };
    Q_ENUM(Direction)

    int partNum() const { return m_partNum; }
    qreal rate() const { return m_rate; }
    QString src() const { return m_src; }
    Direction direction() const { return m_direction; }

    void setPartNum (const int &partNum);
    void setRate (const qreal &rate);
    void setSrc (const QString &src);
    void setDirection (const Direction &direction);

signals:

    void partNumChanged (int);
    void rateChanged (qreal);
    void srcChanged (QString);
    void directionChanged (Direction);

private:
    QPointF m_p0;
    qreal m_rate;
    QString m_src;
    int m_vertexCnt;
    int m_partNum;
    Direction m_direction;
    qreal m_rateWholeHeight;
    qreal m_rateWholeWidth;
};

#endif // TRAPEZIUM_H
