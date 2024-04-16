# Copyright (C) 2024 by Skyward
#
# This program is free software; you can redistribute it and/or 
# it under the terms of the GNU General Public License as published 
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# As a special exception, if other files instantiate templates or use
# macros or inline functions from this file, or you compile this file
# and link it with other works to produce a work based on this file,
# this file does not by itself cause the resulting work to be covered
# by the GNU General Public License. However the source code for this
# file must still be made available in accordance with the GNU 
# Public License. This exception does not invalidate any other 
# why a work based on this file might be covered by the GNU General
# Public License.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>

cmake_minimum_required(VERSION 3.25)

project(MxGui
    DESCRIPTION "GUI library for the Miosix kernel"
    LANGUAGES C CXX
)

# Load in MXGUI_PATH the project path
set(MXGUI_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Create libraries for each board
include(cmake/boards.cmake)
include(cmake/mxgui_add_board_library.cmake)
foreach(BOARD_NAME ${MXGUI_BOARDS})
    mxgui_add_board_library(${BOARD_NAME})
endforeach()