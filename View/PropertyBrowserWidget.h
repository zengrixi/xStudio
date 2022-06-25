/*****************************************************************/ /**
 * \file   PropertyBrowerWidget.h
 * \brief  实体属性展示窗体
 *
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once
#include <QWidget>

#include <GlobalDef/PropertyType.h>
#include <Model/MObject.h>
#include <View/qtpropertybrowser/qteditorfactory.h>
#include <View/qtpropertybrowser/qtpropertymanager.h>
#include <View/qtpropertybrowser/qttreepropertybrowser.h>

namespace xStudio
{
    class PropertyBrowserWidget : public QWidget
    {
        Q_OBJECT
    public:
        PropertyBrowserWidget(QWidget* parent);
        ~PropertyBrowserWidget();

        void SetPropertyName(const QString& value);

        void     SetObject(MObject* value);
        MObject* GetObject() const;

        void            SetObjectList(const QList<MObject*>& value);
        QList<MObject*> GetObjectList() const;

    protected:
        void OnValueChanged();
        void OnObjectPropertyChanged(const QString& propertyName);
        void BeforeObjectDetroyed();
        void OnSetObject();

    private:
        void _Init();

    private:
        QString      _propetyName;
        PropertyType _objectPropertyType;
        MObject*     _object = nullptr;

        QtTreePropertyBrowser* _treePropertyBrowser = nullptr;

        // 可编辑
        QtBoolPropertyManager*       _boolManager;
        QtIntPropertyManager*        _intManager;
        QtDoublePropertyManager*     _doubleManager;
        QtStringPropertyManager*     _stringManager;
        QtSizePropertyManager*       _sizeManager;
        QtRectPropertyManager*       _rectManager;
        QtSizePolicyPropertyManager* _sizePolicyManager;
        QtEnumPropertyManager*       _enumManager;
        QtColorPropertyManager*      _colorManager;
        QtVec3PropertyManager*       _vec3Manager;

        // 不可编辑
        QtGroupPropertyManager*  _groupManager;
        QtIntPropertyManager*    _int_read_only_;
        QtDoublePropertyManager* _double_read_only_;
        QtStringPropertyManager* _string_read_only_;

        // 工厂
        QtCheckBoxFactory*      _checkBoxFactory;
        QtSpinBoxFactory*       _spinBoxFactory;
        QtDoubleSpinBoxFactory* _doubleSpinBoxFactory;
        QtLineEditFactory*      _lineEditFactory;
        QtEnumEditorFactory*    _comboBoxFactory;
        QtColorEditorFactory*   _colorEditorFactory;

        QtProperty* _name;
        QtProperty* _id;
        QtProperty* _position;
        QtProperty* _scale;
        QtProperty* _rotate;
    };
} // namespace xStudio
