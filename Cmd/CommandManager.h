/*****************************************************************/ /**
 * \file   CommandManager.h
 * \brief  ���������
 *
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <QObject.h>
#include <QMap>

#include <Util/Singleton.h>

#include <Cmd/Command/BaseCommand.h>
#include <Cmd/CommandDesc/CommandDesc.h>

namespace xStudio
{
    enum ListOperateEnum
    {
        ListOperateEnum_Add,
        ListOperateEnum_Remove,
        ListOperateEnum_Update
    };

    struct DelayDispatchCommand
    {
        CommandDesc* cmdDesc;
        bool         supportUndoRedo;
        float        delayTime;
    };

    class CommandManager
        : public QObject
        , public Singleton<CommandManager>
    {
        Q_OBJECT

    public:
        void Initialzie();

        /**
         * ע��ָ��.
         *
         * \param cmdDesc   ָ����������
         * \param cmd       ָ��ִ�ж���
         */
        void RegisterCommand(CommandDesc* cmdDesc, BaseCommand* cmd);

        /**
         * ����ָ��.
         *
         * \param cmdDesc           ָ������ָ�루��ָ���ⲿ����Ҫ�ͷţ�ֻ��Ҫ������ָ��ϵͳ������ָ����������ڣ�
         * \param supportUndoRedo   �Ƿ���Ҫ֧�ֳ������������������ָ���֧�ֳ���������������Ҳ���ܳ�����������
         * \param delayTime         �ӳٶ����뷢�ͣ����Ϊ0��������ִ��
         */
        void SendCommand(CommandDesc* cmdDesc, bool supportUndoRedo = true, float delayTime = 0.f);

        /**
         * �����ϴ�ִ�е�ָ��.
         *
         * \param windowName    ָ��ִ�����ĸ���������
         */
        void Undo(const QString& windowName);

        /**
         * �����ϴ�ִ�е�ָ��.
         *
         * \param windowName    ָ��ִ�����ĸ���������
         */
        void Redo(const QString& windowName);

        void ChangeObjectProperty(MObject*        target,
                                  QString         propertyName,
                                  const QVariant& newValue,
                                  const QVariant& oldValue,
                                  bool            canBeCombined = false,
                                  QList<MObject*> refObjectList = QList<MObject*>(),
                                  CommandDesc*    accompanyCmd  = nullptr);

        void ChangeObjectListProperty(MObject*        target,
                                      const QString&  listName,
                                      ListOperateEnum operate,
                                      int             index,
                                      int             cnt,
                                      const QVariant& newValue,
                                      const QVariant& oldValue,
                                      bool            canBeCombined = false,
                                      QList<MObject*> refObjectList = QList<MObject*>(),
                                      CommandDesc*    accompanyCmd  = nullptr);

    private:
        void ExecuteCommand(CommandDesc* commandDesc, CommandUndoRedoState undoRedoState);

    signals:
        void DispatchCommandWithDesc(CommandDesc* commandDesc);

    private:
        //ָ�����ֺ�ָ��ִ�ж����
        QMap<QString, BaseCommand*> _cmdNameToCmd;
        //ָ�����ֺ�ָ�����������
        QMap<QString, CommandDesc*> _cmdNameToCmdDesc;

        int                        _batchLevel = -1;
        QList<QList<CommandDesc*>> _batchCommands;

        QList<DelayDispatchCommand*> _delayDispatchCommandSet;
    };
}; // namespace xStudio
