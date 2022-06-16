#include "ChangeObjectPropertyCommandDesc.h"

namespace xStudio
{
    ChangeObjectPropertyCommandDesc::ChangeObjectPropertyCommandDesc(MObject*                 target,
                                                                     const QString&           propertyName,
                                                                     const QVariant&          newValue,
                                                                     const QVariant&          oldValue,
                                                                     const CommandDescOption& option)
        : CommandDesc(option)
        , _ptarget(target)
        , _propertyName(propertyName)
        , _newValue(newValue)
        , _oldValue(oldValue)
    {
    }

    ChangeObjectPropertyCommandDesc::ChangeObjectPropertyCommandDesc() { }

    ChangeObjectPropertyCommandDesc::~ChangeObjectPropertyCommandDesc() { }

    CommandDesc* ChangeObjectPropertyCommandDesc::CreateSameTypeCommandDesc() const
    {
        return (new ChangeObjectPropertyCommandDesc());
    }

    bool ChangeObjectPropertyCommandDesc::CombinedWith(CommandDesc* lastCmdDesc)
    {
        if (lastCmdDesc->GetCommandName() == GetCommandName() && lastCmdDesc->GetCombinedable())
        {
            auto lastCommandDesc = static_cast<ChangeObjectPropertyCommandDesc*>(lastCmdDesc);
            if (lastCommandDesc->_ptarget == _ptarget && lastCommandDesc->_propertyName == _propertyName)
            {
                _oldValue = lastCommandDesc->_oldValue;
                return true;
            }
        }
        return false;
    }

    bool ChangeObjectPropertyCommandDesc::HasModifiedTarget(MObject* target) const
    {
        return (target == _ptarget || (_ptarget && _ptarget->IsChildOf(target)));
    }

    ChangeObjectListPropertyCommandDesc::ChangeObjectListPropertyCommandDesc(MObject*                 target,
                                                                             const QString&           propertyName,
                                                                             ListOperateEnum          operate,
                                                                             int                      index,
                                                                             int                      cnt,
                                                                             const QVariant&          newValue,
                                                                             const QVariant&          oldValue,
                                                                             const CommandDescOption& option)
        : CommandDesc(option)
        , _ptarget(target)
        , _propertyName(propertyName)
        , _operate(operate)
        , _index(index)
        , _cnt(cnt)
        , _newValue(newValue)
        , _oldValue(oldValue)
    {
    }

    CommandDesc* ChangeObjectListPropertyCommandDesc::CreateSameTypeCommandDesc() const
    {
        return (new ChangeObjectListPropertyCommandDesc());
    }

    bool ChangeObjectListPropertyCommandDesc::HasModifiedTarget(MObject* target) const
    {
        if (target == _ptarget || (_ptarget && _ptarget->IsChildOf(target)))
            return true;

        auto pobject = static_cast<MObject*>(_newValue.value<void*>());
        if (pobject == target || (target && target->IsChildOf(pobject)))
            return true;

        pobject = static_cast<MObject*>(_oldValue.value<void*>());
        if (pobject == target || (target && target->IsChildOf(pobject)))
            return true;

        return false;
    }
} // namespace xStudio