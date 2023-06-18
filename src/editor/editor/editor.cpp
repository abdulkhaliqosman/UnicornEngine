#include "editor.h"
#include <QtWidgets/QApplication>

#include "qt/assetbrowser/qtassetbrowser.h"
#include "qt/editorwindow/qteditorwindow.h"
#include "qt/objecthierarchy/qtobjecthierarchy.h"
#include "qt/property/inspector/qtpropertyinspector.h"
#include "qt/sceneviewer/qtsceneviewer.h"

#include <QTimer>

namespace unieditor
{
    void Editor::Init()
    {
        m_NetworkClient.Init();
    }
    void Editor::Run()
    {
        int argc = 0;
        char** argv = nullptr;
        QApplication a(argc, argv);

        QtEditorWindow w(this);

        QtAssetBrowser ab(&w);
        QtSceneViewer sv(&w);
        QtObjectHierarchy oh(&w);
        QtPropertyInspector pi(&w);
        

        w.setCentralWidget(&sv);
        w.addDockWidget(Qt::RightDockWidgetArea, &pi);
        w.addDockWidget(Qt::BottomDockWidgetArea, &ab);
        // w.addDockWidget(Qt::TopDockWidgetArea, &sv);
        w.addDockWidget(Qt::LeftDockWidgetArea, &oh);
        

        ab.setFloating(false);
        sv.setFloating(false);
        oh.setFloating(false);
        pi.setFloating(false);

        // m_Engine->GetRenderManager().SetHwnd((HWND)sv.widget()->winId());
        // m_Engine->Startup();
        w.Startup();
        w.show();
        a.exec();
    }

    void Editor::Update()
    {
        m_NetworkClient.Update();
        // m_Engine->Update();
    }
}