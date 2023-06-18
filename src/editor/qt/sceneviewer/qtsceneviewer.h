#pragma once

#include <QDockWidget>
#include "ui_qtsceneviewer.h"

class QtSceneViewer : public QDockWidget
{
    Q_OBJECT

public:
    QtSceneViewer(QWidget *parent = nullptr);
    ~QtSceneViewer();

private:
    Ui::QtSceneViewerClass ui;

};
