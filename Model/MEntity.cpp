#include "MEntity.h"

#include <osgDB/ReadFile>
#include <osgEarth/EllipseNode>

#include <Util/TypeConvert.h>
#include <QVector3D>

namespace xStudio
{
    MEntity::MEntity(MObject* parent)
        : MObject(parent)
    {
        _transform  = new osg::MatrixTransform();
        _entityRoot = new osg::Group();
    }

    MEntity::~MEntity() { }

    osg::Group* MEntity::GetRender() { return _entityRoot.get(); }

    bool MEntity::FillWithFile(const QString& file)
    {
        auto node = osgDB::readNodeFile(file.toStdString());

        if (!node)
            return false;

        auto mt = new osg::MatrixTransform();
        mt->addChild(node);
        mt->setMatrix(osg::Matrix::rotate(-osg::PI_2, osg::X_AXIS) * osg::Matrix::scale(osg::Vec3(5, 5, 5)));

        auto autoTrans = new osg::AutoTransform();
        autoTrans->addChild(mt);
        autoTrans->getOrCreateStateSet()->setMode(GL_LIGHTING,
                                                  osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
        autoTrans->setAutoScaleToScreen(true);
        autoTrans->setMinimumScale(100.0);
        autoTrans->setMaximumScale(10000);
        autoTrans->setAutoScaleTransitionWidthRatio(0.0);

        _transform->addChild(autoTrans);

        _entityRoot->addChild(_transform);

        return true;
    }

    QString MEntity::GetName() const { return _name; }

    void MEntity::SetName(const QString& name) { _name = name; }

    QVector3D MEntity::GetPosition() const { return TypeConvert::Vec3dToQVector3D(_position); }

    void MEntity::SetPosition(const QVector3D& pos, bool emitPropertyChanged)
    {
        osg::ref_ptr<osg::EllipsoidModel> em = new osg::EllipsoidModel;
        osg::Matrixd                      mtd;
        /*em->computeLocalToWorldTransformFromLatLongHeight(osg::inDegrees(25.04),
                                                          osg::inDegrees(121.50),
                                                          100, mtd);*/
        em->computeLocalToWorldTransformFromXYZ(pos.x(), pos.y(), pos.z(), mtd);
        _transform->setMatrix(mtd);
    }

    QVector3D MEntity::GetRotate() const { return TypeConvert::Vec3dToQVector3D(_rotate); }

    void MEntity::SetRotate(const QVector3D& rot, bool emitPropertyChanged) { }

    QVector3D MEntity::GetScale() const { return TypeConvert::Vec3dToQVector3D(_scale); }

    void MEntity::SetScale(const QVector3D& scale, bool emitPropertyChanged) { }

    void MEntity::SetId(uint64_t id)
    {
        if (id != _id)
            _id = id;
    }

    uint64_t MEntity::GetId() const { return _id; }
} // namespace xStudio