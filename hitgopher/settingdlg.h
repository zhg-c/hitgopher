#ifndef SETTINGDLG_H
#define SETTINGDLG_H

#include <QDialog>
#include <tuple>

namespace Ui {
class SettingDlg;
}

class SettingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDlg(QWidget *parent = nullptr);
    ~SettingDlg();
signals:
    void settings(const std::tuple<int,int,int> &tSets);
public:
    void setSettings(const std::tuple<int,int,int> &tSets);
private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::SettingDlg *ui;
    std::tuple<int,int,int> m_tPreSets;
};

#endif // SETTINGDLG_H
