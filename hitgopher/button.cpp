#include "button.h"

//! [0]
Button::Button(int flag,QWidget *parent)
    : QToolButton(parent),
      m_flag(flag)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}
QSize Button::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}
