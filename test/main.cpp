/************************************************************************************
#   QFieldValidator: A simple but usefull field validation library
#
#   Copyright 2018-2019 by Targoman Intelligent Processing <http://tip.co.ir>
#
#   QFieldValidator is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Lesser General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   QFieldValidator is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public License
#   along with Targoman. If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/
/**
 * @author S. Mehran M. Ziabary <ziabary@targoman.com>
 */


#include <iostream>
#include <unistd.h>
#include <QtDebug>

#include "QFieldValidator.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc); Q_UNUSED(argv);

    QFieldValidator v;


    qDebug()<<v.notEmpty().isValid("a");

    /*qDebug()<<v.md5().isValid("ffsdfdsfdsf", "fdfds");
    qDebug()<<v.errorMessage();v.reset();
    qDebug()<<v.md5().isValid("abcderf");
    qDebug()<<v.errorMessage();v.reset();
    qDebug()<<v.hex().isValid("abcdef","dfds");
    qDebug()<<v.errorMessage();v.reset();
    */
    return 0;
}


