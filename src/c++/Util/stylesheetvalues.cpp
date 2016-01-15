#include "stylesheetvalues.h"

const QString StyleSheetValues::BUTTON_STYLE="QPushButton {width:1200px;height:40px;color: white;font-weight: 700;text-decoration: none;padding: .5em 2em;outline: none;border: 2px solid;border-radius: 1px; background: rgb(45,45,45)}  QPushButton:hover { border-color: rgb(255,255,255)}";

const QString StyleSheetValues::BUTTON_ACTIVATED_STYLE="QPushButton {width:1200px;height:40px;color: white;font-weight: 700;text-decoration: none;padding: .5em 2em;outline: none;border: 2px solid;border-radius: 1px; background: rgb(45,45,45);border-color: rgb(255,255,255)}";

const QString StyleSheetValues::RESISTOR_BUTTON_HOVER_STYLE = "QPushButton:hover {background: rgb(240,240,240); background-image: url(C:/Users/amylniko/Documents/env/er/VizPROC-master/resource/resistor_button_hover.png);} ";

const QString StyleSheetValues::RESISTOR_BUTTON_STYLE = StyleSheetValues::RESISTOR_BUTTON_HOVER_STYLE+"QPushButton {marginwidth:4px;height:4px;color: white;font-weight: 700;text-decoration: none;padding: 0;outline: none;border: none ; background: rgb(45,45,45);background-image: url(C:/Users/amylniko/Documents/env/er/VizPROC-master/resource/resistor_button.png);}";

StyleSheetValues::StyleSheetValues(QObject *parent) : QObject(parent)
{

}

StyleSheetValues::~StyleSheetValues()
{

}

