#pragma once

#include <QDockWidget>
#include <QListWidget>
#include "ui_qtpropertyinspector.h"

class QtPropertyInspector : public QDockWidget
{
    Q_OBJECT

public:
    QtPropertyInspector(QWidget *parent = nullptr);
    ~QtPropertyInspector();

private:
    Ui::QtPropertyInspectorClass ui;

    QListWidget* paragraphsList;
};
