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

#include "qtinterface/stopbutton.h"

QtStopButton::QtStopButton(VlcMediaPlayer *player, QWidget *parent)
                           : QPushButton(parent),
                             _vlcMediaPlayer(player)
{
    initQtStopButton();
}

QtStopButton::QtStopButton(QWidget *parent)
                           : QPushButton(parent),
                             _vlcMediaPlayer(0)
{
    initQtStopButton();
}

QtStopButton::~QtStopButton()
{

}

void QtStopButton::initQtStopButton()
{
    QSize buttonSize(40,40);
    this->setFixedSize(buttonSize);
    this->setIcon(QIcon(":/stopbuttonLight.png"));

    connect(this, SIGNAL(clicked(bool)), this, SLOT(stopMedia()));
}

void QtStopButton::stopMedia()
{
    if (!_vlcMediaPlayer)
        return;

    if (_vlcMediaPlayer->state() == Vlc::Playing
     || _vlcMediaPlayer->state() == Vlc::Buffering
     || _vlcMediaPlayer->state() == Vlc::Paused)
        _vlcMediaPlayer->stop();
}
