#include "glcylinder.h"

GLCylinder::GLCylinder(float r, float p, float l):
    radius(r),
    precision(p),
    length(l)
{

}

float GLCylinder::getRadius() const{
    return radius;
}
void GLCylinder::setRadius(float r){
    radius = r;
}
float GLCylinder::getPrecision() const{
    return precision;
}
void GLCylinder::setPrecision(float p){
    precision = p;
}
float GLCylinder::getLength() const{
    return length;
}
void GLCylinder::setLength(float l){
    length = l;
}

void GLCylinder::paint(){
    QVector<QVector3D> arc_this;
    QVector<QVector3D> arc_prev;
    QVector<QVector3D> arc_first;
    float ring_length = 2.0f * M_PI;
    float step = ring_length / precision;
    double lstep = length/precision;
    double rstep = radius/precision;
    float cosPhi;
    float sinPhi;
    QVector3D cur_point(0.0f, 0.0f, 0.0f);
    for(float phi = 0; phi < 2*M_PI;phi += step){
        sinPhi = sinf(phi);
        cosPhi = cosf(phi);
        for(float gma = length/2; gma >= -length/2; gma -= lstep){
            cur_point.setX(radius * cosPhi);
            cur_point.setY(radius * sinPhi);
            cur_point.setZ(gma);
            arc_this.push_back(cur_point);
            if(gma+length/2 < lstep){
                cur_point.setX(radius * cosPhi);
                cur_point.setY(radius * sinPhi);
                cur_point.setZ(-length/2);
                arc_this.push_back(cur_point);
            }
        }
        if(arc_prev.size() != 0){
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
    for(int i = 0;i<arc_prev.size()-1;++i){
        addPolygon(arc_first[i], arc_prev[i], arc_prev[i+1]);
        addPolygon(arc_first[i+1], arc_first[i], arc_prev[i+1]);
    }
    arc_first.clear();
    arc_prev.clear();
    arc_this.clear();

    for(float phi = 2*M_PI; phi > 0;phi -= step){
        sinPhi = sinf(phi);
        cosPhi = cosf(phi);
        for(float gma = radius; gma >= 0; gma -= rstep){
            cur_point.setX(gma * cosPhi);
            cur_point.setY(gma * sinPhi);
            cur_point.setZ(length/2);
            arc_this.push_back(cur_point);
            if (gma < rstep){
                cur_point.setX(0);
                cur_point.setY(0);
                cur_point.setZ(length/2);
                arc_this.push_back(cur_point);
            }
        }
        if(arc_prev.size() != 0){
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
    for(int i = 0;i<arc_prev.size()-1;++i){
        addPolygon(arc_first[i], arc_prev[i], arc_prev[i+1]);
        addPolygon(arc_first[i+1], arc_first[i], arc_prev[i+1]);
    }
    arc_first.clear();
    arc_prev.clear();
    arc_this.clear();

    for(float phi = 0; phi < 2*M_PI;phi += step){
        sinPhi = sinf(phi);
        cosPhi = cosf(phi);
        for(float gma = radius; gma >= 0; gma -= rstep){
            cur_point.setX(gma * cosPhi);
            cur_point.setY(gma * sinPhi);
            cur_point.setZ(-length/2);
            arc_this.push_back(cur_point);
            if (gma < rstep){
                cur_point.setX(0);
                cur_point.setY(0);
                cur_point.setZ(-length/2);
                arc_this.push_back(cur_point);
            }
        }
        if(arc_prev.size() != 0){
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
    for(int i = 0;i<arc_prev.size()-1;++i){
        addPolygon(arc_first[i], arc_prev[i], arc_prev[i+1]);
        addPolygon(arc_first[i+1], arc_first[i], arc_prev[i+1]);
    }
}

float f(int t, float step ){
    float r = t;
    r*=2;
    r*= M_PI/180;
    r = 0.8 + cosf(step * 18 + r)/10;
    return r;
}

void GLCylinder::animate(int t){
    QVector<QVector3D> arc_this;
    QVector<QVector3D> arc_prev;
    QVector<QVector3D> arc_first;
    float ring_length = 2.0f * M_PI;
    float step = ring_length / precision;
    double lstep = length/precision;
    double rstep = radius/precision;

    float cosPhi;
    float sinPhi;
    QVector3D cur_point(0.0f, 0.0f, 0.0f);
    for(float phi = 0; phi < 2*M_PI;phi += step){
        sinPhi = sinf(phi);
        cosPhi = cosf(phi);
        for(float gma = length/2; gma >= -length/2; gma -= lstep){

            float tempr = f(t, gma*radius);
            cur_point.setX(tempr * cosPhi);
            cur_point.setY(tempr * sinPhi);
            cur_point.setZ(gma);
            arc_this.push_back(cur_point);
            if(gma+length/2 < lstep){
                cur_point.setX(tempr * cosPhi);
                cur_point.setY(tempr * sinPhi);
                cur_point.setZ(-length/2);
                arc_this.push_back(cur_point);
            }
        }
        if(arc_prev.size() != 0){
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
    for(int i = 0;i<arc_prev.size()-1;++i){
        addPolygon(arc_first[i], arc_prev[i], arc_prev[i+1]);
        addPolygon(arc_first[i+1], arc_first[i], arc_prev[i+1]);
    }
    arc_first.clear();
    arc_prev.clear();
    arc_this.clear();

    for(float phi = 2*M_PI; phi > 0;phi -= step){
        sinPhi = sinf(phi);
        cosPhi = cosf(phi);
        for(float gma = f(t,radius); gma >= 0; gma -= rstep){

            cur_point.setX(gma * cosPhi);
            cur_point.setY(gma * sinPhi);
            cur_point.setZ(length/2);
            arc_this.push_back(cur_point);
            if (gma < rstep){
                cur_point.setX(0);
                cur_point.setY(0);
                cur_point.setZ(length/2);
                arc_this.push_back(cur_point);
            }
        }
        if(arc_prev.size() != 0){
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
    for(int i = 0;i<arc_prev.size()-1;++i){
        addPolygon(arc_first[i], arc_prev[i], arc_prev[i+1]);
        addPolygon(arc_first[i+1], arc_first[i], arc_prev[i+1]);
    }
    arc_first.clear();
    arc_prev.clear();
    arc_this.clear();

    for(float phi = 0; phi < 2*M_PI;phi += step){
        sinPhi = sinf(phi);
        cosPhi = cosf(phi);
        for(float gma = f(t,radius); gma >= 0; gma -= rstep){

            cur_point.setX(gma * cosPhi);
            cur_point.setY(gma * sinPhi);
            cur_point.setZ(-length/2);
            arc_this.push_back(cur_point);
            if (gma < rstep){
                cur_point.setX(0);
                cur_point.setY(0);
                cur_point.setZ(-length/2);
                arc_this.push_back(cur_point);
            }
        }
        if(arc_prev.size() != 0){
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
    for(int i = 0;i<arc_prev.size()-1;++i){
        addPolygon(arc_first[i], arc_prev[i], arc_prev[i+1]);
        addPolygon(arc_first[i+1], arc_first[i], arc_prev[i+1]);
    }
}
