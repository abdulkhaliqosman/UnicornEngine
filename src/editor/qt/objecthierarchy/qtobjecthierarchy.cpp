#include "qtobjecthierarchy.h"

QtObjectHierarchy::QtObjectHierarchy(QWidget *parent)
    : QDockWidget(parent)
{
    ui.setupUi(this);


    paragraphsList = new QListWidget(this);
    paragraphsList->addItems(QStringList()
        << "Object 1"
        << "Object 2"
        << "Object 3"
        << "Object 4"
        << "Object 5"
        << "Object 6"
        << "Object 7");

    setWidget(paragraphsList);
}

QtObjectHierarchy::~QtObjectHierarchy()
{}
