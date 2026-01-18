#!../../bin/linux-aarch64/WiringPi

#- SPDX-FileCopyrightText: 2005 Argonne National Laboratory
#-
#- SPDX-License-Identifier: EPICS

#- You may have to change WiringPi to something else
#- everywhere it appears in this file

< envPaths

## Register all support components
dbLoadDatabase "../../dbd/WiringPi.dbd"
WiringPi_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadRecords("../../db/WiringPiDIO.db","IOCName=RPi")
dbLoadRecords("../../db/WiringPiMode.db","IOCName=RPi")
dbLoadRecords("../../db/WiringPiRB.db","IOCName=RPi")

iocInit()

## Start any sequence programs
#seq sncWiringPi,"user="
