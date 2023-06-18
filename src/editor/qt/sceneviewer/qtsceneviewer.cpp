#include "qtsceneviewer.h"

QtSceneViewer::QtSceneViewer(QWidget *parent)
    : QDockWidget(tr("Scene Viewer"), parent)
{
    ui.setupUi(this);

    // QPalette pal = palette();
    // pal.setColor(QPalette::Window, Qt::black);
    // setAutoFillBackground(true);
    // setPalette(pal);
    // 
    // setFocusPolicy(Qt::StrongFocus);
    // setAttribute(Qt::WA_NativeWindow);

    // Setting these attributes to our widget and returning null on paintEngine event
    // tells Qt that we'll handle all drawing and updating the widget ourselves.
    // setAttribute(Qt::WA_PaintOnScreen);
    // setAttribute(Qt::WA_NoSystemBackground);
}

QtSceneViewer::~QtSceneViewer()
{}
