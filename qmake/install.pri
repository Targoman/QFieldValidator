################################################################################
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
################################################################################
!contains(CONFIG, no_install) {
    INCLUDE_PREFIX = $$[QT_INSTALL_HEADERS]/
    LIB_PREFIX     = $$[QT_INSTALL_LIBS]
    EXAMPLES_PREFIX= $$[QT_INSTALL_EXAMPLES]

    unix:!isEmpty(PREFIX){
            INCLUDE_PREFIX = $$PREFIX/include/
            contains(QT_ARCH, x86_64){
                LIB_PREFIX     = $$PREFIX/lib64
            } else {
                LIB_PREFIX     = $$PREFIX/lib
            }
    }

    PRJDIR = $${dirname(PWD)}
    for(header, DIST_HEADERS) {
      relPath = $${relative_path($$header, $$PRJDIR)}
      path = $${INCLUDE_PREFIX}/$${dirname(relPath)}
      eval(headers_$${path}.files += $$relPath)
      eval(headers_$${path}.path = $$path)
      eval(INSTALLS *= headers_$${path})
    }

    target = $$TARGET
    target.path = $$LIB_PREFIX

    INSTALLS += target
}





