#ifndef GLFIGUREENGINE_H
#define GLFIGUREENGINE_H
#include<QVector>
#include<QQueue>
#include<QtOpenGL>
#include "glabstractpainting.h"
#include "gllight.h"

class GLFigureEngine
{
private:
float rotateX = 0.0;
float rotateY = 0.0;
float rotateZ = 0.0;
float scale = 1.0;
bool isIzomteric = false;
bool isOrtho = true;
bool isHiddingBack = false;
bool isLightEnab = false;
bool isAnimate = false;
QVector<GLAbstractPainting*> paintings;
QQueue<GLenum> enableMods;
QQueue<GLenum> disableMods;
void applyTransform() const;
void applyLight() const;
void enable();
void disable();
void disableBooleanProj();
void prePaintSettings(GLAbstractPainting* figure);
public:
    GLFigureEngine();
    GLLight light;
    void paint();
    void addFigure(GLAbstractPainting* f);
    void deleteFigures();
    ~GLFigureEngine();
    void setRotation(float x, float y, float z);
    float getRotationX() const;
    float getRotationY() const;
    float getRotationZ() const;
    void setRotationX(float a);
    void setRotationY(float a);
    void setRotationZ(float a);
    void Enable(GLenum m);
    void Disable(GLenum m);
    void setIzomtericProjection();
    void setOrthoProjection();
    bool isIzomtericProjection();
    bool isOrthoProjection();
    bool isHidingBack() const;
    void setHidingBack(bool b);
    void setProjection(int w, int h);
    bool isLightEnabled() const;
    void setLightEnabled(bool b);
    void setAnimation(bool s);
    bool Animation();
    unsigned long long tick = 0;
};

#endif // GLFIGUREENGINE_H
