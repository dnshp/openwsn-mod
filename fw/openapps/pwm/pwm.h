#ifndef __PWM_H
#define __PWM_H

/**
\addtogroup AppCoAP
\{
\addtogroup pwm
\{
*/
#include "opencoap.h"
//=========================== define ==========================================

//=========================== typedef =========================================

typedef struct {
   coap_resource_desc_t desc;
} pwm_vars_t;

//=========================== variables =======================================

//=========================== prototypes ======================================

void pwm_init(void);

/**
\}
\}
*/

#endif