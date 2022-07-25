#include "ui_maintainview.h"

MaintainView::MaintainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MaintainView)
{
    ui->setupUi(this);
}

MaintainView::~MaintainView()
{
    delete ui;
}
