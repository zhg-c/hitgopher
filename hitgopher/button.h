#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>
class Button : public QToolButton
{
    Q_OBJECT

public:
    explicit Button(int flag,QWidget *parent = nullptr);

    QSize sizeHint() const override;
    int getFlag(){return m_flag;}
private:
    int m_flag;
};

#endif
