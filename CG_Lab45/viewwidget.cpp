#include "viewwidget.h"
#include "glcuboid.h"
#include <QLabel>

ViewWidget::ViewWidget()
{
    glw->Engine.addFigure(sph);
    hLayout->addLayout(vLayoutView,1);
        vLayoutView->addLayout(hLayoutFigures);
            hLayoutFigures->setAlignment(Qt::AlignLeft);
                hLayoutFigures->addWidget(viewCylinder);
        vLayoutView->addWidget(glw, 1);
    hLayout->addLayout(vLayout);
        vLayout->addWidget(isIzomteric);
        vLayout->addWidget(isHidingBack);
        vLayout->addWidget(isLigthing);
    hLayout->addWidget(sliderPrecision);
        vLayout->addWidget(new QLabel("Rotations"));
        vLayout->addLayout(hLayoutRotations);
            hLayoutRotations->addWidget(sliderRotX);
            hLayoutRotations->addWidget(sliderRotY);
            hLayoutRotations->addWidget(sliderRotZ);
        vLayout->addWidget(ligthSettings);


    viewCylinder->setText("Cylinder");
    isIzomteric->setText("Izomteric");
    isHidingBack->setText("Hide back");
    isLigthing->setText("Enable Light");
    ligthSettings->setText("Light settings");

    sliderPrecision->setRange(3, 200);
    sliderRotX->setRange(0,MAX_VALUE_SLIDER);
    sliderRotY->setRange(0,MAX_VALUE_SLIDER);
    sliderRotZ->setRange(0,MAX_VALUE_SLIDER);

    sliderPrecision->setSingleStep(1);
    sliderPrecision->setValue(10);
    sliderRotX->setSingleStep(1);
    sliderRotY->setSingleStep(1);
    sliderRotZ->setSingleStep(1);

    sliderRotX->setInvertedAppearance(true);
    sliderRotY->setInvertedAppearance(true);
    sliderRotZ->setInvertedAppearance(true);

    viewCylinder->setChecked(true);
    viewCylinder->setEnabled(false);
    sliderPrecision->setEnabled(true);
    ligthSettings->setEnabled(true);

    QObject::connect(sliderRotX, SIGNAL(valueChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(sliderRotY, SIGNAL(valueChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(sliderRotZ, SIGNAL(valueChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(sliderPrecision, SIGNAL(valueChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(isHidingBack, SIGNAL(stateChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(isLigthing, SIGNAL(stateChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(isIzomteric, SIGNAL(stateChanged(int)),
                     this, SLOT(configChanged(int)));

    QObject::connect(viewCylinder, SIGNAL(stateChanged(int)),
                     this, SLOT(figureSwap(int)));
    QObject::connect(ligthSettings, SIGNAL(clicked()),
                     this, SLOT(showLightSettings()));
    QObject::connect(lsw->sliderPositionX, SIGNAL(valueChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(lsw->sliderPositionY, SIGNAL(valueChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(lsw->sliderPositionZ, SIGNAL(valueChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(lsw, SIGNAL(lightColorChanged()),
                     this, SLOT(configChanged()));

    sph->setPrecision(sliderPrecision->value());
}

float f1(int v){
    return (float)v*360/MAX_VALUE_SLIDER;
}
float f2(int v){
    return (float)v;
}
float f3(int v){
    return (float) v/ (float)MAX_VALUE_SLIDER_LW;
}
void ViewWidget::configChanged(){
    glw->Engine.setRotation(f1(sliderRotX->value()),
                             f1(sliderRotY->value()),
                             f1(sliderRotZ->value()));
    glw->Engine.setHidingBack(isHidingBack->isChecked());
    sph->setPrecision(sliderPrecision->value());
    isIzomteric->isChecked() ? glw->Engine.setIzomtericProjection() : glw->Engine.setOrthoProjection();
    ligthSettings->setEnabled(isLigthing->isChecked());

    if(isLigthing->isChecked()){
        cub->setMode(MATERIAL);
        sph->setMode(MATERIAL);
        glw->Engine.setLightEnabled(true);
        isHidingBack->setEnabled(false);
        isHidingBack->setChecked(true);
    } else{
        cub->setMode(FRAME);
        sph->setMode(FRAME);
        glw->Engine.setLightEnabled(false);
        isHidingBack->setEnabled(true);
    }
    glw->Engine.light.direction = QVector3D(f3(lsw->sliderPositionX->value()),
                                            f3(lsw->sliderPositionY->value()),
                                            f3(lsw->sliderPositionZ->value()));
    glw->Engine.light.diffuse = lsw->diffuse;
    glw->updateGL();
}
void ViewWidget::configChanged(int){
    configChanged();
}
ViewWidget::~ViewWidget(){
    delete cub;
}

void ViewWidget::figureSwap(){
        viewCylinder->setChecked(true);

        viewCylinder->setEnabled(false);
        sliderPrecision->setEnabled(true);
        glw->Engine.deleteFigures();
        glw->Engine.addFigure(sph);

}
void ViewWidget::figureSwap(int){
    figureSwap();
}

void ViewWidget::showLightSettings(){
    lsw->show();
}
