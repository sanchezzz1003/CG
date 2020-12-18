#include "widget.h"
#include "ui_widget.h"
#include <math.h>
#include <QPainter>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QWheelEvent>
#include <QString>
#include <cstdlib>
#include <QFont>

//const double pi(4 * atan(1));

#define pi 3.14159265358979323846

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    QLabel* lblRadius(new QLabel("a:", this));
    lblRadius->move(10, 10);
    radius = new QDoubleSpinBox(this);
    radius->setRange(1, 1000);
    radius->setSingleStep(1);
    radius->setValue(150);
    radius->move(10, 30);

    ui->setupUi(this);
    connect(radius, SIGNAL(valueChanged(double)),this, SLOT(redrawOnValueChange(double)));
}

double min(double a, double b){
    if (a < b) return a;
    else return b;
}

QPointF PolarToDecart(double r, double phi){
    QPointF result(cos(phi)*r, sin(phi)*r);
    return result;
}

void Widget::zoom(double change){
    if (scale > 0 || (scale == 1 && change > 0)){
        double buf = 15;
        buf *= (1+change/buf);
        scale *= buf/15;
    }
}

// изменение масштаба при прокручивании колесика
void Widget::wheelEvent(QWheelEvent* events)
{

    int numDegrees = events -> angleDelta().y() / 8;
    double numTicks = numDegrees / 15.0;

    zoom(numTicks);
    update();
}

