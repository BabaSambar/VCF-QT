#include "editvcf.h"
#include "ui_editvcf.h"

editvcf::editvcf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editvcf)
{
    ui->setupUi(this);
}

editvcf::~editvcf()
{
    delete ui;
}
