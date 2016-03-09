# Copyright (c) 2016 CNRS
# Author: Anna Seppala
#
# This file is part of hpp-corbaserver.
# hpp-corbaserver is free software: you can redistribute it
# and/or modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation, either version
# 3 of the License, or (at your option) any later version.
#
# hpp-corbaserver is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Lesser Public License for more details.  You should have
# received a copy of the GNU Lesser General Public License along with
# hpp-corbaserver.  If not, see
# <http://www.gnu.org/licenses/>.

# Requires at least CMake 2.6 to configure the package.
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CXX_DISABLE_WERROR true)

INCLUDE(cmake/base.cmake)
INCLUDE(cmake/cpack.cmake)
INCLUDE(cmake/idl.cmake)
INCLUDE(cmake/python.cmake)

SET(PROJECT_NAME hpp-affordance-corba)
SET(PROJECT_DESCRIPTION "Corba server for Humanoid Path Planner Affordance applications")
SET(PROJECT_URL "")
SET(${PROJECT_NAME}_HEADERS

  include/hpp/corbaserver/affordance/fwd.hh
  include/hpp/corbaserver/affordance/server.hh
#  include/hpp/affordance/client.hh
  )

SET(CUSTOM_HEADER_DIR hpp/corbaserver/affordance)

SETUP_PROJECT ()

# Activate hpp-util logging if requested
SET (HPP_DEBUG FALSE CACHE BOOL "trigger hpp-util debug output")
IF (HPP_DEBUG)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHPP_DEBUG")
ENDIF()

# Dependencies
ADD_REQUIRED_DEPENDENCY("hpp-core >= 3")
ADD_REQUIRED_DEPENDENCY("hpp-model-urdf >= 3")
ADD_REQUIRED_DEPENDENCY("omniORB4 >= 4.1.4")
ADD_REQUIRED_DEPENDENCY("hpp-constraints >= 3")
ADD_REQUIRED_DEPENDENCY("hpp-model >= 3")
ADD_REQUIRED_DEPENDENCY("hpp-affordance")
ADD_REQUIRED_DEPENDENCY("hpp-template-corba")
ADD_REQUIRED_DEPENDENCY("hpp-util")
# This dependency ensures us that the intermediate __init__.py files are
# already installed.
ADD_REQUIRED_DEPENDENCY("hpp-corbaserver >= 2.1")
# Make sure that python submodule is installed in the same prefix as module.
IF (NOT ${HPP_CORBASERVER_PREFIX} STREQUAL ${CMAKE_INSTALL_PREFIX})
  MESSAGE(WARNING
    "  THIS PACKAGE SHOULD BE INSTALLED IN THE SAME PREFIX AS HPP-CORBASERVER,\n"
    "  SINCE IT INSTALLS A PYTHON SUBMODULE OF HPP.CORBASERVER.")
  MESSAGE("CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")
  MESSAGE("HPP_CORBASERVER_PREFIX=${HPP_CORBASERVER_PREFIX}")
ENDIF()

PKG_CONFIG_APPEND_LIBS(${PROJECT_NAME})

ADD_SUBDIRECTORY(src)

SETUP_PROJECT_FINALIZE()
SETUP_PROJECT_CPACK()
