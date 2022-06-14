/*****************************************************************/ /**
 * \file   CommandDesc.h
 * \brief  ָ��������
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
         * ָ��������ѡ�������캯��.
         * 
         * \param combinedable  ��ָ���Ƿ���Ժϲ�
         */
        CommandDescOption(bool combinedable)
            : _accompanyCmd(nullptr)
            , _combinedable(combinedable)
        {
        }

        /**
         * ָ��������ѡ�������캯��.
         * 
         * \param refObjectList ��ָ�����õĶ����б�ָ�����õĶ�������ü������1��ֻҪ��ָ����Գ����������õĶ���Ͳ��ᱻ���٣�
         */
        CommandDescOption(const QList<MObject*>& refObjectList)
            : _accompanyCmd(nullptr)
            , _refObjectList(refObjectList)
            , _combinedable(false)
        {
        }

        /**
         * ָ��������ѡ�������캯��.
         * 
         * \param accompanyCmd  ����ָ���ָ��ִ����֮������Ż�ִ�е�ָ�
         * \param refObjectList ��ָ�����õĶ����б�ָ�����õĶ�������ü������1��ֻҪ��ָ����Գ����������õĶ���Ͳ��ᱻ���٣�
         * \param combinedable  ��ָ���Ƿ���Ժϲ�
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
         * ָ���������캯��.
         * 
         * \param option    ��ѡ����
         */
        CommandDesc(const CommandDescOption& option = CommandDescOption());
        ~CommandDesc();

        /**
         * ��ȡָ������.
         * 
         * \return ָ������
         */
        virtual QString GetCommandName() const = 0;

        /**
         * ���ݵ�ǰָ�����������ʹ���ͬ���͵�ָ������.
         * 
         * \return ��ǰָ������ͬ���͵�ָ������
         */
        virtual CommandDesc* CreateSameTypeCommandDesc() const = 0;

        /**
         * ����ǰָ���ǰ��һ��ָ��ϲ���һ��ָ���Ҫ��Ϊ�˼����ڴ�ռ�úʹﵽһ���Գ�����Ŀ��.
         * 
         * \param lastCmdDesc   ��һ��ָ������
         * \return              �Ƿ�ɹ��ϲ�
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