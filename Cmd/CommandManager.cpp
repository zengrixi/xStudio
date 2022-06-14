#include "CommandManager.h"

namespace xStudio
{
    void CommandManager::Initialzie()
    {
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
    }

    void CommandManager::Undo(const QString& windowName)
    {
    }

    void CommandManager::Redo(const QString& windowName)
    {
    }
} // namespace xStudio
