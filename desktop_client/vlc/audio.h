/* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
 * Modified from 02.2017-05.2017 by AirPenguin team (joistjn@san.rr.com)
 * This file is part of AirPenguin.
 *
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

#ifndef AUDIO_H
#define AUDIO_H

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QMap>

#include "vlc/mediaplayer.h"
#include "vlc/vlc.h"
#include "state.h"

class VlcMediaPlayer;

class VlcAudio : public QObject
{
    Q_OBJECT

private:

    libvlc_media_player_t *_libvlcMediaPlayer;

public:
    /* VlcAudio constructor
     * New audio manager for media playback
     * @param   player VlcMediaPlayer -> instance of player
     */
    explicit VlcAudio(VlcMediaPlayer *player);

    /* VlcAudio destructor */
    ~VlcAudio();

    /* Get current volume */
    int getVolume() const;

    /* Get mute state */
    bool getMute() const;

public slots:

    /* Set audio volume */
    void setVolume(int volume);

    /* Toggle mute of player */
    void toggleMute() const;

signals:
    /* Signal when volume changes
     * @param   volume int
     */
    void volumeChangedInt(int volume);

    /* Signal when volume changes (float)
     * @param   volume float
     */
    void volumeChangedFloat(float volume);

    /* Signal when mute status has changed
     * @param   mute bool
     */
    void muteChanged(bool mute);

};

#endif // AUDIO_H
