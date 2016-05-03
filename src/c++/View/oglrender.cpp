#include "oglrender.h"
#include "src/c++/Elements/resistor.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QPainter>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include <QListView>
#include <math.h>

OGLRender::OGLRender() :
    QGLWidget()
{
    setFocusPolicy(Qt::ClickFocus);
    elementList = new QComboBox();
    elementList->addItem("Резистор");
    elementList->addItem("Диод");
    elementList->addItem("ЭДС");
    elementList->addItem("Провод");
    elementList->addItem("Заземление");
    elementList->addItem("Амперметр");
    elementList->addItem("Вольтметр");

    QVBoxLayout *g = new QVBoxLayout(this);

    elemPanel = new QVBoxLayout();
    elemPanel->setAlignment(Qt::AlignRight|Qt::AlignTop);
    QHBoxLayout *resistancePanel = new QHBoxLayout();
    QHBoxLayout *powerPanel = new QHBoxLayout();
    resistanceLabel = new QLabel("Сопротивление(Ом)");
    resistanceSpinBox = new QDoubleSpinBox();

    powerLabel = new QLabel("Мощность(Вт)");
    power = new QComboBox();
    power->setView(new QListView());
    power->setStyleSheet("QComboBox QAbstractItemView::item {width:60px; color: white;font-weight: 700;text-decoration: none;user-select: none;outline: none; background: rgb(45,45,45); QListView::item:selected {coloe:white;background: rgb(85,85,85);}");
    power->addItem("0.125");
    power->addItem("0.25");
    power->addItem("0.5");
    power->addItem("1.0");

    voltagePanel = new QHBoxLayout();
    voltageLabel = new QLabel("Напряжение(Вт)");
    voltageSpinBox = new QDoubleSpinBox();
    voltageSpinBox->setDecimals(4);
    voltagePanel->addWidget(voltageLabel);
    voltagePanel->addWidget(voltageSpinBox);
    elemPanel->addLayout(voltagePanel);

    resistanceSpinBox->setStyleSheet("QSpinBox {width:60px;color: white;font-weight: 700;text-decoration: none;user-select: none;outline: none;border: 2px solid;border-radius: 1px; background: rgb(45,45,45);} QSpinBox::up-arrow {image: url(C:/Users/amylniko/Documents/env/er/VizPROC-master/resource/spinbox_upbutton.png);} QSpinBox::up-button {image: url(C:/Users/amylniko/Documents/env/er/VizPROC-master/resource/spinbox_upbutton.png);}");

    this->selectedEmf = NULL;
    this->selectedRes = NULL;

    resistancePanel->addWidget(resistanceLabel);
    resistancePanel->addWidget(resistanceSpinBox);

    powerPanel->addWidget(powerLabel);
    powerPanel->addWidget(power);

    QObject::connect(resistanceSpinBox,SIGNAL(editingFinished()),this,SLOT(editingElementFinished()));
    QObject::connect(voltageSpinBox,SIGNAL(editingFinished()),this,SLOT(editingElementFinished()));
    //QObject::connect(resistanceSpinBox,SIGNAL(valueChanged(double)),this,SLOT(valueChanged(double)));
    //QObject::connect(voltageSpinBox,SIGNAL(editingFinished()),this,SLOT(editingElementFinished()));

    elemPanel->addLayout(resistancePanel);
    elemPanel->addLayout(powerPanel);

    g->addLayout(elemPanel);

    g->setAlignment(elementList,Qt::AlignBottom);

    voltageLabel->setVisible(false);
    voltageSpinBox->setVisible(false);

    resistanceLabel->setVisible(false);
    resistanceSpinBox->setVisible(false);

    powerLabel->setVisible(false);
    power->setVisible(false);


    enableVisualisation = false;
    this->setLayout(g);
    setMouseTracking(true);
    setAutoFillBackground(false);

    this->error = false;
    this->errorText="";
    this->renderLock = false;
}

OGLRender::~OGLRender()
{

}

void OGLRender::drawGrid()
{
    glBegin(GL_LINES);
        glColor3f(20,20,20);
        glColor3f(0.9f,0.9f,0.9f);

        for(int i=0;i<this->height();i+=20) {
            glVertex3f(0,i,0.0f);
            glVertex3f(this->width(),i,0.0f);
        }

        for(int i=0;i<this->width();i+=20) {
            glVertex3f(i,0,0.0f);
            glVertex3f(i,this->height(),0.0f);
        }

        glEnd();
}

void OGLRender::hideAllPanesl()
{
    emfPanelVisible=false;
    resistorPanelVisible=false;
    voltageSpinBox->hide();
    resistanceSpinBox->hide();
    power->hide();
}

void OGLRender::initializeGL()
{
    //Установка белого фона
    qglClearColor(Qt::white);
    //Установка размера виджета
    this->resizeGL(400,400);
}

void OGLRender::openResistorPanel(Resistor *res)
{
    if(selectedEmf!=NULL) {
        QObject::disconnect(voltageSpinBox,SIGNAL(valueChanged(double)),selectedEmf,SLOT(setVoltage(double)));
        QObject::disconnect(voltageSpinBox,SIGNAL(valueChanged(double)),this,SLOT(valueChanged(double)));
    }
    if(selectedRes!=NULL) {
        QObject::disconnect(resistanceSpinBox,SIGNAL(valueChanged(double)),selectedRes,SLOT(setResistance(double)));
        QObject::disconnect(power,SIGNAL(currentTextChanged(QString)),selectedRes,SLOT(setMaxPower(QString)));
        QObject::disconnect(resistanceSpinBox,SIGNAL(valueChanged(double)),this,SLOT(valueChanged(double)));
    }

    this->selectedEmf = NULL;
    this->selectedRes = res;

    resistorPanelVisible = true;
    emfPanelVisible = false;

    voltageSpinBox->hide();

    //resistanceLabel->show();
    resistanceSpinBox->show();

    //powerLabel->show();
    power->show();
    qDebug()<<res->getResistance();
    QObject::connect(resistanceSpinBox,SIGNAL(valueChanged(double)),res,SLOT(setResistance(double)));
    QObject::connect(power,SIGNAL(currentTextChanged(QString)),res,SLOT(setMaxPower(QString)));
    QObject::connect(resistanceSpinBox,SIGNAL(valueChanged(double)),this,SLOT(valueChanged(double)));
    resistanceSpinBox->setValue(res->getResistance());
    power->setCurrentText(res->getMaxPower());
}

