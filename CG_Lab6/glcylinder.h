#ifndef GLCYLINDER_H
#define GLCYLINDER_H

#include "glabstractpainting.h"
class GLCylinder : public GLAbstractPainting
{
    float radius, precision, length;
public:
    GLCylinder(float r, float p, float l);
    float getRadius() const;
    void setRadius(float r);
    float getPrecision() const;
    void setPrecision(float p);
    float getLength() const;
    void setLength(float l);
    void paint() override;
    void animate(int t) override;
};

#endif // GLCYLINDER_H
