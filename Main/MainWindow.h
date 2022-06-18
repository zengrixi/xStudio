#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include <View/Main3DWidget.h>
#include <View/PropertyBrowserWidget.h>

namespace xStudio
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = Q_NULLPTR);

    private:
        Ui::xStudioClass ui;

        Main3DWidget* _mainScene;
        PropertyBrowserWidget* _propertyBrowser;
    };
} // namespace xStudio
