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

#ifndef MUTEBUTTON_H
#define MUTEBUTTON_H

#include <QPushButton>
#include <QTimer>

#include "vlc/mediaplayer.h"
#include "vlc/audio.h"

class VlcMediaPlayer;

class QtMuteButton : public QPushButton
{
    Q_OBJECT

public:

    explicit QtMuteButton(VlcMediaPlayer *player, QWidget *parent = 0);

    ~QtMuteButton();

private slots:

    void muteMedia();

    void updateIcon();

private:

    void initQtMuteButton();

    VlcMediaPlayer *_vlcMediaPlayer;

    VlcAudio       *_vlcAudio;

    QTimer         *_timer;

};

#endif // MUTEBUTTON_H
