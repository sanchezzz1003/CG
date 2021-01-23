#include "LOL.h"
#include <QVector3D>
LOL::LOL(float r, float p) :
    radius(r),
    precision(p)
{

}

float LOL::getRadius() const{
    return radius;
}
void LOL::setRadius(float r){
    radius = r;
}
float LOL::getPrecision() const{
    return precision;
}
void LOL::setPrecision(float p){
    precision = p;
}

void LOL::paint(){
    QVector<QVector3D> arc_this;
    QVector<QVector3D> arc_prev;
    QVector<QVector3D> arc_first;
    float ring_length = 2.0f * M_PI;
    float step = ring_length / precision;
    float cosGma;
    float sinGma;
    float cosPhi;
    float sinPhi;
    QVector3D cur_point(0.0f, 0.0f, 0.0f);
    QVector3D up(0.0,0.0,radius);
    QVector3D down(0.0,0.0,-radius);
    for(float phi = 0; phi < 2*M_PI;phi += step){
        sinPhi = sinf(phi);
        cosPhi = cosf(phi);
        for(float gma = M_PI - step; gma > 0; gma -= step){
            sinGma = sinf(gma);
            cosGma = cosf(gma);
            cur_point.setX(radius * sinGma * cosPhi);
            cur_point.setY(radius * sinGma * sinPhi);
            cur_point.setZ(radius * cosGma);
            arc_this.push_back(cur_point);
        }
        if(arc_prev.size() != 0){
            addPolygon(up, arc_this.back(), arc_prev.back());
            addPolygon(down, arc_prev[0], arc_this[0]);
            for(int i = 0;i<arc_this.size()-1;++i){
                addPolygon(arc_this[i], arc_prev[i], arc_prev[i+1]);
                addPolygon(arc_this[i+1], arc_this[i], arc_prev[i+1]);
            }
        }
        if(arc_first.size() == 0){
            arc_first = arc_this;
        }
        arc_this.swap(arc_prev);
        arc_this.clear();
    }
    addPolygon(up, arc_first.back(), arc_prev.back());
    addPolygon(down, arc_prev[0], arc_first[0]);
    for(int i = 0;i<arc_prev.size()-1;++i){
        addPolygon(arc_first[i], arc_prev[i], arc_prev[i+1]);
        addPolygon(arc_first[i+1], arc_first[i], arc_prev[i+1]);
    }
}

