#include "fileedit.h"

#include <QFileDialog>
#include <QFocusEvent>
#include <QHBoxLayout>
#include <QToolButton>

FileEdit::FileEdit(QWidget* parent)
    : QWidget(parent)
{
    auto layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    _theLineEdit = new QLineEdit(this);
    _theLineEdit->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));

    auto button = new QToolButton(this);
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    button->setText("...");

    layout->addWidget(_theLineEdit);
    layout->addWidget(button);

    setFocusProxy(_theLineEdit);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);

    connect(_theLineEdit, &QLineEdit::textEdited, this, &FileEdit::filePathChanged);
    connect(button, &QToolButton::clicked, this, &FileEdit::buttonClicked);
}

void FileEdit::focusInEvent(QFocusEvent* e)
{
    _theLineEdit->event(e);
    if (e->reason() == Qt::TabFocusReason || e->reason() == Qt::BacktabFocusReason)
    {
        _theLineEdit->selectAll();
    }
    QWidget::focusInEvent(e);
}

void FileEdit::focusOutEvent(QFocusEvent* e)
{
    _theLineEdit->event(e);
    QWidget::focusOutEvent(e);
}

void FileEdit::keyPressEvent(QKeyEvent* e) { _theLineEdit->event(e); }

void FileEdit::keyReleaseEvent(QKeyEvent* e) { _theLineEdit->event(e); }

void FileEdit::buttonClicked()
{
    auto path = QFileDialog::getOpenFileName(this, "Choose a file", _theLineEdit->text(), _theFilter);
    if (path.isEmpty())
        return;

    _theLineEdit->setText(path);

    emit filePathChanged(path);
}