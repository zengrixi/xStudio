#include "MainWindow.h"

#include <QAction>
#include <QFileDialog>

#include <osg/MatrixTransform>
#include <osg/Node>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

namespace xStudio
{
    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent)
    {
        ui.setupUi(this);

        auto w = new QWidget(this);
        setCentralWidget(w);

        auto gridLayout = new QGridLayout(this);

        _mainScene = new Main3DWidget(this);
        gridLayout->addWidget(_mainScene, 0, 0, 1, 1);

        _propertyBrowser = new PropertyBrowserWidget(this);
        gridLayout->addWidget(_propertyBrowser, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 4);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);

        w->setLayout(gridLayout);
        showMaximized();

        connect(_mainScene,
                &Main3DWidget::SelectEntity,
                [&](MEntity* entity)
                {
                    _propertyBrowser->SetObject(entity);
                });

        CommandManager::GetSingleton().Initialzie();
    }
} // namespace xStudio