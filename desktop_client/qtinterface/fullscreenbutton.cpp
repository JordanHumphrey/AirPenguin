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

#include <QPushButton>
#include <QIcon>
#include <QStyle>

#include "qtinterface/fullscreenbutton.h"

QtFullscreenButton::QtFullscreenButton(QWidget *parent)
                                      : QPushButton(parent)
{
    initQtFSButton();
}

QtFullscreenButton::~QtFullscreenButton()
{

}

void QtFullscreenButton::initQtFSButton()
{
    QSize buttonSize(20,20);
    this->setFixedSize(buttonSize);
    this->setIcon(QIcon(":/fsbuttonLight.png"));

    connect(this, SIGNAL(clicked(bool)), this, SLOT(toggleFullscreen()));
}

void QtFullscreenButton::toggleFullscreen()
{
    emit emitFullscreen();
}
