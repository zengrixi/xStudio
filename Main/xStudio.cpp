#include "xStudio.h"

#include <QAction>
#include <QFileDialog>

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/MatrixTransform>

xStudio::xStudio(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	_mainScene = new Main3DWidget(this);
    setCentralWidget(_mainScene);

	//auto cow = osgDB::readNodeFile("./Resources/Data/cow.osg");

	//auto trans = new osg::MatrixTransform();
	//trans->addChild(cow);
	//trans->setMatrix(osg::Matrix::translate(0, 0, 10));

	//auto scale = new osg::MatrixTransform();
	//scale->addChild(cow);
	//scale->setMatrix(osg::Matrix::scale(0.5, 0.5, 0.5) * osg::Matrix::translate(0, 0, -10));

	//auto rotate = new osg::MatrixTransform();
	//rotate->addChild(cow);
	//rotate->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(45.0), 1, 0, 0) * osg::Matrix::scale(0.5, 0.5, 0.5) *
	//				  osg::Matrix::translate(4, 0, -2));

 //   _mainScene->AddNodeToRoot(trans);
 //   _mainScene->AddNodeToRoot(scale);
 //   _mainScene->AddNodeToRoot(rotate);

	connect(ui.actionOpen,
            &QAction::triggered,
            [&]
            {
                auto file = QFileDialog::getOpenFileName(this, "open file", "./Resources/", "earth file(*.earth)");
                auto res = _mainScene->OpenEarthFile(file);
            });
}
