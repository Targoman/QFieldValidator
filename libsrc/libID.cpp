/**********************************************************************************
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
 ********************************************************************************/
/**
 * @author S.Mehran M.Ziabary <ziabary@targoman.com>
 * @author Kambiz Zandi <kambizzandi@gmail.com>
 */

#include "libQFieldValidator/Exceptions.h"
#include "libQFieldValidator/QFieldValidator.h"
//Above files are included to be checked by compiler

#define TARGOMAN_STR_VALUE(_arg)    #_arg
#define TARGOMAN_M2STR(_Macro)      TARGOMAN_STR_VALUE(_Macro)

#ifdef TARGOMAN_SHOW_DEBUG
    #define TARGOMAN_LIBRARY_VERSION \
    extern "C" std::string getTargomanLibVersion() { \
      return std::string("Version: ") + \
             std::string(TARGOMAN_M2STR(PROJ_VERSION)) + \
             std::string(" [DEBUG] Last Build: ") + \
             std::string(__DATE__);}
#else
    #define TARGOMAN_LIBRARY_VERSION \
    extern "C" std::string getTargomanLibVersion() { \
      return std::string("Version: ") + \
             std::string(TARGOMAN_M2STR(PROJ_VERSION)) + \
             std::string(" [RELEASE] Last Build: ") + \
             std::string(__DATE__);}
#endif

//Macro used to export Library information
TARGOMAN_LIBRARY_VERSION
