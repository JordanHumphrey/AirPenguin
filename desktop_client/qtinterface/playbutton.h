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

#ifndef PLAYBUTTON_H
#define PLAYBUTTON_H

#include <QPushButton>
#include "vlc/mediaplayer.h"

class VlcMediaPlayer;

class QtPlayButton : public QPushButton
{
    Q_OBJECT

public:

    explicit QtPlayButton(VlcMediaPlayer *player, QWidget *parent = 0);

    explicit QtPlayButton(QWidget *parent = 0);

    ~QtPlayButton();

private slots:

    void playMedia();

    void updateIcon();

private:

    void initQtPlayButton();

    VlcMediaPlayer *_vlcMediaPlayer;

    QTimer         *_timer;
};

#endif // PLAYBUTTON_H
