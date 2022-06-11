#include <Windows.h>

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Node>

int main(int arc, char* arg[])
{
	osgViewer::Viewer viewer;
	auto root = new osg::Group();
	root->addChild(osgDB::readNodeFile("./Resources/Data/cow.osg"));
	viewer.setSceneData(root);
	viewer.realize();
	viewer.run();
	return 0;
}