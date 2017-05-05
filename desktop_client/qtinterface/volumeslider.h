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

#ifndef VOLUMESLIDER_H
#define VOLUMESLIDER_H

#include <QSlider>
#include "vlc/audio.h"
#include "vlc/mediaplayer.h"

class QTimer;

class VlcAudio;
class VlcMediaPlayer;


class QtVolumeSlider : public QSlider
{
    Q_OBJECT

public:

    /* VolumeSlider constructor
     * @param   player VlcMediaPlayer -> player object to connect to
     * @param   parent  QWidget -> pointer to parent QWidget
     */
    explicit QtVolumeSlider(VlcMediaPlayer *player, QWidget *parent = 0);

    ~QtVolumeSlider();

public slots:

    /* Returns mute status */
    bool getMute() const;

    /* Toggles mute */
    void setMute();

    /* Returns volume (int) */
    int volume() const;

    /* Set volume for current media
     * @param   volume  int -> volume to set media at
     */
    void setSlider(int volume);

signals:
    /* Signal for mute change */
    void mute(bool muted);

    /* Signal for new volume */
    void setVolume(int volume);

private slots:

    /* Set volume of _vlcAudio object */
    void updateVolume();

private:

    QTimer  *_timer;

    void initQtVolumeSlider();

    VlcAudio *_vlcAudio;
    VlcMediaPlayer *_vlcMediaPlayer;

    bool _muted;
    int _currentVolume;

};

#endif // VOLUMESLIDER_H
