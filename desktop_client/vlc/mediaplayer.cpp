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
#include "vlc/media.h"
#include "vlc/vlcinstance.h"
#include "vlc/mediaplayer.h"

#include <iostream>

#include <string>


VlcMediaPlayer::VlcMediaPlayer(VlcInstance *instance) : QObject(instance)
    {
        /* Instantiate vlcMediaPlayer with passed libvlc instance */
        _vlcInstance = instance;

        _libvlcMediaPlayer = libvlc_media_player_new(_vlcInstance->libInst_t());

        _audio = new VlcAudio(this);

    }

VlcMediaPlayer::~VlcMediaPlayer()
    {

        /* free memory of audio object */
        delete _audio;

    }

/* Returns current media player object */
libvlc_media_player_t *VlcMediaPlayer::libMedia_p() const
    {
        return _libvlcMediaPlayer;
    }

libvlc_instance_t *VlcMediaPlayer::libInst_t() const
    {
        return _vlcInstance->libInst_t();
    }

VlcInstance *VlcMediaPlayer::vlcInstance() const
    {
        return _vlcInstance;
    }

/* Returns current audio player object */
VlcAudio *VlcMediaPlayer::audio() const
    {
        return _audio;
    }

/* Returns current media */
VlcMedia *VlcMediaPlayer::currentMedia() const
    {
        return _media;
    }


/* Open media file or stream (needs to be playable)
 * @param   VlcMedia   media -> media object
 * NOTE: This function both opens and PLAYS media file
 * for open only, see VlcMediaPlayer::openOnly()
 */
void VlcMediaPlayer::openAndPlay(VlcMedia *media)
    {
        _media = media;
        libvlc_media_player_set_media(_libvlcMediaPlayer, _media->libMedia_t());
        play();
    }

/* Open media file or stream but do not auto-play
 * @param   VlcMedia    media -> media object
 * Opens but does not play media
 */
void VlcMediaPlayer::openOnly(VlcMedia *media)
    {
        _media = media;
        libvlc_media_player_set_media(_libvlcMediaPlayer, _media->libMedia_t());
    }

void VlcMediaPlayer::openUrl(QString url)
    {
        const char *_url = url.toStdString().c_str();
        libvlc_media_t *urlMedia = libvlc_media_new_location(_vlcInstance->libInst_t(), _url);
        libvlc_media_player_set_media(_libvlcMediaPlayer, urlMedia);
    }

/* Set media position
 * @param   pos float   -> position of playback
 */
void VlcMediaPlayer::setPosition(float pos)
    {
        libvlc_media_player_set_position(_libvlcMediaPlayer, pos);
    }

/* Play media if possible */
void VlcMediaPlayer::play()
    {
        //If videoWidget object exits, get WinId, otherwise initialize
        if (_videoWidget)
            {
                _currentWId = _videoWidget->winId();
            }
        else
            {
                _currentWId = 0;
            }
        //Get WId to use in window
        if (_currentWId)
            {
                #if defined (Q_OS_DARWIN) //OS X
                libvlc_media_player_set_nsobject(_libvlcMediaPlayer, (void *)_currentWId);
                #elif defined (Q_OS_UNIX) //Linux
                libvlc_media_player_set_xwindow(_libvlcMediaPlayer, _currentWId);
                #endif
            }

        //after rendering in window, play
        libvlc_media_player_play(_libvlcMediaPlayer);
    }

/* Pause media if possible */
void VlcMediaPlayer::pause()
    {
        if (!_libvlcMediaPlayer)
            {
                return;
            }

            libvlc_media_player_set_pause(_libvlcMediaPlayer, true);

    }

/* Resume media playback if possible */
void VlcMediaPlayer::resume()
    {
        if (!_libvlcMediaPlayer)
            {
                return;
            }

            libvlc_media_player_set_pause(_libvlcMediaPlayer, false);

    }

/* Stop media if possible */
void VlcMediaPlayer::stop()
    {
        _videoWidget = Q_NULLPTR;
        _currentWId = 0;
        libvlc_media_player_stop(_libvlcMediaPlayer);
    }

/* Set video widget to play inside Qt interface */
void VlcMediaPlayer::setVideoWidget(QtVideoFrame *widget)
    {
        _videoWidget = widget;
    }

/* Get current video widget */
QtVideoFrame *VlcMediaPlayer::videoWidget() const
    {
        return _videoWidget;
    }

/* Get current media state */
Vlc::State VlcMediaPlayer::state() const
    {
        libvlc_state_t state = libvlc_media_player_get_state(_libvlcMediaPlayer);

        return Vlc::State(state);
    }

/* Get current media position */
float VlcMediaPlayer::position() const
{
    return libvlc_media_player_get_position(_libvlcMediaPlayer);
}

