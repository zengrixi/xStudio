#include "PropertyBrowserWidget.h"

#include <QHBoxLayout>

#include <Model/MEntity.h>

namespace xStudio
{
    PropertyBrowserWidget::PropertyBrowserWidget(QWidget* parent)
        : QWidget(parent)
    {
        _treePropertyBrowser = new QtTreePropertyBrowser(this);

        auto layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        layout->addWidget(_treePropertyBrowser);
        setLayout(layout);

        _Init();
    }

    PropertyBrowserWidget::~PropertyBrowserWidget() { }

    void PropertyBrowserWidget::SetObject(MObject* value)
    {
        if (value != _object)
        {
            if (_object)
            {
                disconnect(_object, &MObject::PropertyChanged, this, &PropertyBrowserWidget::OnObjectPropertyChanged);
                disconnect(_object, &MObject::BeforeDestroy, this, &PropertyBrowserWidget::BeforeObjectDetroyed);
            }

            _object = value;

            if (_object)
            {
                connect(_object, &MObject::PropertyChanged, this, &PropertyBrowserWidget::OnObjectPropertyChanged);
                connect(_object, &MObject::BeforeDestroy, this, &PropertyBrowserWidget::BeforeObjectDetroyed);
            }

            OnSetObject();
            OnObjectPropertyChanged(QString());
        }
    }

    MObject* PropertyBrowserWidget::GetObject() const { return nullptr; }

    void PropertyBrowserWidget::OnValueChanged() { }

    void PropertyBrowserWidget::OnObjectPropertyChanged(const QString& propertyName) { }

    void PropertyBrowserWidget::BeforeObjectDetroyed() { }

    void PropertyBrowserWidget::OnSetObject()
    {
        auto entity = dynamic_cast<MEntity*>(_object);
        if (entity)
        {
            _stringManager->setValue(_name, entity->GetName());
            _intManager->setValue(_id, entity->GetId());
        }
    }

    void PropertyBrowserWidget::_Init()
    {
        _boolManager       = new QtBoolPropertyManager(this);
        _intManager        = new QtIntPropertyManager(this);
        _doubleManager_    = new QtDoublePropertyManager(this);
        _stringManager     = new QtStringPropertyManager(this);
        _sizeManager       = new QtSizePropertyManager(this);
        _rectManager       = new QtRectPropertyManager(this);
        _sizePolicyManager = new QtSizePolicyPropertyManager(this);
        _enumManager       = new QtEnumPropertyManager(this);
        _colorManager      = new QtColorPropertyManager(this);

        _checkBoxFactory      = new QtCheckBoxFactory(this);
        _spinBoxFactory       = new QtSpinBoxFactory(this);
        _doubleSpinBoxFactory = new QtDoubleSpinBoxFactory(this);
        _lineEditFactory      = new QtLineEditFactory(this);
        _comboBoxFactory      = new QtEnumEditorFactory(this);
        _colorEditorFactory   = new QtColorEditorFactory(this);

        _groupManager = new QtGroupPropertyManager(this);

        _treePropertyBrowser->setFactoryForManager(_boolManager, _checkBoxFactory);
        _treePropertyBrowser->setFactoryForManager(_intManager, _spinBoxFactory);
        _treePropertyBrowser->setFactoryForManager(_doubleManager_, _doubleSpinBoxFactory);
        _treePropertyBrowser->setFactoryForManager(_stringManager, _lineEditFactory);
        _treePropertyBrowser->setFactoryForManager(_sizeManager->subIntPropertyManager(), _spinBoxFactory);
        _treePropertyBrowser->setFactoryForManager(_rectManager->subIntPropertyManager(), _spinBoxFactory);
        _treePropertyBrowser->setFactoryForManager(_sizePolicyManager->subIntPropertyManager(), _spinBoxFactory);
        _treePropertyBrowser->setFactoryForManager(_sizePolicyManager->subEnumPropertyManager(), _comboBoxFactory);
        _treePropertyBrowser->setFactoryForManager(_enumManager, _comboBoxFactory);
        _treePropertyBrowser->setFactoryForManager(_colorManager, _colorEditorFactory);
        _treePropertyBrowser->setFactoryForManager(_colorManager->subIntPropertyManager(), _spinBoxFactory);

        auto _basicProperty = _groupManager->addProperty("basic properties");
        _name       = _stringManager->addProperty("name");
        _basicProperty->addSubProperty(_name);

        _id = _intManager->addProperty("id");
        _basicProperty->addSubProperty(_id);

        _position = _rectManager->addProperty("position");
        _basicProperty->addSubProperty(_position);

        _scale = _rectManager->addProperty("scale");
        _basicProperty->addSubProperty(_scale);

        _rotate = _rectManager->addProperty("rotate");
        _basicProperty->addSubProperty(_rotate);

        _treePropertyBrowser->addProperty(_basicProperty);
    }
} // namespace xStudio