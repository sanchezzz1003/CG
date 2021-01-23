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
    QVector<QVector3D>* arc_prev = new QVector<QVector3D>;
    QVector<QVector3D>* arc_this = new QVector<QVector3D>;
    QVector<QVector3D>* arc_first = new QVector<QVector3D>;
    bool save_first = false;
    float ring_length = 2.0f * M_PI;
    float step = ring_length / precision;
    double lstep = length/precision;
    double rstep = radius/precision;
    QColor color = (getMode() == FRAME ? getFrameColor() : getMaterialColor());
    float red = color.red();
    float blue = color.blue();
    float green = color.green();
    float cosGma;
    float sinGma;
    QVector3D cur_point(0.0f, 0.0f, 0.0f);
    for(float gma = 0.0f; gma <= 2.0f * M_PI;gma += step){
        int i = 0 ;
        cosGma = cosf(gma);
        sinGma = sinf(gma);
        for(float phi = -length/2.0f;phi<= length/2.0f; phi += lstep){

            cur_point.setX(radius * cosGma);
            cur_point.setY(phi);
            cur_point.setZ(radius * sinGma);
            if(abs(phi-length/2) < lstep){
                cur_point.setX(radius * cosGma);
                cur_point.setY(length/2);
                cur_point.setZ(radius * sinGma);
                arc_this->push_back(cur_point);
            }
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
            if(abs(rad-radius) < rstep){
                cur_point.setX(radius * cosGma);
                cur_point.setY(-length/2);
                cur_point.setZ(radius * sinGma);
                arc_this->push_back(cur_point);
            }
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
            if(abs(rad-radius) < rstep){
                cur_point.setX(radius * cosGma);
                cur_point.setY(length/2);
                cur_point.setZ(radius * sinGma);
                arc_this->push_back(cur_point);
            }
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
        }
    }

    delete arc_prev;
    delete arc_this;
}
