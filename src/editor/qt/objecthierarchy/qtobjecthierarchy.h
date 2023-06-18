#pragma once

#include <QDockWidget>
#include <QListWidget>
#include "ui_qtobjecthierarchy.h"

class QtObjectHierarchy : public QDockWidget
{
    Q_OBJECT

public:
    QtObjectHierarchy(QWidget *parent = nullptr);
    ~QtObjectHierarchy();

private:
    Ui::QtObjectHierarchyClass ui;

    QListWidget* paragraphsList;
};
