#ifndef TRAPEZIUM_H
#define TRAPEZIUM_H

#include <QQuickItem>

class Trapezium : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int partNum READ partNum WRITE setPartNum NOTIFY partNumChanged)
    Q_PROPERTY(qreal rate READ rate WRITE setRate NOTIFY rateChanged)
    Q_PROPERTY(QString src READ src WRITE setSrc NOTIFY srcChanged)
    Q_PROPERTY(QString direction READ direction WRITE setDirection NOTIFY directionChanged)

public:
    Trapezium(QQuickItem*parent=0);
    ~Trapezium();
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    int partNum() const {return m_partNum;}
    qreal rate() const {return m_rate;}
    QString src() const { return m_src; }
    QString direction() const{return m_direction;}

    void setPartNum(const int &partNum );
    void setRate(const qreal &rate);
    void setSrc(const QString &src);
    void setDirection(const QString &direction);


signals:

    void partNumChanged(int);
    void rateChanged(qreal);
    void srcChanged(QString);
    void directionChanged(QString);


public slots:

private:
    QPointF m_p0;
    qreal m_rate;
    QString m_src;
    QString m_direction;
    int m_vertexCnt;
    int m_partNum;
    qreal rateWholeHeight;
    qreal rateWholeWidth;
};

#endif // TRAPEZIUM_H
