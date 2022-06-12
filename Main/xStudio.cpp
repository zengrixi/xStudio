#include "xStudio.h"

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/MatrixTransform>

#include <View/Main3DWidget.h>

xStudio::xStudio(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	auto scene = new Main3DWidget(this);
    setCentralWidget(scene);

	auto cow = osgDB::readNodeFile("./Resources/Data/cow.osg");

	auto trans = new osg::MatrixTransform();
	trans->addChild(cow);
	trans->setMatrix(osg::Matrix::translate(0, 0, 10));

	auto scale = new osg::MatrixTransform();
	scale->addChild(cow);
	scale->setMatrix(osg::Matrix::scale(0.5, 0.5, 0.5) * osg::Matrix::translate(0, 0, -10));

	auto rotate = new osg::MatrixTransform();
	rotate->addChild(cow);
	rotate->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(45.0), 1, 0, 0) * osg::Matrix::scale(0.5, 0.5, 0.5) *
					  osg::Matrix::translate(4, 0, -2));

    scene->AddNodeToRoot(trans);
    scene->AddNodeToRoot(scale);
    scene->AddNodeToRoot(rotate);
}
