#include "qtassetbrowser.h"
#include "editor/editor.h"

constexpr int FPS_LIMIT = 60.0f;
constexpr int MS_PER_FRAME = (int)((1.0f / FPS_LIMIT) * 1000.0f);

QtAssetBrowser::QtAssetBrowser(QWidget* parent)
    : QDockWidget(parent)
{
    ui.setupUi(this);
}

QtAssetBrowser::~QtAssetBrowser()
{}
