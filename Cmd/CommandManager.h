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
#include <QStack>

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
         */
        void Undo();

        /**
         * �����ϴ�ִ�е�ָ��.
         *
         */
        void Redo();

        void StartBatch();

        /**
         * ��Ҫһ�𴥷����Ըı��¼���������.
         *
         * \param batchedPropertyName
         * \param target
         */
        void StartBatch(const QString& batchedPropertyName, MObject* target);

        void EndBatch();

        bool HasBatch();

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

        QList<QList<QString>>  _batchedPropertyNames;
        QList<QList<MObject*>> _batchedPropertyTargets;

        QStack<CommandDesc*> _undoStack;
        QStack<CommandDesc*> _redoStack;

        uint64_t _lastStartBatchTime = 0;

        QList<DelayDispatchCommand*> _delayDispatchCommandSet;

        CommandDesc* _lastCombinedableCmd = nullptr;

        friend class BatchCommand;
        friend class CommandDesc;
    };
}; // namespace xStudio
