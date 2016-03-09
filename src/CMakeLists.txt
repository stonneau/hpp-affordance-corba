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

SET(LIBRARY_NAME ${PROJECT_NAME})
SET(IDL_SOURCES
#  common
  affordance
  )

OMNIIDL_INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/idl)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/src)
FOREACH(IDL ${IDL_SOURCES})
  GENERATE_IDL_CPP (${IDL} ${CMAKE_SOURCE_DIR}/idl/hpp/corbaserver/affordance)
  GENERATE_IDL_PYTHON (${IDL} ${CMAKE_SOURCE_DIR}/idl/hpp/corbaserver/affordance)
#  INSTALL(
#    FILES ${CMAKE_CURRENT_BINARY_DIR}/hpp/corbaserver/affordance/${IDL}.hh
#    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/hpp/corbaserver/affordance/)
#  INSTALL(
#    FILES ${CMAKE_CURRENT_BINARY_DIR}/hpp/corbaserver/affordance/${IDL}_idl.py
#    DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/affordance/
#    )
ENDFOREACH()

ADD_LIBRARY(${LIBRARY_NAME}
  SHARED
  server.cc
  affordance.impl.hh
  affordance.impl.cc
  affordanceSK.cc
  #${CMAKE_CURRENT_BINARY_DIR}/hpp/corbaserver/affordance/affordance_idl.py
)

ADD_DEPENDENCIES (${LIBRARY_NAME} generate_idl_cpp)
ADD_DEPENDENCIES (${LIBRARY_NAME} generate_idl_python)

PKG_CONFIG_USE_DEPENDENCY(${LIBRARY_NAME} hpp-affordance)
PKG_CONFIG_USE_DEPENDENCY(${LIBRARY_NAME} hpp-template-corba)
PKG_CONFIG_USE_DEPENDENCY(${LIBRARY_NAME} hpp-util)

INSTALL(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
#
# search for python
FINDPYTHON()

# search for omniidl
FIND_PROGRAM(OMNIIDL omniidl)
IF(${OMNIIDL} STREQUAL OMNIIDL-NOTFOUND)
  MESSAGE(FATAL_ERROR "cannot find omniidl.")
ENDIF(${OMNIIDL} STREQUAL OMNIIDL-NOTFOUND)

#FOREACH (IDL ${IDL_SOURCES})
#  ADD_CUSTOM_COMMAND(
#    OUTPUT
#    ${CMAKE_CURRENT_BINARY_DIR}/hpp/corbaserver/affordance/${IDL}_idl.py
#    COMMAND ${OMNIIDL} ARGS -bpython -Wbpackage=""
#    ${CMAKE_SOURCE_DIR}/idl/hpp/corbaserver/affordance/${IDL}.idl
#    MAIN_DEPENDENCY
#    ${CMAKE_SOURCE_DIR}/idl/hpp/corbaserver/affordance/${IDL}.idl
#    )
#  SET_SOURCE_FILES_PROPERTIES(
#    ${CMAKE_CURRENT_BINARY_DIR}/hpp/corbaserver/affordance/${IDL}_idl.py
#    GENERATED=ON
#    )
#  INSTALL(
#    FILES
#    ${CMAKE_CURRENT_BINARY_DIR}/${IDL}_idl.py
#    DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/affordance
#    )
#ENDFOREACH()
#INSTALL(
#  FILES
#  ${CMAKE_CURRENT_SOURCE_DIR}/hpp/corbaserver/affordance/__init__.py
#  DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/affordance
#  )
#INSTALL(
#  FILES
#  ${CMAKE_CURRENT_SOURCE_DIR}/hpp/corbaserver/affordance/client.py
#  DESTINATION ${PYTHON_SITELIB}/hpp/corbaserver/affordance
#  )

# Standalone corba server
ADD_EXECUTABLE (hpp-affordance-server hpp-affordance-corba.cc)
TARGET_LINK_LIBRARIES (hpp-affordance-server ${LIBRARY_NAME})
PKG_CONFIG_USE_DEPENDENCY(hpp-affordance-server hpp-affordance)
PKG_CONFIG_USE_DEPENDENCY(hpp-affordance-server hpp-corbaserver)
PKG_CONFIG_USE_DEPENDENCY(hpp-affordance-server hpp-template-corba)
PKG_CONFIG_USE_DEPENDENCY(hpp-affordance-server hpp-util)

INSTALL (TARGETS hpp-affordance-server DESTINATION ${CMAKE_INSTALL_BINDIR})
