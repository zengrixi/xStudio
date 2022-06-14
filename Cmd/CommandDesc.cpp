#include "CommandDesc.h"
#include "CommandManager.h"

namespace xStudio
{
    CommandDesc::CommandDesc(const CommandDescOption& option)
        : _accompanyCmd(option._accompanyCmd)
        , _refObjectList(option._refObjectList)
        , _combinedable(option._combinedable)
    {
        for (auto& object : _refObjectList)
        {
            object->Ref();
        }
    }

    CommandDesc::~CommandDesc()
    {
        if (!_accompanyCmd)
        {
            delete _accompanyCmd;
        }

        for (auto& object : _refObjectList)
        {
            object->UnRef();
        }
    }

    bool CommandDesc::GetCombinedable() const
    {
        return _combinedable;
    }
} // namespace xStudio
