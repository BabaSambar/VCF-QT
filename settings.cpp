#include "settings.h"
#include "ui_settings.h"
#include <QSettings>
#include <iostream>
#include "vcf.h"
#include <QFileDialog>

// Constructor
settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    loadFolderFromSetting();

    QSettings setting("VCFSaver", "vcf");
    setting.beginGroup("settings");
    QString theme = setting.value("theme", "dark").toString();
    setting.endGroup();

    QString background_color = "";
    QString foreground_color = "";
    if(theme == "dark")  // Set color values for dark
    {
        background_color = "#252525";
        foreground_color = "#ffffff";
    }else if(theme == "light")  // Set color values for light
    {
        background_color = "#dcdcdd";
        foreground_color = "#222222";
    }else if(theme == "red")  // Set color values for red
    {
        background_color = "#fe8d3d";
        foreground_color = "#ff0004";
    }
    else if(theme == "blue")  // Set color values for blue
    {
        background_color = "#59ecff";
        foreground_color = "#400161";
    }else if(theme == "pink")  // Set color values for pink
    {
        background_color = "#ffaec2";
        foreground_color = "#fb2156";
    }
    this->setStyleSheet("background-color: " + background_color);
    this->setStyleSheet("color: " + foreground_color);

    loadSettings(foreground_color);  // Load function called at form load
}

// Destructor
settings::~settings()
{
    delete ui;
}

// Save Settings Function
void settings::saveSettings()
{
    QString theme = "dark";
    // Add setting to automatically save radio buttons
    if(ui->darkThemeRadioButton->isChecked())
    {
        theme = "dark";
    }else if(ui->lightThemeRadioButton->isChecked())
    {
        theme = "light";
    }else if(ui->redThemeRadioButton->isChecked())
    {
        theme = "red";
    }else if(ui->blueThemeRadioButton->isChecked())
    {
        theme = "blue";
    }else if(ui->pinkThemeRadioButton->isChecked())
    {
        theme = "pink";
    }
    QSettings setting("VCFSaver", "vcf");
    setting.beginGroup("settings");
    setting.setValue("numberLock", ui->numberLimitCheckBox->isChecked());
    setting.setValue("numberLockLength", ui->numberLockEntry->text());
    setting.setValue("autoCapitalize", ui->capitalizeCheckBox->isChecked());
    setting.setValue("prefix", ui->prefixEntry->text());
    setting.setValue("suffix", ui->suffixEntry->text());
    setting.setValue("theme", theme);
    setting.setValue("setCounter", ui->counterCheckBox->isChecked());
    setting.setValue("counter", ui->counterEntry->text());
    setting.setValue("fileName", ui->fileNameEntry->text());
    setting.setValue("folderPath", ui->folderEntry->text());
    setting.endGroup();
}

// Load Settings Function
void settings::loadSettings(QString foreground_color)
{
    QSettings setting("VCFSaver", "vcf");
    setting.beginGroup("settings");
    bool numberLock = setting.value("numberLock").toBool();
    bool autoCapitalize = setting.value("autoCapitalize").toBool();
    bool setCounter = setting.value("setCounter").toBool();
    QString numberLockLength = setting.value("numberLockLength", 10).toString();
    QString prefix = setting.value("prefix").toString();
    QString suffix = setting.value("suffix").toString();
    QString theme = setting.value("theme").toString();
    QString counter = setting.value("counter", "1").toString();
    QString folderPath = setting.value("folderPath").toString();
    QString fileName = setting.value("fileName").toString();
    setting.endGroup();

    ui->numberLimitCheckBox->setChecked(numberLock);
    ui->numberLockEntry->setText(numberLockLength);
    ui->capitalizeCheckBox->setChecked(autoCapitalize);
    ui->prefixEntry->setText(prefix);
    ui->suffixEntry->setText(suffix);
    ui->counterEntry->setText(counter);
    ui->counterCheckBox->setChecked(setCounter);
    ui->fileNameEntry->setText(fileName);
    // Set theme radio buttons to true according to the one selected
    if(theme == "dark")
    {
        ui->darkThemeRadioButton->setChecked(true);
    }else if(theme == "light")
    {
        ui->lightThemeRadioButton->setChecked(true);
    }else if(theme == "red")
    {
        ui->redThemeRadioButton->setChecked(true);
    }else if(theme == "blue")
    {
        ui->blueThemeRadioButton->setChecked(true);
    }else if(theme == "pink")
    {
        ui->pinkThemeRadioButton->setChecked(true);
    }
    // What a mess! I wonder if something can be done about it
    // Set all widgets color according to theme
    ui->prefixLabel->setStyleSheet("color: " + foreground_color);
    ui->settingsLabel->setStyleSheet("color: " + foreground_color);
    ui->numberLockEntryLabel->setStyleSheet("color: " + foreground_color);
    ui->suffixLabel->setStyleSheet("color: " + foreground_color);
    ui->themeLabel->setStyleSheet("color: " + foreground_color);
    ui->darkThemeRadioButton->setStyleSheet("color: " + foreground_color);
    ui->redThemeRadioButton->setStyleSheet("color: " + foreground_color);
    ui->blueThemeRadioButton->setStyleSheet("color: " + foreground_color);
    ui->pinkThemeRadioButton->setStyleSheet("color: " + foreground_color);
    ui->lightThemeRadioButton->setStyleSheet("color: " + foreground_color);
    ui->saveButton->setStyleSheet("color: " + foreground_color);
    ui->capitalizeCheckBox->setStyleSheet("color: " + foreground_color);
    ui->numberLimitCheckBox->setStyleSheet("color: " + foreground_color);
    ui->numberLockEntry->setStyleSheet("color: " + foreground_color);
    ui->prefixEntry->setStyleSheet("color: " + foreground_color);
    ui->suffixEntry->setStyleSheet("color: " + foreground_color);
    ui->counterCheckBox->setStyleSheet("color: " + foreground_color);
    ui->counterEntry->setStyleSheet("color: " + foreground_color);
    ui->fileNameEntry->setStyleSheet("color: " + foreground_color);
    ui->fileNameLabel->setStyleSheet("color: " + foreground_color);
    ui->folderEntry->setStyleSheet("color: " + foreground_color);
    ui->folderLabel->setStyleSheet("color: " + foreground_color);
}

// Save Button Clicked
void settings::on_saveButton_clicked()
{
    saveSettings();

    VCF *homewindow = new VCF;
    hide();
    homewindow->show();
}

// Load Folder Path from Setting
void settings::loadFolderFromSetting()
{
    QSettings setting("VCFSaver", "vcf");
    setting.beginGroup("settings");
    QString folderPath = setting.value("folderPath", QDir::homePath()).toString();
    setting.endGroup();
    ui->folderEntry->setText(folderPath);
}

// Save Folder Path into Settings
void settings::saveFolderPathSetting()
{
    QSettings setting("VCFSaver", "vcf");
    setting.beginGroup("settings");
    setting.setValue("folderPath", ui->folderEntry->text());
    setting.endGroup();
}

// Pick File Button Clicked Event
void settings::on_vcfFilePickButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::homePath());
    ui->folderEntry->setText(path);
}
