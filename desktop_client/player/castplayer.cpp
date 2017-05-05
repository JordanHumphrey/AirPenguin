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

#include <QWidget>
#include <QtWidgets>
#include <QFrame>
#include <QTimer>

#include "player/castplayer.h"
#include "vlc/media.h"
#include "vlc/mediaplayer.h"
#include "vlc/args.h"
#include "vlc/vlcinstance.h"
#include "vlc/state.h"

CastPlayer::CastPlayer(QString filePath, VlcArgs *args, bool autoPlay, QWidget *parent) :
                                            QDockWidget(parent),
                                            _filePath(filePath),
                                            _autoPlay(autoPlay)
{
    initQtPlayer(args);
}

CastPlayer::~CastPlayer()
{
    _player->stop();

    delete _media;

    delete _player;

    emit playerClosed();
}

void CastPlayer::initQtPlayer(VlcArgs *args)
{
    /* if we set this inside our application window we do not want a minimum size */
    this->setFixedSize(150, 90);
    /* Delete next event loop*/
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setAttribute(Qt::WA_TranslucentBackground);

    _videoFrame = new QtVideoFrame(this);

    _layout = new QWidget();

    _instance       = new VlcInstance(args->list(), this);
    _player         = new VlcMediaPlayer(_instance);
    _playButton     = new QtPlayButton(_player, this);
    _stopButton     = new QtStopButton(_player, this);
    _media          = new VlcMedia(_filePath, true, _instance);

    _player->setVideoWidget(_videoFrame);

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->addWidget(_stopButton);
    controlLayout->addWidget(_playButton);

    QBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(controlLayout);

    _layout->setLayout(layout);

    this->setWidget(_layout);

    this->setAllowedAreas(Qt::RightDockWidgetArea);

    if (_autoPlay)
        _player->openAndPlay(_media);
    else
        _player->openOnly(_media);
}

/* Background coloring */
void CastPlayer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(250,250,250,240));
    painter.drawRect(0,0,width(),height());
}

