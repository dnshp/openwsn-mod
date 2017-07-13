/**
DO NOT EDIT DIRECTLY!!

This file was 'objectified' by SCons as a pre-processing
step for the building a Python extension module.

This was done on 2017-06-19 21:16:58.868279.
*/
#ifndef __RADIOTIMER_H
#define __RADIOTIMER_H

/**
\addtogroup BSP
\{
\addtogroup radiotimer
\{

\brief Cross-platform declaration "radiotimer" bsp module.

\author Thomas Watteyne <watteyne@eecs.berkeley.edu>, February 2012.
*/

#include "Python.h"

#include "stdint.h"
#include "board_obj.h"

//=========================== define ==========================================
#ifdef SLOT_FSM_IMPLEMENTATION_MULTIPLE_TIMER_INTERRUPT

enum radiotimer_action_enum {
    // action items
    ACTION_LOAD_PACKET                     = 0x01,
    ACTION_SEND_PACKET                     = 0x02,
    ACTION_RADIORX_ENABLE                  = 0x03,
    ACTION_NORMAL_TIMER                    = 0x04,
    ACTION_TX_SFD_DONE                     = 0x05,
    ACTION_RX_SFD_DONE                     = 0x06,
    ACTION_TX_SEND_DONE                    = 0x07,
    ACTION_RX_DONE                         = 0x08,
    ACTION_ALL_RADIOTIMER_INTERRUPT        = 0x09,
};

#else
#endif

//=========================== typedef =========================================

typedef void (*radiotimer_compare_cbt)(OpenMote* self);
typedef void (*radiotimer_capture_cbt)(OpenMote* self, PORT_TIMER_WIDTH timestamp);

//=========================== variables =======================================

#include "openwsnmodule_obj.h"
typedef struct OpenMote OpenMote;

//=========================== prototypes ======================================

// admin
void radiotimer_init(OpenMote* self);
void radiotimer_setOverflowCb(OpenMote* self, radiotimer_compare_cbt cb);
void radiotimer_setCompareCb(OpenMote* self, radiotimer_compare_cbt cb);
void radiotimer_setStartFrameCb(OpenMote* self, radiotimer_capture_cbt cb);
void radiotimer_setEndFrameCb(OpenMote* self, radiotimer_capture_cbt cb);
void radiotimer_start(OpenMote* self, PORT_RADIOTIMER_WIDTH period);
// direct access
PORT_RADIOTIMER_WIDTH radiotimer_getValue(OpenMote* self);
void radiotimer_setPeriod(OpenMote* self, PORT_RADIOTIMER_WIDTH period);
PORT_RADIOTIMER_WIDTH radiotimer_getPeriod(OpenMote* self);
// compare
#ifdef SLOT_FSM_IMPLEMENTATION_MULTIPLE_TIMER_INTERRUPT
void radiotimer_schedule(OpenMote* self, uint8_t type,PORT_RADIOTIMER_WIDTH offset);
void radiotimer_cancel(OpenMote* self, uint8_t type);
void     radiotimer_setCapture(uint8_t type);
#else
void radiotimer_schedule(OpenMote* self, PORT_RADIOTIMER_WIDTH offset);
void radiotimer_cancel(OpenMote* self);
#endif
// capture
PORT_RADIOTIMER_WIDTH radiotimer_getCapturedTime(OpenMote* self);

// interrupt handlers
kick_scheduler_t radiotimer_isr(OpenMote* self);

/**
\}
\}
*/

#endif
