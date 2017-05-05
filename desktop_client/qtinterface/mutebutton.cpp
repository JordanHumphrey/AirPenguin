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

#include <QIcon>
#include <QStyle>

#include "qtinterface/mutebutton.h"

QtMuteButton::QtMuteButton(VlcMediaPlayer *player, QWidget *parent)
                           : QPushButton(parent),
                             _vlcMediaPlayer(player)
{
    initQtMuteButton();
}

QtMuteButton::~QtMuteButton()
{

}

void QtMuteButton::initQtMuteButton()
{
    QSize buttonSize(20, 20);
    this->setFixedSize(buttonSize);
    this->setIcon(QIcon(":/mutebuttonOnLight.png"));

    _vlcAudio = _vlcMediaPlayer->audio();

    _timer = new QTimer();
    _timer->start(100);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateIcon()));

    connect(this, SIGNAL(clicked()), this, SLOT(muteMedia()));
}

void QtMuteButton::muteMedia()
{
    if (!_vlcMediaPlayer->currentMedia())
    {
        this->setIcon(QIcon(":/mutebuttonOnLight.png"));
        return;
    }

    if (_vlcAudio->getMute())
        _vlcAudio->toggleMute();
    else
        _vlcAudio->toggleMute();

}

void QtMuteButton::updateIcon()
{
    if (_vlcAudio->getMute() || _vlcAudio->getVolume() == 0)
        this->setIcon(QIcon(":/mutebuttonOnLight.png"));
    else
        this->setIcon(QIcon(":/mutebuttonOffLight.png"));
}
