#include "createvcf.h"
#include "qvalidator.h"
#include "ui_createvcf.h"
#include "vcf.h"
#include <iostream>
#include <QFileDialog>
#include <QSettings>
#include <QKeyEvent>
#include <fstream>

CreateVCF::CreateVCF(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateVCF)
// Constructor
{
    ui->setupUi(this);
    ui->numberEntry->setValidator(new QIntValidator(0, 9999999999, this));
    ui->numberComboBox->setCurrentText("NUMBERS");
    ui->addNumberButton->setShortcut(Qt::Key_Enter);

    QSettings setting("VCFSaver", "vcf");
    setting.beginGroup("settings");
    counterNum = setting.value("counter").toInt();
    setting.endGroup();
}

// Destructor
CreateVCF::~CreateVCF()
{
    delete ui;
}

//Back Button Clicked Event
void CreateVCF::on_backButton_clicked()
{
    numberList = {};
    VCF *homeWindow = new VCF;
    hide();
    homeWindow->show();
}

//Add Button Clicked Event
void CreateVCF::on_addNumberButton_clicked()
{
    QSettings setting("VCFSaver", "vcf");
    setting.beginGroup("settings");
    bool numberLock = setting.value("numberLock").toBool();
    QString numberLockLength = setting.value("numberLockLength", 10).toString();
    setting.endGroup();

    int numberLockLengthInteger = numberLockLength.toInt();
    if(ui->numberEntry->text() != ""){
        if(numberLock == 1 && ui->numberEntry->text().size() != numberLockLengthInteger)
        {
            return;
        }else{
            numberList.append(ui->numberEntry->text());
            ui->numberComboBox->addItem(ui->numberEntry->text());
            ui->numberEntry->setText("");
            ui->numberEntry->setFocus();
        }
    }
}

// Number Entry Validate Clicked Event
void CreateVCF::on_numberEntry_textChanged()
{
    QSettings setting("VCFSaver", "vcf");
    setting.beginGroup("settings");
    QString numberLockLength = setting.value("numberLockLength", 10).toString();
    bool numberLock = setting.value("numberLock").toBool();
    setting.endGroup();

    if(std::strlen(ui->numberEntry->text().toStdString().c_str()) == numberLockLength.toInt())
    {
        ui->numberEntry->setStyleSheet("color: green;");
    }else
    {
        ui->numberEntry->setStyleSheet("color: black;");
    }
    if(numberLock == 1 && ui->numberEntry->text().length() > numberLockLength.toInt())
    {
        QString text = ui->numberEntry->text().remove(1,1);
        ui->numberEntry->setText(text);
    }
}

// Convert First Word Of Each Line To Uppercase
QString CreateVCF::firstLetterToUpperCase(QString str)
{
    int length = str.length();
    str[0] = str[0].toUpper();
    for(int i=0; i<length; i++)
    {
        if(str[i] == ' ')
        {
            str[i + 1] = str[i + 1].toUpper();
        }
    }
    return str;
}

// Replace multiple spaces with single space
QString CreateVCF::removeDoubleSpaces(QString name)
{
    while(name.contains("  ")){
        name.replace("  ", " ");
    }
    return name;
}

// Save Button Clicked Event
void CreateVCF::on_saveButton_clicked()
{
    QSettings setting("VCFSaver", "vcf");
    setting.beginGroup("settings");
    bool autoCapitalize = setting.value("autoCapitalize", true).toBool();
    bool setCounter = setting.value("setCounter").toBool();
    QString suffix = setting.value("suffix", "").toString();
    QString prefix = setting.value("prefix", "").toString();
    QString fileName = setting.value("fileName").toString();
    QString folderPath = setting.value("folderPath").toString();
    setting.endGroup();
    QString name = ui->nameEntry->text(), number, path;
    name = prefix + " " + name + " " + suffix;
    // Numeric Counter toggle from settings
    if(setCounter == true)
    {
        QString tempStr = QString::number(counterNum);
        name = name + " " + tempStr;
        counterNum++;
    }
    // Auto Capitalize toggle from settings
    if(autoCapitalize == true)
    {
        name = firstLetterToUpperCase(name);
        name = removeDoubleSpaces(name);
    }

    // Open vcf file
    std::ofstream file;
    path = folderPath + "/" + fileName + ".vcf";
    file.open(path.toStdString().c_str(), std::ios::app);
    int counter = 0;

    // Enter data in vcf file
    file << "BEGIN:VCARD\n";
    file << "VERSION:2.1\n";
    file << "FN:" << name.toStdString().c_str() << "\n";
    while(counter < numberList.length() && file.is_open())
    {
        number = numberList[counter];
        file << "TEL;CELL:" << number.toStdString().c_str() << "\n";
        counter++;
    }
    file << "END:VCARD\n";
    file.close();

    // Reset entries
    ui->nameEntry->clear();
    ui->numberEntry->clear();
    ui->numberComboBox->clear();
    numberList = {};
}

// Reset Button Clicked Event
void CreateVCF::on_resetButton_clicked()
{
    ui->nameEntry->setText("");
    ui->nameEntry->setText("");
    ui->numberComboBox->clear();
    numberList = {};
}
