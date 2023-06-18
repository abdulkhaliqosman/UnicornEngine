#include "qteditorwindow.h"
#include "editor/editor.h"

constexpr int FPS_LIMIT = 1000.0f;
constexpr int MS_PER_FRAME = (int)((1.0f / FPS_LIMIT) * 1000.0f);

QtEditorWindow::QtEditorWindow(unieditor::Editor* editor, QWidget* parent)
    : QMainWindow(parent), m_Editor(editor)
{
    ui.setupUi(this);

    connect(&m_qTimer, &QTimer::timeout, this, &QtEditorWindow::Update);
}

QtEditorWindow::~QtEditorWindow()
{}


void QtEditorWindow::Startup()
{
    m_qTimer.start(MS_PER_FRAME);
}

void QtEditorWindow::Update()
{
    m_Editor->Update();
    m_qTimer.start(MS_PER_FRAME);
}
