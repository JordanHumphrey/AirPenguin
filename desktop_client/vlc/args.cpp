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

#include "vlc/args.h"
#include <QStringList>

/* Command line arguments to pass to vlc instace
 * * For a list of possible arguments see
 * https://wiki.videolan.org/VLC_command-line_help/
 */

/* Constructor for cast args object */
VlcArgs::VlcArgs(QString hostAddr, QString rtspAddress,
                 QString port, QString sdpName, QString networkSettings) :
                   _hostAddr(hostAddr),
                   _rtspAddress(rtspAddress),
                   _port(port),
                   _sdpName(sdpName),
                   _networkSettings(networkSettings)
{
    _argsList << "-vvv"
              << "--sout=#transcode{vcode=h264,vb=2048,acodec=mpga,ab=192,channels=2}:rtp{dst=" + _hostAddr + ",port=" + _port + ",sdp=rtsp"
                    "://" + _rtspAddress + ":" + RTSP_PORT + "/" + _sdpName + "}"
              << _networkSettings;
}

/* TODO: Options for local media playback */
VlcArgs::VlcArgs()
{
    _argsList << "-vv";
}

VlcArgs::~VlcArgs() {}

/* Return QStringList of args */
QStringList VlcArgs::list()
{
    return _argsList;
}
