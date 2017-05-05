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

#include <QtCore/QDebug>
#include <QtCore/QDir>

#include <iostream>

#include "vlc/vlc.h"

#include "vlc/media.h"
#include "vlc/vlcinstance.h"

/* Media file containing media for load
 * @param   &location QString -> address of Qstring with filepath or url
 * @param   localFile bool     -> local files are handled differently than
 *                                urls in player media instantiation
 * @param   instance  VlcInstance-> instance of vlcplayer
 */
VlcMedia::VlcMedia(QString &currentLocation, bool local, VlcInstance *instance)
                  //: QObject(instance)
{
    _currentLocation = currentLocation;

    if (local)
    {
        //toUtf8().data() creates char pointer to pass to libvlc API
        _libvlcMedia = libvlc_media_new_path(instance->libInst_t(), _currentLocation.toUtf8().data());
    }
    else
    {
        //libvlc_media_new_location call needed for url playback (remote)
        _libvlcMedia = libvlc_media_new_location(instance->libInst_t(), _currentLocation.toUtf8().data());
    }
}

/* Release the media object from the vlc player */
VlcMedia::~VlcMedia()
{
    libvlc_media_release(_libvlcMedia);
}

/* Return libvlc_media_t struct */
libvlc_media_t *VlcMedia::libMedia_t() const
{
    return _libvlcMedia;
}

/* Return the state of the vlcmediaplayer (check settings for states) */
Vlc::State VlcMedia::state() const
{
    libvlc_state_t state = libvlc_media_get_state(_libvlcMedia);

    return Vlc::State(state);
}




