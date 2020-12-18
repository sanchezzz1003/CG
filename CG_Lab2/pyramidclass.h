#ifndef PYRAMIDCLASS_H
#define PYRAMIDCLASS_H

#include"abstractpaintitng3d.h"
#include"rectpolygon3d.h"

class PyramidClass : public AbstractPaintitng3D

{
private:
    QVector4D points[5];
    float width, height;
public:
    PyramidClass(float w, float h);
    void calculatePolygons() override;
    void setWidth(float w);
    void setHeight(float h);
    void setSize(float w, float h);
};

#endif // PYRAMIDCLASS_H

