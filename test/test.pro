################################################################################
#   QBuildSystem
#
#   Copyright(c) 2021 by Targoman Intelligent Processing <http://tip.co.ir>
#
#   Redistribution and use in source and binary forms are allowed under the
#   terms of BSD License 2.0.
################################################################################

HEADERS +=

# +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-#
SOURCES += \
    main.cpp \

LIBS += \
    -lprotobuf \
    -lphonenumber \

################################################################################
include($$QBUILD_PATH/templates/testConfigs.pri)

!exists(/usr/lib64/libphonenumber.so*) {
    error (**** Unable to find linphonenumber.so ****\n\
    zypper ar -f https://download.opensuse.org/repositories/devel:/libraries:/c_c++/openSUSE_Leap_15.2/ devel_libraries\n\
    zypper install libphonenumber8 libphonenumber-devel)
}
