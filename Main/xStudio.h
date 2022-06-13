#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_xStudio.h"

#include <View/Main3DWidget.h>

class xStudio : public QMainWindow
{
    Q_OBJECT

public:
    xStudio(QWidget *parent = Q_NULLPTR);

private:
    Ui::xStudioClass ui;

    Main3DWidget* _mainScene;
};
