#pragma once
#include "BaseCommand.h"
namespace xStudio
{
    class ChangeObjectPropertyCommand : public BaseCommand
    {
    public:
        void Execute(CommandDesc*         commandDesc,
                     CommandUndoRedoState undoRedoState = CommandUndoRedoState_Normal) const override;
    };

    class ChangeObjectListPropertyCommand : public BaseCommand
    {
    public:
        void Execute(CommandDesc*         commandDesc,
                     CommandUndoRedoState undoRedoState = CommandUndoRedoState_Normal) const override;
    };
} // namespace xStudio
