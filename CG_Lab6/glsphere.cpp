#include "glsphere.h"
#include <QVector3D>
GLSphere::GLSphere(float r, float p) :
    radius(r),
    precision(p)
{

}

float GLSphere::getRadius() const{
    return radius;
}
void GLSphere::setRadius(float r){
    radius = r;
}
float GLSphere::getPrecision() const{
    return precision;
}
void GLSphere::setPrecision(float p){
    precision = p;
}

void GLSphere::paint(){
    QVector<QVector3D>* arc_prev = new QVector<QVector3D>;
    QVector<QVector3D>* arc_this = new QVector<QVector3D>;
    QVector<QVector3D>* arc_first = new QVector<QVector3D>;
    bool save_first = false;
    float ring_length = 2.0f * M_PI;
    float step = ring_length / precision;
    QColor color = (getMode() == FRAME ? getFrameColor() : getMaterialColor());
    float red = color.red();
    float blue = color.blue();
    float green = color.green();
    float cosGma;
    float sinGma;
    float cosPhi;
    float sinPhi;
    QVector3D cur_point(0.0f, 0.0f, 0.0f);
    for(float gma = 0.0f; gma <= 2.0f * M_PI;gma += step){
        int i = 0 ;
        cosGma = cosf(gma);
        sinGma = sinf(gma);
        for(float phi = -M_PI_2;phi< M_PI_2; phi += step){
            cosPhi = cosf(phi);
            sinPhi = sin(phi);
            cur_point.setX(radius * cosGma * cosPhi);
            cur_point.setY(radius * sinPhi);
            cur_point.setZ(radius * sinGma * cosPhi);
            if(arc_prev->size()){
                if(i < (arc_prev->size() - 1) && i > 0){
                    glBegin(GL_POLYGON);
                    glColor3f(red, green, blue);
                    glVertex3f(  cur_point.x(),cur_point.y(), cur_point.z() );
                    glVertex3f(  arc_prev->at(i).x(),arc_prev->at(i).y(),arc_prev->at(i).z());
                    glVertex3f(  arc_prev->at(i+1).x(),arc_prev->at(i+1).y(),arc_prev->at(i+1).z());
                    glEnd();
                    glBegin(GL_POLYGON);
                    glColor3f(red, green, blue);
                    glVertex3f(  arc_this->at(i-1).x(),arc_this->at(i-1).y(), arc_this->at(i-1).z() );
                    glVertex3f(  arc_prev->at(i).x(),arc_prev->at(i).y(),arc_prev->at(i).z());
                    glVertex3f(  cur_point.x(),cur_point.y(),cur_point.z());
                    glEnd();
                 //polygons->push_back(new Polygon3D(cur_point,arc_prev->at(i+1),arc_prev->at(i)));
                 //polygons->push_back(new Polygon3D(arc_this->at(i-1),cur_point,arc_prev->at(i)));
                }
            }
            arc_this->push_back(cur_point);
            ++i;
        }
        float phi = M_PI_2;
        float cosPhi = cosf(phi);
        float sinPhi = sin(phi);
        cur_point.setX(radius * cosGma * cosPhi);
        cur_point.setY(radius * sinPhi);
        cur_point.setZ(radius * sinGma * cosPhi);
        //if(arc_prev->size()){
          //  polygons->push_back(new Polygon3D(cur_point,arc_prev->at((i+1 == arc_prev->size() ? 0 : i+1)),arc_prev->at(i)));
        //}
        arc_this->push_back(cur_point);
        if(!save_first){
            save_first = true;
            *arc_first = *arc_this;
        }
        qSwap(arc_prev, arc_this);
        arc_this->clear();
    }
    for(int i = 0;i<arc_first->size()-1;++i){
        if(i < arc_prev->size() - 1 && i > 0){glBegin(getMode());
            glBegin(GL_POLYGON);
            glColor3f(red, green, blue);
            glVertex3f(  arc_first->at(i).x(),arc_first->at(i).y(), arc_first->at(i).z() );
            glVertex3f(  arc_prev->at(i).x(),arc_prev->at(i).y(),arc_prev->at(i).z());
            glVertex3f(  arc_prev->at(i+1).x(),arc_prev->at(i+1).y(),arc_prev->at(i+1).z());
            glEnd();
            glBegin(GL_POLYGON);
            glColor3f(red, green, blue);
            glVertex3f(  arc_first->at(i-1).x(),arc_first->at(i-1).y(), arc_first->at(i-1).z() );
            glVertex3f(  arc_prev->at(i).x(),arc_prev->at(i).y(),arc_prev->at(i).z());
            glVertex3f(  arc_first->at(i).x(),arc_first->at(i).y(),arc_first->at(i).z());
            glEnd();
            //polygons->push_back(new Polygon3D(arc_first->at(i),arc_prev->at(i+1),arc_prev->at(i)));
            //polygons->push_back(new Polygon3D(arc_first->at(i-1),arc_first->at(i),arc_prev->at(i)));
        }
    }
    delete arc_prev;
    delete arc_this;
}
float f4(int t, float step ){
    float r = t;
    r*=2;
    r*= M_PI/180;
    r = 0.8 + sinf(step * 18 + r)/10;
    return r;
}

void GLSphere::animate(int t){
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
    QVector3D up(0.0,0.0,f4(t, 0));
    QVector3D down(0.0,0.0,-f4(t, ring_length/2));
    for(float phi = 0; phi < 2*M_PI;phi += step){
        sinPhi = sinf(phi);
        cosPhi = cosf(phi);
        for(float gma = M_PI - step; gma > 0; gma -= step){
            sinGma = sinf(gma);
            cosGma = cosf(gma);
            float tempr = f4(t, gma * radius);
            cur_point.setX(tempr * sinGma * cosPhi);
            cur_point.setY(tempr * sinGma * sinPhi);
            cur_point.setZ(tempr * cosGma);
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
