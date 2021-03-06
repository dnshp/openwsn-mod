/**
DO NOT EDIT DIRECTLY!!

This file was 'objectified' by SCons as a pre-processing
step for the building a Python extension module.

This was done on 2017-06-19 21:16:15.058132.
*/
/**
\brief This project runs the full OpenWSN stack.

\author Thomas Watteyne <watteyne@eecs.berkeley.edu>, August 2010
*/

#include "board_obj.h"
#include "crypto_engine.h"
#include "scheduler_obj.h"
#include "openstack_obj.h"
#include "opendefs_obj.h"

int mote_main(OpenMote* self) {
   
   // initialize
 board_init(self);
   CRYPTO_ENGINE.init();
 scheduler_init(self);
 openstack_init(self);
   
   // indicate
   
   // start
 scheduler_start(self);
   return 0; // this line should never be reached
}

void sniffer_setListeningChannel(uint8_t channel){return;}
