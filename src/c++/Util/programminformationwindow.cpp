#include "programminformationwindow.h"
#include <QVBoxLayout>

ProgrammInformationWindow::ProgrammInformationWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->information = new QLabel("VizPROC v 0.0.1 \n\rРазработчик: Александр Мыльников");
    this->okButton = new QPushButton("Закрыть");
    mainLayout->addWidget(information);
    mainLayout->addWidget(okButton);
    QObject::connect(okButton,SIGNAL(clicked()),this,SLOT(deleteLater()));
}

ProgrammInformationWindow::~ProgrammInformationWindow()
{
    this->hide();
    delete okButton;
    delete information;
}

