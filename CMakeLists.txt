# Copyright (c) 2021 Skyward Experimental Rocketry
# Author: Damiano Amatruda
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

cmake_minimum_required(VERSION 3.16)
project(Mxgui C CXX ASM)

set(KPATH "" CACHE PATH "Path to kernel directory")
file(GLOB KPATH ${KPATH})
if(NOT KPATH)
    message(FATAL_ERROR "Kernel directory not found")
endif()

include(${KPATH}/config/boards.cmake)

foreach(OPT_BOARD ${BOARDS})
    set(DFLAGS -MMD -MP)
    include(${KPATH}/config/options.cmake)

    set(MXGUI_LIBRARY mxgui-${OPT_BOARD})
    add_library(${MXGUI_LIBRARY} STATIC
        display.cpp
        font.cpp
        misc_inst.cpp
        tga_image.cpp
        resourcefs.cpp
        resource_image.cpp
        level2/input.cpp
        level2/application.cpp
        level2/drawing_context_proxy.cpp
        level2/label.cpp
        level2/simple_plot.cpp
        drivers/display_stm3210e-eval.cpp
        drivers/event_stm3210e-eval.cpp
        drivers/display_mp3v2.cpp
        drivers/event_mp3v2.cpp
        drivers/resfs_mp3v2.cpp
        drivers/display_strive.cpp
        drivers/display_st7735.cpp
        drivers/display_oledboard2.cpp
        drivers/event_strive.cpp
        drivers/display_redbull_v2.cpp
        drivers/event_redbull_v2.cpp
        drivers/display_bitsboard.cpp
        drivers/display_sony-newman.cpp
        drivers/event_sony-newman.cpp
        drivers/display_stm32f4discovery.cpp
        drivers/event_stm32f4discovery.cpp
        drivers/display_generic_1bpp.cpp
        drivers/display_generic_4bpp.cpp
        drivers/display_st7735.cpp
    )
    add_library(mxgui::${MXGUI_LIBRARY} ALIAS ${MXGUI_LIBRARY})
    target_include_directories(${MXGUI_LIBRARY} PUBLIC
        ${KPATH}/config
        ${KPATH}/config/${BOARD_INC}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${KPATH}
        ${KPATH}/arch/common
        ${KPATH}/${ARCH_INC}
        ${KPATH}/${BOARD_INC}
    )
    target_compile_options(${MXGUI_LIBRARY} PUBLIC ${DFLAGS} $<$<COMPILE_LANGUAGE:C>:${CFLAGS_BASE}> $<$<COMPILE_LANGUAGE:CXX>:${CXXFLAGS_BASE}> $<$<COMPILE_LANGUAGE:ASM>:${AFLAGS_BASE}>)
    target_compile_definitions(${MXGUI_LIBRARY} PUBLIC MXGUI_LIBRARY)
endforeach()
