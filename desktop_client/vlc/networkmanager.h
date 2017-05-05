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

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <list>
#include <string>
#include <QUdpSocket>

typedef struct  s_packet {
    uint16_t    port;
    char        name[20];
}               t_packet;

typedef struct s_AirPenguin {
    std::string name;
    std::string ip;
    int         port;
}               t_AirPenguin;

class NetworkManager
{
public:
    virtual                         ~NetworkManager() {}

    const std::list<t_AirPenguin>&  getAirPenguinList() const;
    bool                            fillAirPenguinList();
    t_AirPenguin const              getDeviceFromName(std::string) const;
    void                            connectToAP(std::string);

    /* Singleton */
    static NetworkManager&          getInstance() {
        static NetworkManager       networkManager;

        return networkManager;
    }

private:
    NetworkManager();

    std::list<t_AirPenguin>     _airPenguins;
    QUdpSocket                  _udpSocket;
};

#endif // NETWORKMANAGER_H
