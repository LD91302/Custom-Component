#include "rpbutton.h"
#include "qevent.h"

RpButton::RpButton(const QString &text,QWidget *parent)
{
    setParent(parent);
    m_text= text;
    m_radius=0;
    m_btn_radius=10;
    m_max_radius=qPow(width()*width()+height()*height(),0.5);
    m_BK_Color = QColor(46, 22, 177);
    m_CG_Color = QColor(255,189,0);
    m_timer = new QTimer(this);
    m_timer->setInterval(m_mesc);
    connect(m_timer,&QTimer::timeout,this,&RpButton::incRadius);
    setStyleSheet(
        "*{"
           "border:none;"
           "border-radius:10px;"
           "background-color:rgb(46, 22, 177);"
           "color:rgb(255, 255, 255);"
        "}"
    );
    update();

}
void RpButton::setRadius(quint16 radius){
    //
    m_btn_radius = radius;
}
void RpButton::setColor(QColor bk_color,QColor cg_color){
    m_BK_Color = bk_color;
    m_CG_Color = cg_color;
    update();// 直接更新
}
void RpButton::setDuration(const quint16 mesc){
    assert(mesc>0);
    m_mesc = mesc;
    m_timer->setInterval(m_mesc);
}
void RpButton::incRadius(){
    m_max_radius=qPow(width()*width()+height()*height(),0.5);
    m_radius+=1;
    if(m_radius >m_max_radius){
        m_timer->stop();
        return;
    }
    update();
}
void RpButton::decRadius(){
    m_radius-=1;
    if(m_radius <=0){
        m_timer->stop();
        return;
    }
    update();

}

void RpButton::paintEvent(QPaintEvent *event){
    QPushButton::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if(!m_center.isNull()){
        QBrush brush(m_CG_Color);
        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);
        QPainterPath path;
        path.addRoundedRect(rect(),m_btn_radius,m_btn_radius);
        painter.setClipPath(path);
        painter.drawEllipse(m_center,m_radius,m_radius);
    }
    painter.setPen(QPen(Qt::white));
    painter.drawText(rect(),Qt::AlignCenter,m_text);


}

void RpButton::enterEvent(QEnterEvent *event){
    m_center = event->position();
    disconnect(m_timer,&QTimer::timeout,this,&RpButton::decRadius);
    connect(m_timer,&QTimer::timeout,this,&RpButton::incRadius);
    m_timer->start();
    QPushButton::enterEvent(event);
}
void RpButton::leaveEvent(QEvent *event){
    m_center = mapFromGlobal(QCursor::pos());
    disconnect(m_timer,&QTimer::timeout,this,&RpButton::incRadius);
    connect(m_timer,&QTimer::timeout,this,&RpButton::decRadius);
    m_timer->start();
    QPushButton::leaveEvent(event);
}
