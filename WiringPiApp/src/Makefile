# SPDX-FileCopyrightText: 2003 Argonne National Laboratory
#
# SPDX-License-Identifier: EPICS

TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================
PROD_SYS_LIBS += wiringPi
#=============================
# Build the IOC application

PROD_IOC = WiringPi
# WiringPi.dbd will be created and installed
DBD += WiringPi.dbd

# WiringPi.dbd will be made up from these files:
WiringPi_DBD += base.dbd
WiringPi_DBD += devWiringPi.dbd

# Include dbd files from all support applications:
#WiringPi_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#WiringPi_LIBS += xxx

# WiringPi_registerRecordDeviceDriver.cpp derives from WiringPi.dbd
WiringPi_SRCS += WiringPi_registerRecordDeviceDriver.cpp
WiringPi_SRCS += devWiringPi.c
# Build the main IOC entry point on workstation OSs.
WiringPi_SRCS_DEFAULT += WiringPiMain.cpp
WiringPi_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#WiringPi_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Link QSRV (pvAccess Server) if available
ifdef EPICS_QSRV_MAJOR_VERSION
    WiringPi_LIBS += qsrv
    WiringPi_LIBS += $(EPICS_BASE_PVA_CORE_LIBS)
    WiringPi_DBD  += PVAServerRegister.dbd
    WiringPi_DBD  += qsrv.dbd
endif

# Finally link to the EPICS Base libraries
WiringPi_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

