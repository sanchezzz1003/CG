#ifndef LOL_H
#define LOL_H

#include "glabstractpainting.h"
class LOL : public GLAbstractPainting
{
    float radius, precision;
public:
    LOL(float r, float p);
    float getRadius() const;
    void setRadius(float r);
    float getPrecision() const;
    void setPrecision(float p);
    void paint() override;
    void animate(int t) override;
};

#endif // LOL_H
