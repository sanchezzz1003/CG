#include "lightsettingswidget.h"
#include <QLabel>
LightSettingsWidget::LightSettingsWidget()
{
    setMinimumSize(350, 180);
    setMaximumSize(minimumSize());
    cD->setModal(true);
    setWindowTitle("Light settings");
    cD->setCurrentColor(Qt::red);
    vLayout->addWidget(new QLabel("Position"));
    vLayout->addWidget(sliderPositionX);
    vLayout->addWidget(sliderPositionY);
    vLayout->addWidget(sliderPositionZ);

    vLayout->addLayout(hLayout);

        hLayout->addWidget(pushButtonDiffuse);


    sliderPositionX->setRange(-MAX_VALUE_SLIDER_LW, MAX_VALUE_SLIDER_LW);
    sliderPositionY->setRange(-MAX_VALUE_SLIDER_LW, MAX_VALUE_SLIDER_LW);
    sliderPositionZ->setRange(-MAX_VALUE_SLIDER_LW, MAX_VALUE_SLIDER_LW);


    sliderPositionX->setSingleStep(1);
    sliderPositionY->setSingleStep(1);
    sliderPositionZ->setSingleStep(1);


    sliderPositionX->setValue(MAX_VALUE_SLIDER_LW);
    sliderPositionY->setValue(MAX_VALUE_SLIDER_LW);
    sliderPositionZ->setValue(MAX_VALUE_SLIDER_LW);



    QObject::connect(pushButtonDiffuse, SIGNAL(released()),
                this, SLOT(getColorDialogD()));

    QObject::connect(cD, SIGNAL(colorSelected(const QColor&))
                     , this, SLOT(lightChanged(const QColor&)));
}
void LightSettingsWidget::getColorDialogA(){
    cD->show();
    isAmbient = true;
}
void LightSettingsWidget::getColorDialogS(){
    cD->show();
    isSpecular = true;
}
void LightSettingsWidget::getColorDialogD(){
    cD->show();
    isDiffuse = true;
}

void LightSettingsWidget::lightChanged(const QColor&){
    if(isDiffuse){
        diffuse = cD->selectedColor();
        isDiffuse = false;
        pushButtonDiffuse->setText("Diffuse:"+cD->selectedColor().name());
    }

    emit lightColorChanged();
}
