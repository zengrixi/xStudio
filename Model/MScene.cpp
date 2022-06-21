#include "MScene.h"

#include <Util/CoordConvert.h>
#include <QVariant>

namespace xStudio
{
    MScene::MScene(MObject* parent)
        : MObject(parent)
    {
        _scene = new osg::Group();
    }

    MScene::~MScene() { }

    bool MScene::CreateScene(const QString& path) { return false; }

    MEntity* MScene::GenerateEntityFromFile(const QString&   filePath,
                                            const QVector3D& pos,
                                            const QVector3D& rot,
                                            const QVector3D& scale,
                                            bool             supportUndoRedo)
    {
        auto entity = new MEntity(this);
        entity->FillWithFile(filePath);
        entity->SetPosition(pos);
        entity->SetRotate(rot);
        entity->SetScale(scale);
        entity->SetId(qrand());

        auto nodeIndex = _entityList.size();

        if (supportUndoRedo)
        {
            auto newValue = QVariant::fromValue((void*) entity);
            auto oldValue = QVariant::fromValue((void*) nullptr);
            auto list     = QList<MObject*>{ entity };
            CommandManager::GetSingleton().ChangeObjectListProperty(this,
                                                                    "EntityList",
                                                                    ListOperateEnum_Add,
                                                                    nodeIndex,
                                                                    1,
                                                                    newValue,
                                                                    oldValue,
                                                                    false,
                                                                    list);
        }

        return entity;
    }

    osg::Group* MScene::GetScene() { return _scene; }

    void MScene::_AddEntity(MEntity* entity, int index)
    {
        if (_entityList.contains(entity))
            return;

        _entityList.insert(index, entity);

        AddChild(entity);

        _AddEntityRender(entity->GetRender());
    }

    void MScene::_RemoveEntity(MEntity* entity)
    {
        _entityList.removeOne(entity);

        _RemoveEntityRender(entity->GetRender());

        RemoveChild(entity);
    }

    void MScene::_AddEntityRender(osg::Node* node) { _scene->addChild(node); }

    void MScene::_RemoveEntityRender(osg::Node* node) { _scene->removeChild(node); }

    void MScene::ChangeListEntityList(int             operate,
                                      int             index,
                                      int             cnt,
                                      const QVariant& newValue,
                                      const QVariant& oldValue)
    {
        switch (operate)
        {
            case ListOperateEnum_Add:
            {
                if (1 == cnt)
                {
                    auto p_entity = static_cast<MEntity*>(newValue.value<void*>());
                    _AddEntity(p_entity, index);
                }
                else
                {
                    auto variantList = newValue.toList();
                    for (auto& variant : variantList)
                    {
                        auto p_entity = static_cast<MEntity*>(variant.value<void*>());
                        _AddEntity(p_entity, index++);
                    }
                }
            }
            break;
            case ListOperateEnum_Remove:
            {
                if (1 == cnt)
                {
                    auto p_entity = static_cast<MEntity*>(oldValue.value<void*>());
                    _RemoveEntity(p_entity);
                }
                else
                {
                    auto variantList = oldValue.toList();
                    for (auto& variant : variantList)
                    {
                        auto p_entity = static_cast<MEntity*>(variant.value<void*>());
                        _RemoveEntity(p_entity);
                    }
                }
            }
            break;
            default:
                break;
        }

        OnPropertyChanged("EntityList");
    }
} // namespace xStudio