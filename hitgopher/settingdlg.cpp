#include "settingdlg.h"
#include "ui_settingdlg.h"

SettingDlg::SettingDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDlg)
{
    ui->setupUi(this);
}

SettingDlg::~SettingDlg()
{
    delete ui;
}

void SettingDlg::setSettings(const std::tuple<int, int,int> &tSets)
{
    ui->spinBox_rows->setValue(std::get<0>(tSets));
    ui->spinBox_cols->setValue(std::get<1>(tSets));
    ui->spinBox_timer->setValue(std::get<2>(tSets));
    m_tPreSets = tSets;
}

void SettingDlg::on_pushButton_ok_clicked()
{
    std::tuple<int,int,int> tSets;
    std::get<0>(tSets) = ui->spinBox_rows->value();
    std::get<1>(tSets) = ui->spinBox_cols->value();
    std::get<2>(tSets) = ui->spinBox_timer->value();
    if(m_tPreSets != tSets)
    {
        emit settings(tSets);
    }
    QDialog::accept();
}
