#ifndef __GPIO_H
#define __GPIO_H

/**
\addtogroup AppCoAP
\{
\addtogroup gpio
\{
*/

#include "opencoap.h"

//=========================== define ==========================================

//=========================== typedef =========================================

//=========================== variables =======================================

typedef struct {
   coap_resource_desc_t desc;
} gpio_vars_t;

//=========================== prototypes ======================================

void gpio_init(void);

/**
\}
\}
*/

#endif
