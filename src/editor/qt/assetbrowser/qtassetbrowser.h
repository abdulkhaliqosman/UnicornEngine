#pragma once

#include <QDockWidget>
#include "ui_qtassetbrowser.h"

class QtAssetBrowser : public QDockWidget
{
    Q_OBJECT

public:
    QtAssetBrowser(QWidget* parent = nullptr);
    ~QtAssetBrowser() override;

private:
    Ui::QtAssetBrowserClass ui;

};
