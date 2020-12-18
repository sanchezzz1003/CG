#ifndef CYLINDERCLASS_H
#define CYLINDERCLASS_H

#include"abstractpaintitng3d.h"

class CylinderClass : public AbstractPaintitng3D
{
    float precision = 0.01;
    float radius = 10.0;
    float length = 20.0;
public:
    void setPrecision(float p);
    void setRadius(float r);
    void setLength(float l);
    float getPrecision() const;
    float getRadius() const;
    float getLength() const;
    CylinderClass(float r, float p, double l);
    void calculatePolygons() override;
};

#endif // CYLINDERCLASS_H
