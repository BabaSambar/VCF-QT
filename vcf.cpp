#include "vcf.h"
#include "ui_vcf.h"
#include "createvcf.h"
#include "settings.h"
#include "editvcf.h"

VCF::VCF(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VCF)
{
    ui->setupUi(this);
}

VCF::~VCF()
{
    delete ui;
}

void VCF::on_createVCFButton_clicked()
{
    CreateVCF *createVCFDialog = new CreateVCF;
    hide();
    createVCFDialog->show();
}

void VCF::on_editbutton_clicked()
{
    editvcf *editVCFDialog = new editvcf;
    hide();
    editVCFDialog->show();
}

void VCF::on_settingsbutton_clicked()
{
    settings *settingsDialog = new settings;
    hide();
    settingsDialog->show();
}

