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

#ifndef SCRUBBER_H
#define SCRUBBER_H

#include <QSlider>
#include <QTimer>
#include "vlc/mediaplayer.h"

class QTimer;

class VlcMediaPlayer;

class QtPositionScrubber : public QSlider
{
    Q_OBJECT

public:

    /* PositionScrubber constructor
     * @param   player  VlcMediaPlayer -> player object to connect to
     * @param   parent  QWidget -> pointer to parent QWidget
     */
    explicit QtPositionScrubber(VlcMediaPlayer *player, QWidget *parent = 0);

    ~QtPositionScrubber();

public slots:

    /* Returns playback position */
    float playbackPosition() const;

    /* Sets scrubber position */
    void setScrubberPosition(int position);

private slots:
    /* Update playback position of player */
    void updatePlaybackPosition();

    /* Update position of scrubber graphic in player */
    void updateScrubberDisplay();

    /* Click along scrubber bar to change position */
    void clickToPosition();

private:

    void initQtPositionScrubber();

    /* Function to convert float pos->int pos
     * @param   pos float -> position of media playback
     */
    float slideToPlayback(int slidePos);
    int playToSlide();

    VlcMediaPlayer *_vlcMediaPlayer;

    int   _qtSlidePos;
    float _currentPlayPos;

    QTimer  *_timer;
};

#endif // SCRUBBER_H
