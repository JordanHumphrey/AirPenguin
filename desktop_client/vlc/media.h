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

#ifndef MEDIA_H
#define MEDIA_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>

#include "vlc/vlcinstance.h"
#include "vlc/vlc.h"
#include "vlc/state.h"

class VlcMedia //: public QObject
{

public:

    /* Constructor for new media instance from local
     * @param   location    QString (const) -> address of media
     * @param   localFile   bool    -> in application directory or url
     * @param   instace     VlcInstance -> Instance of vlc player
     */
    explicit VlcMedia(QString &currentLocation,
                      bool local,
                      VlcInstance *instance);

    /* Destructor */
    ~VlcMedia();

    /* return libvlc struct */
    libvlc_media_t *libMedia_t() const;

    /* Get current media state */
    Vlc::State state() const;

private:

    libvlc_media_t *_libvlcMedia;

    QString _currentLocation;

};

#endif // MEDIA_H
