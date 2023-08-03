#ifndef RPBUTTON_H
#define RPBUTTON_H

#include <QPushButton>
#include <QObject>
#include<QTimer>
#include<QEnterEvent>
#include<QPainter>
#include<QPainterPath>
class RpButton : public QPushButton
{
public:
    RpButton(const QString &text,QWidget *parent=nullptr);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
    void setDuration(const quint16 mesc);
    void setColor(QColor bk_color=QColor(46, 22, 177),
                  QColor cg_color=QColor(135, 89, 0));
    void setRadius(quint16 radius);

private:
    QTimer * m_timer;
    quint16 m_mesc=10;// QTimer 时间间隔
    QPointF m_center;// 鼠标进入位置
    QColor m_BK_Color;// 按钮基色
    QColor m_CG_Color;// 波纹颜色
    QString m_text;// 不让Button的paintEvent绘制字，自己绘制
    quint16 m_radius;// 波纹半径
    quint16 m_btn_radius;// 按钮圆角大小
    quint16 m_max_radius;
    void incRadius();
    void decRadius();
};

#endif // RPBUTTON_H
