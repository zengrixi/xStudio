/*****************************************************************//**
 * \file   BatchCommand.h
 * \brief  批量执行多个其他Command的操作
 * 
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include "BaseCommand.h"

namespace xStudio
{
    class BatchCommand : public BaseCommand
    {
    public:
        /**
         * 执行指令（可重入）.
         * 
         * \param commandDesc   指令描述
         * \param undoRedoState 指令是否处于撤销或者重做状态
         */
        void Execute(CommandDesc*         commandDesc,
                     CommandUndoRedoState undoRedoState = CommandUndoRedoState_Normal) const override;
    };
} // namespace xStudio
