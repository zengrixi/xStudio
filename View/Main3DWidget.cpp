#include "Main3DWidget.h"

Main3DWidget::Main3DWidget(QWidget* parent)
    : Base3DViewerWidget(parent)
{
}

Main3DWidget::~Main3DWidget()
{
}

osg::Group* Main3DWidget::GetRootNode() const
{
    return _root;
}

void Main3DWidget::AddNodeToRoot(const osg::ref_ptr<osg::Node>& node)
{
    _root->addChild(node);
}