#include "rendialog.h"
#include "ui_rendialog.h"

RenDialog::RenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenDialog)
{
    ui->setupUi(this);
}

RenDialog::~RenDialog()
{
    delete ui;
}
