#include "ChangeObjectPropertyCommand.h"

#include <Cmd/CommandDesc/ChangeObjectPropertyCommandDesc.h>

#include <QMetaObject>

namespace xStudio
{
    void ChangeObjectPropertyCommand::Execute(CommandDesc* commandDesc, CommandUndoRedoState undoRedoState) const
    {
        auto cmdDesc      = static_cast<ChangeObjectPropertyCommandDesc*>(commandDesc);
        auto targetObject = cmdDesc->_ptarget;

        if (targetObject)
        {
            auto propertyFuncName = "Set" + cmdDesc->_propertyName;
            if (undoRedoState == CommandUndoRedoState_Undo)
                QMetaObject::invokeMethod(targetObject,
                                          propertyFuncName.toStdString().c_str(),
                                          Q_ARG(QVariant, cmdDesc->_oldValue));
            else
                QMetaObject::invokeMethod(targetObject,
                                          propertyFuncName.toStdString().c_str(),
                                          Q_ARG(QVariant, cmdDesc->_newValue));
        }
    }

    void ChangeObjectListPropertyCommand::Execute(CommandDesc* commandDesc, CommandUndoRedoState undoRedoState) const
    {
        auto cmdDesc  = static_cast<ChangeObjectListPropertyCommandDesc*>(commandDesc);
        auto listName = cmdDesc->_propertyName;
        auto operate  = cmdDesc->_operate;
        auto newValue = cmdDesc->_newValue;
        auto oldValue = cmdDesc->_oldValue;

        if (undoRedoState == CommandUndoRedoState_Undo)
        {
            if (operate == ListOperateEnum_Add)
                operate = ListOperateEnum_Remove;
            else if (operate == ListOperateEnum_Remove)
                operate = ListOperateEnum_Add;

            newValue = cmdDesc->_oldValue;
            oldValue = cmdDesc->_newValue;
        }

        auto ptarget            = cmdDesc->_ptarget;
        auto index              = cmdDesc->_index;
        auto cnt                = cmdDesc->_cnt;
        auto changeListFuncName = "ChangeList" + listName;

        QMetaObject::invokeMethod(ptarget,
                                  changeListFuncName.toStdString().c_str(),
                                  Q_ARG(int, operate),
                                  Q_ARG(int, index),
                                  Q_ARG(int, cnt),
                                  Q_ARG(QVariant, newValue),
                                  Q_ARG(QVariant, oldValue));
    }
} // namespace xStudio