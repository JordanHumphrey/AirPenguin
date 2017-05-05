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

#include <QNetworkDatagram>
#include <QNetworkAddressEntry>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include "networkmanager.h"
#include "vlc/args.h"


NetworkManager::NetworkManager()
{
}

const std::list<t_AirPenguin>&  NetworkManager::getAirPenguinList() const {
    return _airPenguins;
}


/*
 * This function scan all host interfaces and send
 * message to broadcast address to find an AirPenguin
 */
bool            NetworkManager::fillAirPenguinList() {
    t_packet    readPacket;
    t_packet        packet;
    t_AirPenguin    airPenguin;
    QHostAddress    addr;
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    packet.port = 0;
/*
 * This for loop find all network interfaces and
 * send a packet to each available broadcast address
 */
/*    for (int i = 0; i < interfaces.size(); i++)
    {
        QNetworkInterface item = interfaces.at(i);
        QList<QNetworkAddressEntry> entryList = item.addressEntries();

        std::cout << "Interface: " << interfaces[i].name().toStdString() << std::endl;
        for (int j = 0; j < entryList.size(); j++)
        {
            std::cout << "Item #" << j << std::endl;
            std::cout << "IP : " << entryList.at(j).ip().toString().toStdString() << std::endl;
            std::cout << "Netmask: " << entryList.at(j).netmask().toString().toStdString() << std::endl;
            std::cout << "Broadcast: " << entryList.at(j).broadcast().toString().toStdString() << std::endl;
            if (!entryList.at(j).broadcast().isNull())
            {*/
                std::cout << "Broadcast NOT NULL" << std::endl;
                _udpSocket.writeDatagram((char*)&packet, sizeof(packet), /*entryList.at(j).broadcast()*/ QHostAddress::Broadcast, 49152);
/*            }
            std::cout << " ~~~~~~~~~~~~~ " << std::endl;
        }
        std::cout << " ----------------- " << std::endl;
    }*/
    _airPenguins.clear();
    usleep(1000);
    while (_udpSocket.hasPendingDatagrams())
    {
        memset(&readPacket, 0, sizeof(readPacket));
        memset(&airPenguin, 0, sizeof(airPenguin));
        std::cout << "READ: " << _udpSocket.readDatagram((char*)&readPacket, sizeof(readPacket), &addr, Q_NULLPTR) << std::endl;
        airPenguin.ip.assign(std::to_string(addr.toIPv4Address()));
        airPenguin.name = std::string(readPacket.name);
        airPenguin.port = readPacket.port;
        std::cout << airPenguin.name << " " << airPenguin.ip << " " << airPenguin.port << " - " << addr.toString().toStdString() << std::endl;
        _airPenguins.push_back(airPenguin);
    }
    return true;
}

/*
 * Return a device from the given name
 * If no device found return an empty structure
 */
t_AirPenguin const     NetworkManager::getDeviceFromName(std::string name) const
{
    t_AirPenguin        device;

    memset(&device, 0, sizeof(device));
    for (std::list<t_AirPenguin>::const_iterator it = _airPenguins.begin(); it != _airPenguins.end(); ++it)
    {
        std::cout << name << " --- " << it->name << std::endl;
        if (name.compare(it->name) == 0)
        {
            std::cout << "MATCH" << std::endl;
            device.name = it->name;
            device.ip = it->ip;
            device.port = it->port;
            break;
        }
    }
    std::cout << device.name << " " << device.ip << " " << device.port << std::endl;
    return (device);
}

void                NetworkManager::connectToAP(std::string addr)
{
    t_packet        packet;
    QHostAddress    serverAddr;

    packet.port = atoi(RTSP_PORT);
    serverAddr = QHostAddress(QString::fromStdString(addr));
    this->_udpSocket.writeDatagram((char*)&packet, sizeof(packet), serverAddr, 49152);
}
