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

        _mainScene = new Main3DWidget(this);
        setCentralWidget(_mainScene);

        CommandManager::GetSingleton().Initialzie();
    }
} // namespace xStudio