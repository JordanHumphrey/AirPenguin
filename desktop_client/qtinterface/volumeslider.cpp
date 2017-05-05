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

#include <QtCore/QTimer>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

#include "qtinterface/volumeslider.h"

QtVolumeSlider::QtVolumeSlider(VlcMediaPlayer * player, QWidget *parent)
                              : QSlider(parent),
                                _vlcAudio(player->audio()),
                                _vlcMediaPlayer(player)
{
    initQtVolumeSlider();
}

QtVolumeSlider::~QtVolumeSlider()
{
    delete _timer;
}

void QtVolumeSlider::initQtVolumeSlider()
{

    _timer = new QTimer(this);
    _timer->start(100);

    this->setOrientation(Qt::Vertical);
    QSize sliderSize(20,80);
    this->setFixedSize(sliderSize);
    this->setRange(0, 100);
    this->setToolTip("Volume");

    connect(_timer, SIGNAL(timeout()), this, SLOT(updateVolume()));
    connect(this, SIGNAL(valueChanged(int)), _vlcAudio, SLOT(setVolume(int)));

}

bool QtVolumeSlider::getMute() const
{
    if (!(_vlcMediaPlayer->state() == Vlc::Buffering
          || _vlcMediaPlayer->state() == Vlc::Playing
          || _vlcMediaPlayer->state() == Vlc::Paused))
        return false;
    else
        return _vlcAudio->getMute();
}

void QtVolumeSlider::setMute()
{
    if (!(_vlcMediaPlayer->state() == Vlc::Buffering
          || _vlcMediaPlayer->state() == Vlc::Playing
          || _vlcMediaPlayer->state() == Vlc::Paused
          || _vlcMediaPlayer->state() == Vlc::Idle))
        return;

    _vlcAudio->toggleMute();

    emit mute(this->getMute());
}

int QtVolumeSlider::volume() const
{
    return _vlcAudio->getVolume();
}

void QtVolumeSlider::setSlider(int volume)
{
    _currentVolume = volume;

    //set position of the slider
    this->setValue(_currentVolume);

    emit setVolume(_currentVolume);
}

void QtVolumeSlider::updateVolume()
{
    if (!_vlcMediaPlayer)
        return;

    if (_vlcMediaPlayer->state() == Vlc::Buffering
            || _vlcMediaPlayer->state() == Vlc::Playing
            || _vlcMediaPlayer->state() == Vlc::Paused)
    {
        _vlcAudio->setVolume(this->volume());

        if (_vlcMediaPlayer->audio()->getMute())
        {
            this->blockSignals(true);
            this->setValue(0);
        }
        else
        {
            this->blockSignals(false);
            this->setValue(_vlcAudio->getVolume());
        }
    }
    else
    {
        this->setValue(0);
    }
}

