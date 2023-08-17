#ifndef VCF_H
#define VCF_H

#include <QMainWindow>
#include "createvcf.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VCF; }
QT_END_NAMESPACE

class VCF : public QMainWindow
{
    Q_OBJECT

public:
    VCF(QWidget *parent = nullptr);
    ~VCF();

private slots:

    void on_createVCFButton_clicked();

    void on_editbutton_clicked();

    void on_settingsbutton_clicked();

private:
    Ui::VCF *ui;
    CreateVCF *saveVCFdialog;

};
#endif // VCF_H
