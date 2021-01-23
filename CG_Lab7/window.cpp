#include "window.h"

Window::point::point(int e, double X, double Y){
    edge=e;
    x=X;
    y=Y;
}

Window::point::point(double X, double Y){
    x=X;
    y=Y;
}
Window::point::point(QPointF p){
    x=p.x();
    y=p.y();
}

Window::point::~point(){}
void Window::point::draw(QPainter& p){
    p.drawRect(x-edge, y-edge, 2*edge, 2*edge);

}
bool Window::point::pressed(QPointF p){
    return (p.x()>=x-edge) && (p.x()<=x+edge)
        && (p.y()>=y-edge) && (p.y()<=y+edge) ;
}
void Window::point::move(QPointF p){
    x=p.x();
    y=p.y();
}

void Window::point::set_scale(int e){
    edge=e;
}
QPointF Window::point::pos(){
    return QPointF(x, y);
}


Window::Window(QWidget *parent)
    : QMainWindow(parent){
    points.push_back(point(  scale/4, 3*scale/4));
    points.push_back(point(  scale/4,   scale/4));
    points.push_back(point(  scale/2,   scale/2));
    points.push_back(point(3*scale/4,   scale/4));
    points.push_back(point(3*scale/4, 3*scale/4));

    l_aprox = new QLabel("aproximation", this);
    l_aprox->move(10, 10);
    aprox = new QSpinBox(this);
    aprox -> setRange(1, 150);
    aprox -> setValue(100);
    aprox -> move(80, 10);
    aprox -> setSingleStep(5);
    connect(aprox, SIGNAL(valueChanged(int)), this, SLOT(changed(int)));


}

void Window::changed(bool){
    update();
}

void Window::changed(int){
    update();
}

void Window::mousePressEvent(QMouseEvent* m){
    for(int i=0; i<points.size(); ++i)
        if(points[i].pressed(m->pos()))
            pressed_point=i;
}

void Window::mouseMoveEvent(QMouseEvent* m){
    if( (m->pos().x()>=0) && (m->pos().x()<=width())
     && (m->pos().y()>=0) && (m->pos().y()<=height()))
    points[pressed_point].move(m->pos());
    update();
}

void Window::mouseReleaseEvent(QMouseEvent* m){
    pressed_point=-1;
}

QPointF Window::Bezie(double t){
    return points[0].pos()*(1-t)*(1-t)*(1-t)*(1-t)
           + 4*points[1].pos()*t*(1-t)*(1-t)*(1-t)
           + 6*points[2].pos()*t*t*(1-t)*(1-t)
           + 4*points[3].pos()*t*t*t*(1-t)
           + points[4].pos()*t*t*t*t;
}

void Window::drawBezie(QPainter& pntr, unsigned int n){
    for(int i=1; i<=n; ++i){
        pntr.drawLine(Bezie(((double)i-1)/n), Bezie((double)i/n));
    }
}

void Window::paintEvent(QPaintEvent*){
    unsigned int n = aprox -> value();

    for(point& p:points){
        QPointF po((p.pos().x() - xpos)/scale*std::min(width(), height()) + (width() - scale)/2,
                  (p.pos().y() -ypos)/scale*std::min(width(), height()) + (height() - scale)/2);

        p.move(po);
    }
    xpos=(width() - scale)/2;
    ypos=(height() - scale)/2;
    scale=std::min(width(), height());

    QPainter pntr(this);
    pntr.setPen(QPen(Qt::black, 1, Qt::DashLine));
    for(int i=0; i<points.size()-1; ++i)
        pntr.drawLine(points[i].pos(), points[i+1].pos());

    pntr.setBrush(Qt::Dense5Pattern);
    pntr.setPen(QPen(Qt::black, 1));
    for(point p:points)
        p.draw(pntr);
    pntr.setBrush(Qt::NoBrush);
    pntr.setPen(QPen(Qt::red, 3));
    drawBezie(pntr, n);
}


Window::~Window(){
}
