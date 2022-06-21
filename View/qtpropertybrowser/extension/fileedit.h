/*****************************************************************//**
 * \file   fileedit.h
 * \brief  文件属性的编辑框小部件
 * 
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <QLineEdit>

class FileEdit : public QWidget
{
    Q_OBJECT

public:
    FileEdit(QWidget* parent = nullptr);

    void setFilePath(const QString& path)
    {
        if (_theLineEdit->text() != path)
            _theLineEdit->setText(path);
    }
    QString filePath() const { return _theLineEdit->text(); }
    void    setFilter(const QString& filter) { _theFilter = filter; }
    QString filter() const { return _theFilter; }

protected:
    void focusInEvent(QFocusEvent* e);
    void focusOutEvent(QFocusEvent* e);
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);

signals:
    void filePathChanged(const QString& file_path);

protected slots:
    void buttonClicked();

private:
    QLineEdit* _theLineEdit;
    QString    _theFilter;
};
