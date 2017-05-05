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

#include "qtinterface/playbutton.h"

QtPlayButton::QtPlayButton(VlcMediaPlayer *player, QWidget *parent)
                           : QPushButton(parent),
                             _vlcMediaPlayer(player)
{
    initQtPlayButton();
}

QtPlayButton::QtPlayButton(QWidget *parent)
                          : QPushButton(parent),
                            _vlcMediaPlayer(0)
{
    initQtPlayButton();
}

QtPlayButton::~QtPlayButton()
{

}

void QtPlayButton::initQtPlayButton()
{
    QSize buttonSize(40,40);
    this->setFixedSize(buttonSize);
    this->setIcon(QIcon(":/playbuttonLight.png"));

    //timer for button updates
    _timer = new QTimer();
    _timer->start(100);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateIcon()));

    connect(this, SIGNAL(clicked(bool)), this, SLOT(playMedia()));
}

void QtPlayButton::playMedia()
{
    if (!_vlcMediaPlayer->currentMedia())
    {
        this->setIcon(QIcon(":/playbuttonLight.png"));
        return;
    }

    if (_vlcMediaPlayer->state() == Vlc::Paused
    || _vlcMediaPlayer->state() == Vlc::Idle
    || _vlcMediaPlayer->state() == Vlc::Stopped)
        _vlcMediaPlayer->play();
    else
        _vlcMediaPlayer->pause();

}

void QtPlayButton::updateIcon()
{
    if (_vlcMediaPlayer->state() == Vlc::Paused
     || _vlcMediaPlayer->state() == Vlc::Idle
     || _vlcMediaPlayer->state() == Vlc::Stopped)
        this->setIcon(QIcon(":/playbuttonLight.png"));
    else
        this->setIcon(QIcon(":/pausebuttonLight.png"));
}