void Widget::paintEvent(QPaintEvent*){
    const double rad(radius->value());
    const double st(0.01);
    const double end(pi + st);
    double wSize = min(width(),height())/400.0;
    double r(0);

    QPointF p1(rad, 0);

    // оси
    QPointF up(width() / 2.0, 0);
    QPointF down(width() / 2.0, height());
    QPointF left(0, height() / 2.0);
    QPointF right(width(), height() / 2.0);
    QPainter ptr(this);
    QPen mypen;
    mypen.setWidth(3);
    mypen.setBrush(Qt::blue);
    ptr.setPen(mypen);
    const QPointF center(width() / 2.0, height() / 2.0);

    //график
    for (double phi(st); phi < end; phi+= st){
        r = rad*cos(3*phi);
        QPointF p2 = PolarToDecart(r, phi);
        ptr.drawLine(center+p1*wSize*scale/15, center+p2*wSize*scale/15);
        p1 = p2;
    }

    mypen.setBrush(Qt::black);
    mypen.setWidth(2);
    ptr.setPen(mypen);
    QPointF Arrow(width() - 6, height()/2.0 + 3);
    ptr.drawLine(right, Arrow);
    Arrow.setY(height()/2.0 - 3);
    ptr.drawLine(right, Arrow);
    Arrow.setX(width()/2.0 - 3);
    Arrow.setY(0 + 6);
    ptr.drawLine(up, Arrow);
    Arrow.setX(width()/2.0 + 3);
    ptr.drawLine(up, Arrow);
    ptr.drawLine(left, right);
    ptr.drawLine(down, up);
    mypen.setWidth(1);
    ptr.setPen(mypen);

    int j = 0;
    char buffer [100];

    //масштаб на осях
    if(scale > 10){
        p1.setX(width()/2);
        p1.setY(height()/2-3);
        QPointF p2(width()/2, height()/2+3);
        for(int i = center.y(); i < center.y()+width(); i+=scale*wSize/1.5){
            ptr.drawLine(p1,p2);
            itoa(j, buffer, 10);
            if (scale > 19 && j % 100 != 0)
                ptr.drawText(p1, buffer);
            j += 10;
            p1.setX(p1.x()+scale*wSize/1.5);
            p2.setX(p2.x()+scale*wSize/1.5);
        }
        p1.setX(width()/2);
        p1.setY(height()/2-3);
        p2.setX(width()/2);
        p2.setY(height()/2+3);
        j = 0;
        for(int i = center.y(); i > center.y()-width(); i-=scale*wSize/1.5){
            ptr.drawLine(p1,p2);
            itoa(j, buffer, 10);
            if (scale > 19 && j % 100 != 0)
                ptr.drawText(p1, buffer);
            j -= 10;
            p1.setX(p1.x()-scale*wSize/1.5);
            p2.setX(p2.x()-scale*wSize/1.5);
        }
        p1.setX(width()/2-3);
        p1.setY(height()/2);
        p2.setX(width()/2+3);
        p2.setY(height()/2);
        j = 0;
        for(int i = center.x(); i < center.x()+height(); i+=scale*wSize/1.5){
            ptr.drawLine(p1,p2);
            itoa(j, buffer, 10);
            if (scale > 19 && j % 100 != 0)
                ptr.drawText(p2, buffer);
            j -= 10;
            p1.setY(p1.y()+scale*wSize/1.5);
            p2.setY(p2.y()+scale*wSize/1.5);
        }
        p1.setX(width()/2-3);
        p1.setY(height()/2);
        p2.setX(width()/2+3);
        p2.setY(height()/2);
        j = 0;
        for(int i = center.x(); i > center.y()-height(); i-=scale*wSize/1.5){
            ptr.drawLine(p1,p2);
            itoa(j, buffer, 10);
            if (scale > 19 && j % 100 != 0)
                ptr.drawText(p2, buffer);
            j += 10;
            p1.setY(p1.y()-scale*wSize/1.5);
            p2.setY(p2.y()-scale*wSize/1.5);
        }
    }
    mypen.setWidth(2);
    ptr.setPen(mypen);
    p1.setX(width()/2);
    p1.setY(height()/2-4);
    j = 0;

    ptr.setFont(QFont("Times", 10, 100, 0));
    QPointF p2(width()/2, height()/2+4);
    for(int i = center.y(); i < center.y()+width(); i+=scale*10*wSize/1.5){
        ptr.drawLine(p1,p2);
        itoa(j, buffer, 10);
        ptr.drawText(p1, buffer);
        j += 100;
        p1.setX(p1.x()+scale*10*wSize/1.5);
        p2.setX(p2.x()+scale*10*wSize/1.5);
    }
    p1.setX(width()/2);
    p1.setY(height()/2-4);
    p2.setX(width()/2);
    p2.setY(height()/2+4);
    j = 0;
    for(int i = center.y(); i > center.y()-width(); i-=scale*10*wSize/1.5){
        ptr.drawLine(p1,p2);
        itoa(j, buffer, 10);
        ptr.drawText(p1, buffer);
        j -= 100;
        p1.setX(p1.x()-scale*10*wSize/1.5);
        p2.setX(p2.x()-scale*10*wSize/1.5);
    }
    p1.setX(width()/2-4);
    p1.setY(height()/2);
    p2.setX(width()/2+4);
    p2.setY(height()/2);
    j = 0;
    for(int i = center.x(); i < center.x()+height(); i+=scale*10*wSize/1.5){
        ptr.drawLine(p1,p2);
        itoa(j, buffer, 10);
        if (j != 0) ptr.drawText(p2, buffer);
        j -= 100;
        p1.setY(p1.y()+scale*10*wSize/1.5);
        p2.setY(p2.y()+scale*10*wSize/1.5);
    }
    p1.setX(width()/2-4);
    p1.setY(height()/2);
    p2.setX(width()/2+4);
    p2.setY(height()/2);
    j = 0;
    for(int i = center.x(); i > center.y()-height(); i-=scale*10*wSize/1.5){
        ptr.drawLine(p1,p2);
        itoa(j, buffer, 10);
        if (j != 0) ptr.drawText(p2, buffer);
        j += 100;
        p1.setY(p1.y()-scale*10*wSize/1.5);
        p2.setY(p2.y()-scale*10*wSize/1.5);
    }
}

void Widget::redrawOnValueChange(double){
    update();
}

Widget::~Widget()
{
    delete ui;
}



