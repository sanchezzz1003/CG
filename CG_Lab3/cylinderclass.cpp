#include "cylinderclass.h"
#include "polygon3d.h"
#include <QtMath>

CylinderClass::CylinderClass(float r, float p, double l) :
    precision(p), radius(r), length(l)
{

}

void CylinderClass::setPrecision(float p){
    if(p != precision){
        precision = p;
        isChanged = true;
    }
}
void CylinderClass::setRadius(float r){
    if(r != radius){
        r = radius;
        isChanged = true;
    }
}
void CylinderClass::setLength(float l){
    if(l != length){
        l = length;
        isChanged = true;
    }
}
float CylinderClass::getPrecision() const{
    return precision;
}
float CylinderClass::getRadius() const{
    return radius;
}
float CylinderClass::getLength() const{
    return length;
}
//*
void CylinderClass::calculatePolygons(){
    QVector<QVector4D>* arc_prev = new QVector<QVector4D>;
    QVector<QVector4D>* arc_this = new QVector<QVector4D>;
    QVector<QVector4D>* arc_first = new QVector<QVector4D>;
    bool save_first = false;
    float ring_length = 2.0f * M_PI;
    float step = ring_length / precision;
    double lstep = length/precision;
    double rstep = radius/precision;

    float cosGma;
    float sinGma;
    QVector4D cur_point(0.0f, 0.0f, 0.0f, 1.0f);
    for(float gma = 0.0f; gma <= 2.0f * M_PI;gma += step){
        int i = 0 ;
        cosGma = cosf(gma);
        sinGma = sinf(gma);


        for(float phi = -length/2.0f;phi < length/2.0f+lstep; phi += lstep){

            cur_point.setX(radius * cosGma);
            cur_point.setY(phi);
            cur_point.setZ(radius * sinGma);
            if(arc_prev->size()){
                if(i < (arc_prev->size() - 1) && i > 0){
                 addPolygon(new Polygon3D(cur_point,arc_prev->at(i+1),arc_prev->at(i)));
                 addPolygon(new Polygon3D(arc_this->at(i-1),cur_point,arc_prev->at(i)));
                }
            }
            arc_this->push_back(cur_point);
            ++i;
        }

        cur_point.setX(radius * cosGma);
        cur_point.setY(length/2.0f);
        cur_point.setZ(radius * sinGma);
        arc_this->push_back(cur_point);

        cur_point.setX(radius * cosGma);
        cur_point.setY(-length/2.0f);
        cur_point.setZ(radius * sinGma);
        arc_this->push_front(cur_point);

        if(!save_first){
            save_first = true;
            *arc_first = *arc_this;
        }
        qSwap(arc_prev, arc_this);
        arc_this->clear();


    }
    for(int i = 0;i<arc_first->size()-1;++i){
        if(i <= arc_prev->size() - 1 && i > 0){
            addPolygon(new Polygon3D(arc_first->at(i),arc_prev->at(i+1),arc_prev->at(i)));
            addPolygon(new Polygon3D(arc_first->at(i-1),arc_first->at(i),arc_prev->at(i)));
        }
    }
    arc_prev->clear();
    arc_first->clear();
    save_first = false;

/*----*/

    for (float gma = 0.0f; gma <= 2.0f * M_PI;gma += step){
        int i = 0;
        cosGma = cosf(gma);
        sinGma = sinf(gma);
        for(float rad = 0.0f;rad <= radius; rad += rstep){

            cur_point.setX(rad * cosGma);
            cur_point.setY(-length/2.0f);
            cur_point.setZ(rad * sinGma);
            if(arc_prev->size()){
                if(i < (arc_prev->size() - 1) && i > 0){
                 addPolygon(new Polygon3D(cur_point,arc_prev->at(i+1),arc_prev->at(i)));
                 addPolygon(new Polygon3D(arc_this->at(i-1),cur_point,arc_prev->at(i)));
                }
            }
            arc_this->push_back(cur_point);

            ++i;
        }

        cur_point.setX(radius * cosGma);
        cur_point.setY(-length/2);
        cur_point.setZ(radius * sinGma);
        arc_this->push_back(cur_point);

        if(!save_first){
            save_first = true;
            *arc_first = *arc_this;
        }
        qSwap(arc_prev, arc_this);
        arc_this->clear();
    }
    for(int i = 0;i<arc_first->size()-1;++i){
        if(i <= arc_prev->size() - 1 && i > 0){
            addPolygon(new Polygon3D(arc_first->at(i),arc_prev->at(i+1),arc_prev->at(i)));
            addPolygon(new Polygon3D(arc_first->at(i-1),arc_first->at(i),arc_prev->at(i)));
        }
    }
    arc_prev->clear();
    arc_first->clear();
    save_first = false;

/*----*/

    for (float gma = 2.0f * M_PI; gma >= 0;gma -= step){
        int i = 0;
        cosGma = cosf(gma);
        sinGma = sinf(gma);
        for(float rad = 0.0f;rad <= radius; rad += rstep){

            cur_point.setX(rad * cosGma);
            cur_point.setY(length/2.0f);
            cur_point.setZ(rad * sinGma);
            if(arc_prev->size()){
                if(i < (arc_prev->size() - 1) && i > 0){
                 addPolygon(new Polygon3D(cur_point,arc_prev->at(i+1),arc_prev->at(i)));
                 addPolygon(new Polygon3D(arc_this->at(i-1),cur_point,arc_prev->at(i)));
                }
            }
            arc_this->push_back(cur_point);

            ++i;
        }

        cur_point.setX(radius * cosGma);
        cur_point.setY(length/2);
        cur_point.setZ(radius * sinGma);
        arc_this->push_back(cur_point);

        if(!save_first){
            save_first = true;
            *arc_first = *arc_this;
        }
        qSwap(arc_prev, arc_this);
        arc_this->clear();
    }
    for(int i = 0;i<arc_first->size()-1;++i){
        if(i <= arc_prev->size() - 1 && i > 0){
            addPolygon(new Polygon3D(arc_first->at(i),arc_prev->at(i+1),arc_prev->at(i)));
            addPolygon(new Polygon3D(arc_first->at(i-1),arc_first->at(i),arc_prev->at(i)));
        }
    }

    delete arc_prev;
    delete arc_this;
}

