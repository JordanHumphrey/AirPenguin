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
#include <QtWidgets/QSlider>

#include "qtinterface/scrubber.h"

#define SCRUBBER_RESOLUTION 2000

QtPositionScrubber::QtPositionScrubber(VlcMediaPlayer *player, QWidget *parent)
                                       : QSlider(parent),
                                         _vlcMediaPlayer(player)
{
    initQtPositionScrubber();
}

QtPositionScrubber::~QtPositionScrubber()
{

}

void QtPositionScrubber::initQtPositionScrubber()
{
    /* Timer for updating GUI display */
    _timer = new QTimer();
    /* Start update timer for ui */
    _timer->start(50);

    //Range of scrubber (need to convert float->int
    // before passing setPosition argument)
    this->setOrientation(Qt::Horizontal);
    this->setRange(0, SCRUBBER_RESOLUTION);

    connect(_timer, SIGNAL(timeout()), this, SLOT(updateScrubberDisplay()));
    connect(this, SIGNAL(sliderPressed()), this, SLOT(clickToPosition()));
    connect(this, SIGNAL(sliderMoved(int)), this, SLOT(setScrubberPosition(int)));

}


float QtPositionScrubber::playbackPosition() const
{
    if (!(_vlcMediaPlayer->state() == Vlc::Stopped))
        return 0;
    else
        return _currentPlayPos;
}

void QtPositionScrubber::setScrubberPosition(int position)
{
    _vlcMediaPlayer->setPosition(slideToPlayback(position));
}

void QtPositionScrubber::clickToPosition()
{
    _vlcMediaPlayer->setPosition(slideToPlayback(this->value()));
}

float QtPositionScrubber::slideToPlayback(int slidePos)
{
    if (!_vlcMediaPlayer)
        return 0;

    _qtSlidePos = slidePos;

     return (float) _qtSlidePos / SCRUBBER_RESOLUTION;

}

int QtPositionScrubber::playToSlide()
{
    if (!_vlcMediaPlayer)
        return 0;

    return (int) (_vlcMediaPlayer->position() * SCRUBBER_RESOLUTION);
}

void QtPositionScrubber::updatePlaybackPosition()
{

    if (!_vlcMediaPlayer)
        return;

    _vlcMediaPlayer->setPosition(slideToPlayback(this->value()));
}

void QtPositionScrubber::updateScrubberDisplay()
{
    if (!_vlcMediaPlayer)
        return;

    this->setValue(playToSlide());

}

