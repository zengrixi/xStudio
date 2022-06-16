/*****************************************************************/ /**
 * \file   MScene.h
 * \brief  场景数据
 *
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include "MEntity.h"
#include "MObject.h"

#include <Cmd/CommandManager.h>

#include <QVariant>
#include <QVector3D>

#include <osg/Group>

namespace xStudio
{
    class MScene : public MObject
    {
        Q_OBJECT

    public:
        MScene(MObject* parent);
        ~MScene();

        bool CreateScene(const QString& path);

        /**
         * 从文件中生成实体.
         *
         * \param parent
         * \param filePath          文件路径
         * \param pos
         * \param rot
         * \param scale
         * \param supportUndoRedo
         * \return
         */
        MEntity* GenerateEntityFromFile(const QString&   filePath,
                                        const QVector3D& pos,
                                        const QVector3D& rot             = QVector3D(0, 0, 0),
                                        const QVector3D& scale           = QVector3D(1.0f, 1.0f, 1.0f),
                                        bool             supportUndoRedo = true);

        osg::Group* GetScene();

    public slots:
        void ChangeListEntityList(int operate, int index, int cnt, const QVariant& newValue, const QVariant& oldValue);

    private:
        void _AddEntity(MEntity* entity, int index);
        void _RemoveEntity(MEntity* entity);

        void _AddEntityRender(osg::Node* node);
        void _RemoveEntityRender(osg::Node* node);

    private:
        QList<MEntity*>          _entityList;
        osg::ref_ptr<osg::Group> _scene;
    };
} // namespace xStudio
