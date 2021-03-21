#!/bin/bash
############################################################################
##
## Copyright (C) 2016 The Qt Company Ltd.
## Contact: https://www.qt.io/licensing/
##
## This file is part of the Boot to Qt meta layer.
##
## $QT_BEGIN_LICENSE:GPL$
## Commercial License Usage
## Licensees holding valid commercial Qt licenses may use this file in
## accordance with the commercial license agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and The Qt Company. For licensing terms
## and conditions see https://www.qt.io/terms-conditions. For further
## information use the contact form at https://www.qt.io/contact-us.
##
## GNU General Public License Usage
## Alternatively, this file may be used under the terms of the GNU
## General Public License version 3 or (at your option) any later version
## approved by the KDE Free Qt Foundation. The licenses are as published by
## the Free Software Foundation and appearing in the file LICENSE.GPL3
## included in the packaging of this file. Please review the following
## information to ensure the GNU General Public License requirements will
## be met: https://www.gnu.org/licenses/gpl-3.0.html.
##
## $QT_END_LICENSE$
##
############################################################################

set -e

ABI="arm-linux-poky-elf-64bit"

printUsage ()
{
    echo "Usage: $0 --env-setup <file-path>" \
         " --creator-base <dir-path>" \
         " --name <basename>" \
         " [--abi <flavour>]" \
         " [--remove]" \
         " [--device <hostname>] "
}

while test -n "$1"; do
  case "$1" in
    "--creator-base")
      shift
      QTCREATOR=$1
      ;;
    "--env-setup")
      shift
      CONFIG=$1
      ;;
    "--name")
      shift
      NAME=$1
      ;;
    "--abi")
      shift
      ABI=$1
      ;;
    "--remove")
      REMOVEONLY=1
      ;;
    "--device")
      shift
      DEVICE_HOSTNAME=$1
      ;;
    *)
      printUsage
      exit 0
      ;;
  esac
  shift
done

if [ ! -f "$CONFIG" ]; then
   echo "ERROR: Environment setup file not found!"
   printUsage
   exit 1
fi

SDKTOOL="${QTCREATOR}/libexec/qtcreator/sdktool"
if [ ! -x ${SDKTOOL} ]; then
    echo "ERROR: Cannot find 'sdktool' from QtCreator!"
    printUsage
    exit 1
fi

if [ -z "${NAME}" ]; then
    echo "ERROR: Name of kit missing!"
    printUsage
    exit 1
fi

if [ -n "${DEVICE_HOSTNAME}" ]; then
    echo "Include device: ${DEVICE_HOSTNAME}" 
else
    echo "Exclude device"
fi

source $CONFIG

QT_VERSION=$(qmake -query QT_VERSION)
BASEID="byos.${NAME}.${QT_VERSION}"
CMAKE_BASE_DIR="${OECORE_NATIVE_SYSROOT}/usr/share/cmake"
CMAKE_TOOLCHAIN_FILE="${CMAKE_BASE_DIR}/OEToolchainConfig.cmake"
CMAKE_TOOLCHAIN_DIR="${CMAKE_BASE_DIR}/OEToolchainConfig.cmake.d"

echo "NAME = ${NAME}"
echo "BASEID = ${BASEID}"
echo "ABI = ${ABI}"

# exit 0

echo "Removing CMake toolchain files"
rm -f "${CMAKE_TOOLCHAIN_DIR}/*.cmake"

echo "Removing toolchain/C"
${SDKTOOL} rmTC --id ProjectExplorer.ToolChain.Gcc:${BASEID}.gcc || true

echo "Removing toolchain/C++"
${SDKTOOL} rmTC --id ProjectExplorer.ToolChain.Gcc:${BASEID}.g++ || true

echo "Removing debugger"
${SDKTOOL} rmDebugger --id ${BASEID}.gdb || true

echo "Removing Qt"
${SDKTOOL} rmQt --id ${BASEID}.qt || true

echo "Removing CMake"
${SDKTOOL} rmCMake --id ${BASEID}.cmake || true

if [ -n "${DEVICE_HOSTNAME}" ]; then
    echo "Removing Device"
    ${SDKTOOL} rmDev --id ${BASEID}.dev || true
fi

echo "Removing kit"
${SDKTOOL} rmKit --id ${BASEID}.kit || true

if [ -n "${REMOVEONLY}" ]; then
    echo "Kit removed: ${NAME}"
    exit 0
fi



