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

#ifndef ARGS_H
#define ARGS_H

#include <QString>
#include <QStringList>

#define RTSP_PORT "8080"

class VlcArgs
{

public:

    explicit VlcArgs(QString hostAddr, QString rtspAddress,
                                       QString port, QString sdpName,
                                                     QString networkSettings);

    //TODO: Write constructor for local file arguments
    VlcArgs();

    ~VlcArgs();

    /* Returns QStringList of arguments for player */
    QStringList list();

private:

    QStringList _argsList;
    QString     _hostAddr;
    QString     _rtspAddress;
    QString     _udpAddress;
    QString     _port;
    QString     _sdpName;
    QString     _networkSettings;

};
#endif // ARGS_H
