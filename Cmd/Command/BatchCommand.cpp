#include "BatchCommand.h"

#include <Cmd/CommandDesc/BatchCommandDesc.h>
#include <Cmd/CommandManager.h>

namespace xStudio
{
    void BatchCommand::Execute(CommandDesc* commandDesc, CommandUndoRedoState undoRedoState) const
    {
        auto batchCommandDesc   = static_cast<BatchCommandDesc*>(commandDesc);
        auto cmdCnt             = batchCommandDesc->_cmdList.size();
        auto batchedPropertyCnt = batchCommandDesc->_batchedPropertyNames.size();

        if (undoRedoState == CommandUndoRedoState_Undo || undoRedoState == CommandUndoRedoState_Redo)
        {
            CommandManager::GetSingleton()._batchedPropertyTargets.push_back(QList<MObject*>());
            CommandManager::GetSingleton()._batchedPropertyNames.push_back(QList<QString>());

            if (batchedPropertyCnt > 0)
            {
                auto batchLevel = CommandManager::GetSingleton()._batchedPropertyTargets.size() - 1;
                auto tagets     = batchCommandDesc->_batchedPropertyTargets;
                auto names      = batchCommandDesc->_batchedPropertyNames;

                CommandManager::GetSingleton()._batchedPropertyTargets[batchLevel] = tagets;
                CommandManager::GetSingleton()._batchedPropertyNames[batchLevel]   = names;
            }

            for (int i = 0; i < cmdCnt; i++)
            {
                auto undoCmd = batchCommandDesc->_cmdList[i];
                CommandManager::GetSingleton().ExecuteCommand(undoCmd, undoRedoState);
            }

            CommandManager::GetSingleton()._batchedPropertyTargets.removeLast();
            CommandManager::GetSingleton()._batchedPropertyNames.removeLast();
        }

        if (batchedPropertyCnt > 0)
        {
            for (int i = 0; i < batchedPropertyCnt; i++)
            {
                auto propertyName = batchCommandDesc->_batchedPropertyNames[i];
                auto target       = batchCommandDesc->_batchedPropertyTargets[i];
                target->OnPropertyChanged(propertyName);
            }
        }
    }
} // namespace xStudio