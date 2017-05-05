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

#ifndef VLCINSTANCE_H
#define VLCINSTANCE_H

#include <QtCore/QObject>

#include "vlc/vlc.h"
#include "vlc/state.h"

class VlcInstance : public QObject
{

    Q_OBJECT

public:

    /* VlcInstance constructor
     * @param   QString args -> list of arguments for instantiation
     * @param   QObject parent -> Instance's parent object
     */
    explicit VlcInstance(const QStringList &args, QObject *parent = 0);

    /* VlcInstance destructor */
    ~VlcInstance();

    /* Returns libvlc instance object */
    libvlc_instance_t *libInst_t();

private:

    libvlc_instance_t *_libvlcInstance;
};

#endif // VLCINSTANCE_H
