/* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
 * Modified from 02.2017-05.2017 by AirPenguin team (joistjn@san.rr.com)
 * This file is part of AirPenguin.

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

#include "vlc/vlc.h"
#include "vlc/audio.h"
#include "vlc/mediaplayer.h"

VlcAudio::VlcAudio(VlcMediaPlayer *player) : QObject(player),
                   _libvlcMediaPlayer(player->libMedia_p())
{}

VlcAudio::~VlcAudio() {}

/* Get current volume
 * Returns volume -> int
 */
int VlcAudio::getVolume() const
{
    int volume = libvlc_audio_get_volume(_libvlcMediaPlayer);

    return volume;
}

/* Get mute state
 * Returns mute state -> bool
 */
bool VlcAudio::getMute() const
{
    bool mute = libvlc_audio_get_mute(_libvlcMediaPlayer);

    return mute;
}

/* Set audio volume
 * @param   volume  int -> Volume to set */
void VlcAudio::setVolume(int volume)
{
    libvlc_audio_set_volume(_libvlcMediaPlayer, volume);

    emit volumeChangedInt(volume);

}

/* Toggle mute of player
 * Some media might not support this */
void VlcAudio::toggleMute() const
{
    libvlc_audio_toggle_mute(_libvlcMediaPlayer);
}
