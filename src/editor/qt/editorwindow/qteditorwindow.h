#pragma once

#include <QMainWindow>
#include <QTimer>
#include "ui_qteditorwindow.h"

namespace unieditor
{
    class Editor;
}

class QtEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    QtEditorWindow(unieditor::Editor* editor, QWidget* parent = nullptr);
    ~QtEditorWindow();

    void Startup();
    void Update();
signals:

private:
    void SetupUI();

    Ui::QtEditorWindowClass ui;
    QTimer m_qTimer;
    unieditor::Editor* m_Editor;
};