void OGLRender::openEmfPanel(EMF *emf)
{

    if(selectedEmf!=NULL) {
        QObject::disconnect(voltageSpinBox,SIGNAL(valueChanged(double)),selectedEmf,SLOT(setVoltage(double)));
        QObject::disconnect(voltageSpinBox,SIGNAL(valueChanged(double)),this,SLOT(valueChanged(double)));
    }
    if(selectedRes!=NULL) {
        QObject::disconnect(resistanceSpinBox,SIGNAL(valueChanged(double)),selectedRes,SLOT(setResistance(double)));
        QObject::disconnect(power,SIGNAL(currentTextChanged(QString)),selectedRes,SLOT(setMaxPower(QString)));
        QObject::disconnect(resistanceSpinBox,SIGNAL(valueChanged(double)),this,SLOT(valueChanged(double)));
    }

    resistorPanelVisible=false;
    emfPanelVisible=true;

    resistanceLabel->hide();
    resistanceSpinBox->hide();

    powerLabel->hide();
    power->hide();

    voltageSpinBox->show();

    QObject::connect(voltageSpinBox,SIGNAL(valueChanged(double)),emf,SLOT(setVoltage(double)));
    QObject::connect(voltageSpinBox,SIGNAL(valueChanged(double)),this,SLOT(valueChanged(double)));
    voltageSpinBox->setValue(emf->getVoltage());

}

void OGLRender::resizeGL(int width, int height)
{
    //Не менять!!!!! Я не до конца понимаю что и как здесь
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,width,height); //размер порта на котором будем рисовать вроде
    glOrtho(0,width,height,0,-1,1);
}

//Ивент который вызывается при нажатии на кнопку мыши
void OGLRender::mousePressEvent(QMouseEvent *event)
{
    hideAllPanesl();
    this->error = false;
    emit mouseClicked(event);
}
//Ивент который вызывается при передвижении мыши и нажатии кнопки, удобно кстати оч
void OGLRender::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event);
}
//Ивент который вызывается при отпускании клавиши мыши
void OGLRender::mouseReleaseEvent(QMouseEvent *event)
{
    this->error = false;
    emit mouseReleased(event);
}
//Ивент который вызывается при двойном клике мышью
void OGLRender::mouseDoubleClickEvent(QMouseEvent *event)
{
    this->error = false;
    emit mouseDoubleClicked(event);
}

void OGLRender::paintEvent(QPaintEvent *event)
{

    if(renderLock) {
        return;
    }

//    w->initParticles();
    QPainter painter;
    painter.begin(this);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //отрисовка сетки
    drawGrid();
    painter.setBrush(Qt::black);
    painter.setPen(Qt::black);
    if(error) {
        painter.drawText(5,13,errorText);
    }

    if(resistorPanelVisible) {
        painter.drawText(resistanceSpinBox->x()-103,resistanceSpinBox->y()+14,"Сопротивление(Ом)");
        painter.drawText(power->x()-74,power->y()+14,"Мощность(Вт)");
    } else if (emfPanelVisible) {
        painter.drawText(voltageSpinBox->x()-65,voltageSpinBox->y()+14,"Напряжение");
    }

    if(!enableVisualisation) {
    painter.beginNativePainting();
    emit paintComponents();
    emit paintMeters(&painter);
    } else {
      painter.drawText(5,13,"Режим визуализации");

      emit updateVisualisation(&painter);
    }
    painter.endNativePainting();
    painter.end();
    glFlush();
}

void OGLRender::wheelEvent(QWheelEvent *event)
{
    qDebug()<<"В будущем добавим масштабирование";
}

void OGLRender::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);
}

void OGLRender::setRenderLock()
{
    this->renderLock=true;
}

void OGLRender::unsetRenderLock()
{
    this->renderLock=false;
}

void OGLRender::editingElementFinished()
{
    if(enableVisualisation) {
        emit recalculate();
    }
}

void OGLRender::valueChanged()
{
    qDebug()<<"recalc";
    if(enableVisualisation) {
        emit recalculate();
    }
}

void OGLRender::startButtonPressed()
{
    emit startVisualisation();
}

void OGLRender::enableVisualisationSlot()
{
    qDebug()<<"Visualisation enabled";
    this->enableVisualisation = true;
}

void OGLRender::stopVisualisationSlot()
{
    qDebug()<<"Visualisation stopped";
    this->enableVisualisation=false;
    emit releaseLock();
}

void OGLRender::setError(QString errorText)
{
    this->error = true;
    this->errorText = errorText;
}

void OGLRender::elementDeleted()
{
    this->selectedEmf = NULL;
    this->selectedRes = NULL;
    resistanceLabel->hide();
    resistanceSpinBox->hide();
    power->hide();
    voltageLabel->hide();
    voltageSpinBox->hide();
    resistorPanelVisible = false;
    emfPanelVisible = false;
}
