#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>
#include <QtCore>

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();

private slots:
    void on_saveButton_clicked();

    void on_vcfFilePickButton_clicked();

private:
    Ui::settings *ui;

    void loadFolderFromSetting();

    void saveFolderPathSetting();

public:
    void saveSettings();

    void loadSettings(QString foreground_color);

};

#endif // SETTINGS_H