echo "Generating ${CMAKE_TOOLCHAIN_DIR}/OEQt5Toolchain.cmake"
cat << EOF > ${CMAKE_TOOLCHAIN_DIR}/OEQt5Toolchain.cmake
set( OE_QMAKE_PATH_EXTERNAL_HOST_BINS "${OE_QMAKE_PATH_HOST_BINS}" )
EOF


echo "Generating ${CMAKE_TOOLCHAIN_DIR}/$NAME.cmake"
cat << EOF > ${CMAKE_TOOLCHAIN_DIR}/$NAME.cmake
set( CMAKE_SYSTEM_NAME "Linux" )
set( CMAKE_C_FLAGS "${CFLAGS}" CACHE STRING "" FORCE )
set( CMAKE_CXX_FLAGS "${CXXFLAGS}"  CACHE STRING "" FORCE )
set( CMAKE_ASM_FLAGS "${CFLAGS}" CACHE STRING "" FORCE )
set( CMAKE_LDFLAGS_FLAGS "${CXXFLAGS}" CACHE STRING "" FORCE )
set( CMAKE_SYSROOT "${OECORE_TARGET_SYSROOT}" )

set( CMAKE_FIND_ROOT_PATH "${OECORE_TARGET_SYSROOT}" )
set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY )

set(CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX "${OE_CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX}")

set(CMAKE_SYSTEM_PROCESSOR "$OECORE_TARGET_ARCH")
EOF



echo "Adding ABI flavour"
${SDKTOOL} addAbiFlavor --flavor poky --oses linux || true

echo "Adding toolchain/C"
${SDKTOOL} \
    addTC \
    --id "ProjectExplorer.ToolChain.Gcc:${BASEID}.gcc" \
    --name "GCC (${NAME})" \
    --path "$(type -p ${CC})" \
    --abi "${ABI}" \
    --language 1

echo "Adding toolchain/C++"
${SDKTOOL} \
    addTC \
    --id "ProjectExplorer.ToolChain.Gcc:${BASEID}.g++" \
    --name "G++ (${NAME})" \
    --path "$(type -p ${CXX})" \
    --abi "${ABI}" \
    --language 2

echo "Adding debugger"
${SDKTOOL} \
    addDebugger \
    --id "${BASEID}.gdb" \
    --name "GDB (${NAME})" \
    --engine 1 \
    --binary "$(type -p ${GDB})" \
    --abis "${ABI}"

echo "Adding Qt"
${SDKTOOL} \
    addQt \
    --id "${BASEID}.qt" \
    --name "${NAME}" \
    --type "Qdb.EmbeddedLinuxQt" \
    --qmake "$(type -p qmake)"

echo "Adding CMake"
${SDKTOOL} \
    addCMake \
    --id "${BASEID}.cmake" \
    --name "CMake ${NAME}" \
    --path "$(type -p cmake)"

if [ -n "${DEVICE_HOSTNAME}" ]; then
    echo "Adding device"
    ${SDKTOOL} \
        addDev \
    --id "${BASEID}.dev" \
    --name "Device ${NAME}" \
    --type 0 \
    --authentication 1 \
    --freePorts "10000-10100" \
    --host "${DEVICE_HOSTNAME}" \
    --keyFile "${HOME}/.ssh/qtc_id" \
    --origin 0 \
    --osType "GenericLinuxOsType" \
    --sshPort 22 \
    --timeout 10 \
    --uname "root"
fi

echo "Adding kit"
${SDKTOOL} \
    addKit \
    --id "${BASEID}.kit" \
    --name "${NAME}" \
    --devicetype "GenericLinuxOsType" \
    --device "${BASEID}.dev" \
    --qt "${BASEID}.qt" \
    --debuggerid "${BASEID}.gdb" \
    --sysroot "${OECORE_TARGET_SYSROOT}" \
    --Ctoolchain "ProjectExplorer.ToolChain.Gcc:${BASEID}.gcc" \
    --Cxxtoolchain "ProjectExplorer.ToolChain.Gcc:${BASEID}.g++" \
    --cmake "${BASEID}.cmake" \
    --cmake-generator "Unix Makefiles:::" \
    --cmake-config "CMAKE_TOOLCHAIN_FILE:FILEPATH=${CMAKE_TOOLCHAIN_FILE}" \
    --cmake-config "CMAKE_MAKE_PROGRAM:FILEPATH=$(type -p make)" \
    --cmake-config "CMAKE_CXX_COMPILER:FILEPATH=$(type -p ${CXX})" \
    --cmake-config "CMAKE_C_COMPILER:FILEPATH=$(type -p ${CC})"

echo "Configured Qt Creator with new kit: ${NAME}"
