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

#include <QtCore/QDebug>
#include <QtCore/QStringList>

#include "vlc/vlc.h"

#include "vlc/vlcinstance.h"

VlcInstance::VlcInstance(const QStringList &args, QObject *parent) :
                            QObject(parent)
{

/* Need to convert QStringList to const char * for passing to new instance
 * as well as getting the number of arguments to pass
 */
    char *argv[args.count()];
          for (int i = 0; i < args.count(); ++i)
              argv[i] = (char *)qstrdup(args.at(i).toUtf8().data());

    /* Create new libvlc instance */
    _libvlcInstance = libvlc_new(args.count(), argv);

}

/* Destructor -> release libvlc instance per API */
VlcInstance::~VlcInstance()
{
    if (_libvlcInstance)
        libvlc_release(_libvlcInstance);
}

/* Returns libvlc instance */
libvlc_instance_t *VlcInstance::libInst_t()
{
    return _libvlcInstance;
}

//
