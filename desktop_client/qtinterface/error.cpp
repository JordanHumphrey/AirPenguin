/*This file is part of AirPenguin.

    AirPenguin is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AirPenguin is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with AirPenguin.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "qtinterface/error.h"
#include <QAbstractButton>
#include <QGraphicsEffect>
#include <QPropertyAnimation>

QtError::QtError(QString errMsg, QWidget *parent)
                                   : QMessageBox(parent),
                                    _errMsg(errMsg)
{
    initQtError();
}

QtError::~QtError(){}

void QtError::initQtError()
{

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setText(_errMsg);
    this->setIcon(QMessageBox::Critical);
    this->setStandardButtons(QMessageBox::Ok);
    this->button(QMessageBox::Ok)->animateClick(2000);

    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(eff);
    QPropertyAnimation *anim = new QPropertyAnimation(eff, "opacity");
    anim->setDuration(10000);
    anim->setStartValue(1);
    anim->setEndValue(0);
    anim->setEasingCurve(QEasingCurve::OutQuart);
    anim->start(QPropertyAnimation::DeleteWhenStopped);
    this->exec();

    QTimer::singleShot(2000, this, SLOT(hide()));
}

void QtError::hide()
{
    this->close();
}

void QtError::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    QPen pen(Qt::black, 3);
    painter.setPen(pen);
    painter.setBrush(QColor(255,40,40,150));
    painter.drawRect(0,0,width(),height());
}
