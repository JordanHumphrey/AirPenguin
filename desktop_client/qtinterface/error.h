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

#ifndef ERROR_H
#define ERROR_H

#include <QMessageBox>
#include <QPainter>
#include <QTimer>

class QtError : QMessageBox
{
    Q_OBJECT

public:

    explicit QtError(QString errMsg, QWidget *parent=0);

    ~QtError();

private:

    void initQtError();

    void hide();

    void paintEvent(QPaintEvent *event);

    QString         _errMsg;

};

#endif // ERROR_H
