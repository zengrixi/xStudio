#include "CommandManager.h"
#include <Cmd/Command/ChangeObjectPropertyCommand.h>
#include <Cmd/CommandDesc/ChangeObjectPropertyCommandDesc.h>

#include <Cmd/CommandDesc/BatchCommandDesc.h>
#include <QDateTime>

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
                if (_batchLevel == -1)
                {
                    if (cmdDesc->_combinedable)
                    {
                        auto lastCommand = _undoStack.top();
                        if (lastCommand && cmdDesc->CombinedWith(lastCommand))
                        {
                            _undoStack.pop();
                        }
                        _lastCombinedableCmd = cmdDesc;
                    }

                    _undoStack.push(cmdDesc);
                }
                else if (_batchLevel >= 0)
                {
                    if (_batchCommands[_batchLevel].size() > 0 && cmdDesc->_combinedable)
                    {
                        for (int i = 0; i < _batchCommands[_batchLevel].size(); i++)
                        {
                            auto lastCommand = _batchCommands[_batchLevel][i];
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

    void CommandManager::Undo()
    {
        if (_undoStack.top())
        {
            auto lastCmd = _undoStack.pop();
            _redoStack.push(lastCmd);
            ExecuteCommand(lastCmd, CommandUndoRedoState_Undo);
        }
    }

    void CommandManager::Redo()
    {
        if (_redoStack.top())
        {
            auto lastCmd = _redoStack.pop();
            _undoStack.push(lastCmd);
            ExecuteCommand(lastCmd, CommandUndoRedoState_Redo);
        }
    }

    void CommandManager::StartBatch()
    {
        _lastStartBatchTime = QDateTime::currentMSecsSinceEpoch();
        _batchCommands.push_back(QList<CommandDesc*>());
        _batchedPropertyNames.push_back(QList<QString>());
        _batchedPropertyTargets.push_back(QList<MObject*>());
        _batchLevel++;
    }

    void CommandManager::StartBatch(const QString& batchedPropertyName, MObject* target)
    {
        StartBatch();
        _batchedPropertyNames[_batchLevel].push_back(batchedPropertyName);
        _batchedPropertyTargets[_batchLevel].push_back(target);
    }

    void CommandManager::EndBatch()
    {
        if (_batchLevel != -1 && !_batchCommands.isEmpty() && _batchCommands[_batchLevel].size() > 0)
        {
            auto cmdList       = QList<CommandDesc*>();
            auto canBeCombined = true;

            for (int i = 0; i < _batchCommands[_batchLevel].size(); i++)
            {
                cmdList.push_back(_batchCommands[_batchLevel][i]);
                if (!_batchCommands[_batchLevel][i]->_combinedable)
                    canBeCombined = false;
            }

            auto cmd = new BatchCommandDesc(cmdList,
                                            _batchedPropertyTargets[_batchLevel],
                                            _batchedPropertyNames[_batchLevel],
                                            CommandDescOption(canBeCombined));

            _batchLevel--;
            _batchCommands.removeLast();
            _batchedPropertyTargets.removeLast();
            _batchedPropertyNames.removeLast();

            SendCommand(cmd, true);
        }
        else
        {
            if (_batchLevel >= 0)
            {
                _batchLevel--;
                _batchCommands.removeLast();
                _batchedPropertyTargets.removeLast();
                _batchedPropertyNames.removeLast();
            }
        }
    }

    bool CommandManager::HasBatch() { return (!_batchCommands.isEmpty()); }

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