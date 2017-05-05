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

#include "player/localplayer.h"
#include "vlc/media.h"
#include "vlc/mediaplayer.h"
#include "vlc/args.h"
#include "vlc/vlcinstance.h"
#include "vlc/state.h"
#include <iostream>

LocalPlayer::LocalPlayer(QString &filePath, VlcArgs *args, bool autoPlay, bool stream, QWidget *parent) :
                                            QWidget(parent),
                                            _filePath(filePath),
                                            _args(args),
                                            _stream(stream),
                                            _autoPlay(autoPlay)



{
    initQtPlayer();
}

LocalPlayer::~LocalPlayer()
{
    _player->stop();

    delete _media;

    delete _player;

    emit playerClosed();
}

void LocalPlayer::initQtPlayer()
{
    /* if we set this inside our application window we do not want a minimum size */
    this->setMinimumSize(800, 600);
    /* Don't rely on parent to delete */
    this->setAttribute(Qt::WA_DeleteOnClose);

    _videoFrame     = new QtVideoFrame(this);

    _instance       = new VlcInstance(_args->list(), this);
    _player         = new VlcMediaPlayer(_instance);
    _posScrubber    = new QtPositionScrubber(_player, this);
    _volSlider      = new QtVolumeSlider(_player, this);
    _playButton     = new QtPlayButton(_player, this);
    _stopButton     = new QtStopButton(_player, this);
    _muteButton     = new QtMuteButton(_player, this);

    _media          = new VlcMedia(_filePath, !_stream, _player->vlcInstance());

    _player->setVideoWidget(_videoFrame);

    connect(_videoFrame, SIGNAL(doubleClicked()), this, SLOT(toggleFullscreen()));

    QBoxLayout *audioLayout = new QVBoxLayout;
    audioLayout->addWidget(_volSlider);
    audioLayout->addWidget(_muteButton);

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->addWidget(_posScrubber);
    controlLayout->addWidget(_stopButton);
    controlLayout->addWidget(_playButton);
    controlLayout->addLayout(audioLayout);
    controlLayout->setAlignment(Qt::AlignHCenter);

    QBoxLayout *mediaLayout = new QHBoxLayout;
    mediaLayout->addWidget(_videoFrame);

    QBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(mediaLayout);
    layout->addLayout(controlLayout);

    setLayout(layout);

    if (_autoPlay)
        _player->openAndPlay(_media);
    else
        _player->openOnly(_media);
}

void LocalPlayer::toggleFullscreen()
{
    if (!_player)
        return;

    if (!this->isFullScreen())
    {
        this->showFullScreen();
    }
    else
    {
        this->showNormal();
    }
}
