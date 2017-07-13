/**
DO NOT EDIT DIRECTLY!!

This file was 'objectified' by SCons as a pre-processing
step for the building a Python extension module.

This was done on 2017-06-19 21:16:32.688990.
*/
#ifndef __SF0_H
#define __SF0_H

/**
\addtogroup MAChigh
\{
\addtogroup sf0
\{
*/

#include "Python.h"

#include "opendefs_obj.h"

//=========================== define ==========================================

//=========================== typedef =========================================

typedef struct {
   uint8_t numAppPacketsPerSlotFrame;
   uint8_t backoff;
} sf0_vars_t;

//=========================== module variables ================================

#include "openwsnmodule_obj.h"
typedef struct OpenMote OpenMote;

//=========================== prototypes ======================================

// admin
void sf0_init(OpenMote* self);
// notification from sixtop
void sf0_notif_addedCell(OpenMote* self);
void sf0_notif_removedCell(OpenMote* self);
// notification from schedule
void sf0_notifyNewSlotframe(OpenMote* self);
void      sf0_appPktPeriod(uint8_t numAppPacketsPerSlotFrame);

void sf0_setBackoff(OpenMote* self, uint8_t value);
/**
\}
\}
*/

#endif
