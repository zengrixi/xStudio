#include "CommandManager.h"
#include <Cmd/Command/ChangeObjectPropertyCommand.h>
#include <Cmd/CommandDesc/ChangeObjectPropertyCommandDesc.h>

namespace xStudio
{
    void CommandManager::Initialzie()
    {
        RegisterCommand(new ChangeObjectPropertyCommandDesc(), new ChangeObjectPropertyCommand());
        RegisterCommand(new ChangeObjectListPropertyCommandDesc(), new ChangeObjectListPropertyCommand());
    }

    void CommandManager::RegisterCommand(CommandDesc* cmdDesc, BaseCommand* cmd)
    {
        _cmdNameToCmd[cmdDesc->GetCommandName()]     = cmd;
        _cmdNameToCmdDesc[cmdDesc->GetCommandName()] = cmdDesc;
    }

    void CommandManager::SendCommand(CommandDesc* cmdDesc, bool supportUndoRedo, float delayTime)
    {
        if (delayTime > 0)
        {
            auto delayDispatchCommand             = new DelayDispatchCommand();
            delayDispatchCommand->cmdDesc         = cmdDesc;
            delayDispatchCommand->supportUndoRedo = supportUndoRedo;
            delayDispatchCommand->delayTime       = delayTime;
            _delayDispatchCommandSet.push_back(delayDispatchCommand);
            return;
        }

        if (_cmdNameToCmd.contains(cmdDesc->GetCommandName()))
        {
            auto cmd = _cmdNameToCmd[cmdDesc->GetCommandName()];

            ExecuteCommand(cmdDesc, CommandUndoRedoState_Normal);

            if (supportUndoRedo)
            {
                if (_batchLevel >= 0)
                {
                    if (_batchCommands[_batchLevel].size() > 0 && cmdDesc->_combinedable)
                    {
                        for (int i = 0; i < _batchCommands[_batchLevel].size(); i++)
                        {
                            CommandDesc* lastCommand = _batchCommands[_batchLevel][i];
                            if (cmdDesc->CombinedWith(lastCommand))
                            {
                                delete lastCommand;
                                _batchCommands[_batchLevel].removeAt(i--);
                            }
                        }
                    }

                    _batchCommands[_batchLevel].push_back(cmdDesc);
                }
            }
            else
            {
                delete cmdDesc;
            }
        }
        else
        {
            ExecuteCommand(cmdDesc, CommandUndoRedoState_Normal);
        }
    }

    void CommandManager::Undo(const QString& windowName) { }

    void CommandManager::Redo(const QString& windowName) { }

    void CommandManager::ChangeObjectProperty(MObject*        target,
                                              QString         propertyName,
                                              const QVariant& newValue,
                                              const QVariant& oldValue,
                                              bool            canBeCombined,
                                              QList<MObject*> refObjectList,
                                              CommandDesc*    accompanyCmd)
    {
        auto option      = CommandDescOption(accompanyCmd, refObjectList, canBeCombined);
        auto commandDesc = new ChangeObjectPropertyCommandDesc(target, propertyName, newValue, oldValue, option);

        SendCommand(commandDesc, true);
    }

    void CommandManager::ChangeObjectListProperty(MObject*        target,
                                                  const QString&  listName,
                                                  ListOperateEnum operate,
                                                  int             index,
                                                  int             cnt,
                                                  const QVariant& newValue,
                                                  const QVariant& oldValue,
                                                  bool            canBeCombined,
                                                  QList<MObject*> refObjectList,
                                                  CommandDesc*    accompanyCmd)
    {
        auto option      = CommandDescOption(accompanyCmd, refObjectList, canBeCombined);
        auto commandDesc = new ChangeObjectListPropertyCommandDesc(target,
                                                                   listName,
                                                                   operate,
                                                                   index,
                                                                   cnt,
                                                                   newValue,
                                                                   oldValue,
                                                                   option);

        SendCommand(commandDesc, true);
    }

    void CommandManager::ExecuteCommand(CommandDesc* commandDesc, CommandUndoRedoState undoRedoState)
    {
        auto cmd = _cmdNameToCmd[commandDesc->GetCommandName()];

        if (cmd)
            cmd->Execute(commandDesc, undoRedoState);
        else
            emit DispatchCommandWithDesc(commandDesc);

        if (commandDesc->_accompanyCmd)
            ExecuteCommand(commandDesc->_accompanyCmd, undoRedoState);
    }
} // namespace xStudio