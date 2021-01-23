#ifndef VIEWIDGET_H
#define VIEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QSlider>
#include <QPushButton>
#include "glwidget.h"
#include "glcuboid.h"
#include "glsphere.h"
#include "glcylinder.h"
#include "lightsettingswidget.h"
const int MAX_VALUE_SLIDER = 1000;

class ViewWidget : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* hLayout = new QHBoxLayout(this);
    QVBoxLayout* vLayout = new QVBoxLayout();
    QVBoxLayout* vLayoutView = new QVBoxLayout();
    QHBoxLayout* hLayoutFigures = new QHBoxLayout();
    QHBoxLayout* hLayoutRotations = new QHBoxLayout();
public slots:
    void configChanged(int);
    void configChanged();
    void figureSwap();
    void figureSwap(int);
    void showLightSettings();
public:
    LightSettingsWidget* lsw = new LightSettingsWidget();
    ViewWidget();
    ~ViewWidget();
    GlWidget* glw = new GlWidget;
    QCheckBox* viewCylinder = new QCheckBox();
    QCheckBox* isIzomteric = new QCheckBox();
    QCheckBox* isHidingBack = new QCheckBox();
    QCheckBox* isLigthing = new QCheckBox();
    QSlider* sliderRotX = new QSlider(Qt::Vertical);
    QSlider* sliderRotY = new QSlider(Qt::Vertical);
    QSlider* sliderRotZ = new QSlider(Qt::Vertical);
    QSlider* sliderPrecision = new QSlider(Qt::Vertical);
    QPushButton* ligthSettings = new QPushButton();
    GLCuboid* cub = new GLCuboid(1,1,1);
    GLCylinder* sph = new GLCylinder(0.7,100, 1);
};

#endif // VIEWIDGET_H
