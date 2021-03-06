#ifndef __DEBUGPINS_H
#define __DEBUGPINS_H

/**
\addtogroup BSP
\{
\addtogroup debugpins
\{

\brief Cross-platform declaration "leds" bsp module.

\author Thomas Watteyne <watteyne@eecs.berkeley.edu>, February 2012.
*/

#include "opentimers.h"

//=========================== define ==========================================

#define PA3_PERIOD_MS 1

//=========================== typedef =========================================

//=========================== variables =======================================
typedef struct {
    opentimer_id_t	timerId;
    uint16_t		counter;
    uint16_t		period;
} PA3_vars_t;

//=========================== prototypes ======================================

void debugpins_init(void);

void debugpins_frame_toggle(void);
void debugpins_frame_clr(void);
void debugpins_frame_set(void);

void debugpins_slot_toggle(void);
void debugpins_slot_clr(void);
void debugpins_slot_set(void);

void debugpins_fsm_toggle(void);
void debugpins_fsm_clr(void);
void debugpins_fsm_set(void);

void debugpins_task_toggle(void);
void debugpins_task_clr(void);
void debugpins_task_set(void);

void debugpins_isr_toggle(void);
void debugpins_isr_clr(void);
void debugpins_isr_set(void);

void debugpins_radio_toggle(void);
void debugpins_radio_clr(void);
void debugpins_radio_set(void);

void debugpins_gpio1_toggle(void);
void debugpins_gpio1_clr(void);
void debugpins_gpio1_set(void);

void debugpins_gpio2_toggle(void);
void debugpins_gpio2_clr(void);
void debugpins_gpio2_set(void);

void debugpins_gpio3_toggle(void);
void debugpins_gpio3_clr(void);
void debugpins_gpio3_set(void);

void debugpins_gpio4_toggle(void);
void debugpins_gpio4_clr(void);
void debugpins_gpio4_set(void);

#ifdef OPENSIM
void debugpins_ka_clr(void);
void debugpins_ka_set(void);

void debugpins_syncPacket_clr(void);
void debugpins_syncPacket_set(void);

void debugpins_syncAck_clr(void);
void debugpins_syncAck_set(void);

void debugpins_debug_clr(void);
void debugpins_debug_set(void);
#endif

/**
\}
\}
*/

#endif
