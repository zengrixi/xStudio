#include "BatchCommandDesc.h"

namespace xStudio
{
    BatchCommandDesc::BatchCommandDesc(const QList<CommandDesc*>& cmdList,
                                       const QList<MObject*>&     batchedPropertyTargets,
                                       const QList<QString>&      batchedPropertyNames,
                                       const CommandDescOption&   option)
        : CommandDesc(option)
        , _cmdList(cmdList)
        , _batchedPropertyTargets(batchedPropertyTargets)
        , _batchedPropertyNames(batchedPropertyNames)
    {
    }

    CommandDesc* BatchCommandDesc::CreateSameTypeCommandDesc() const { return (new BatchCommandDesc()); }

    bool BatchCommandDesc::CombinedWith(CommandDesc* lastCmdDesc)
    {
        if (lastCmdDesc->GetCommandName() == GetCommandName() && lastCmdDesc->GetCombinedable())
        {
            auto lastBatchCommandDesc = static_cast<BatchCommandDesc*>(lastCmdDesc);
            if (lastBatchCommandDesc->_cmdList.size() == _cmdList.size())
            {
                for (int i = 0; i < _cmdList.size(); ++i)
                {
                    auto thisChildCmdDesc = _cmdList[i];
                    auto lastChildCmdDesc = lastBatchCommandDesc->_cmdList[i];
                    if (!thisChildCmdDesc->CombinedWith(lastChildCmdDesc))
                    {
                        return false;
                    }
                }
                return true;
            }
        }
        return false;
    }

    bool BatchCommandDesc::HasModifiedTarget(MObject* target) const
    {
        for (auto cmdDes : _cmdList)
        {
            if (cmdDes->HasModifiedTarget(target))
                return true;
        }
        return false;
    }
} // namespace xStudio