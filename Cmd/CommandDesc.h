/*****************************************************************/ /**
 * \file   CommandDesc.h
 * \brief  指令描述类
 * 
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <QtCore/QList>
#include <QtCore/QString>

#include <Model/MObject.h>

namespace xStudio
{
    class CommandDesc;

    class CommandDescOption
    {
    public:
        CommandDescOption()
            : _accompanyCmd(nullptr)
            , _combinedable(false)
        {
        }

        /**
         * 指令描述可选参数构造函数.
         * 
         * \param combinedable  该指令是否可以合并
         */
        CommandDescOption(bool combinedable)
            : _accompanyCmd(nullptr)
            , _combinedable(combinedable)
        {
        }

        /**
         * 指令描述可选参数构造函数.
         * 
         * \param refObjectList 该指令引用的对象列表（指令引用的对象的引用计数会加1，只要该指令还可以撤销，被引用的对象就不会被销毁）
         */
        CommandDescOption(const QList<MObject*>& refObjectList)
            : _accompanyCmd(nullptr)
            , _refObjectList(refObjectList)
            , _combinedable(false)
        {
        }

        /**
         * 指令描述可选参数构造函数.
         * 
         * \param accompanyCmd  伴随指令（该指令执行完之后紧接着会执行的指令）
         * \param refObjectList 该指令引用的对象列表（指令引用的对象的引用计数会加1，只要该指令还可以撤销，被引用的对象就不会被销毁）
         * \param combinedable  该指令是否可以合并
         */
        CommandDescOption(CommandDesc*           accompanyCmd,
                          const QList<MObject*>& refObjectList = QList<MObject*>(),
                          bool                   combinedable  = false)
            : _accompanyCmd(accompanyCmd)
            , _refObjectList(refObjectList)
            , _combinedable(combinedable)
        {
        }

    private:
        CommandDesc*    _accompanyCmd;
        QList<MObject*> _refObjectList;
        bool            _combinedable;

        friend class CommandDesc;
    };

    class CommandDesc
    {
    public:
        /**
         * 指令描述构造函数.
         * 
         * \param option    可选参数
         */
        CommandDesc(const CommandDescOption& option = CommandDescOption());
        ~CommandDesc();

        /**
         * 获取指令名称.
         * 
         * \return 指令名称
         */
        virtual QString GetCommandName() const = 0;

        /**
         * 根据当前指令描述的类型创建同类型的指令描述.
         * 
         * \return 当前指令描述同类型的指令描述
         */
        virtual CommandDesc* CreateSameTypeCommandDesc() const = 0;

        /**
         * 将当前指令和前面一条指令合并成一条指令，主要是为了减少内存占用和达到一次性撤销的目的.
         * 
         * \param lastCmdDesc   上一条指令描述
         * \return              是否成功合并
         */
        virtual bool CombinedWith(CommandDesc* lastCmdDesc) { return false; }

        virtual bool HasModifiedTarget(MObject* target) const { return false; }

        bool GetCombinedable() const;

    protected:
        CommandDesc*    _accompanyCmd;
        QList<MObject*> _refObjectList;
        bool            _combinedable;

        friend class CommandManager;
        friend class UndoRedoActor;
    };
} // namespace xStudio