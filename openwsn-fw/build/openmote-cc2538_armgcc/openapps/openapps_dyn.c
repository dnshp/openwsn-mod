#include "opendefs.h"

#include "opencoap.h"
#include "c6t.h"
#include "cinfo.h"
#include "cleds.h"
#include "cwellknown.h"
#include "gpio.h"
#include "rrt.h"
#include "techo.h"
#include "uecho.h"
#include "uinject.h"
#include "userialbridge.h"

void openapps_init(void) {
   opencoap_init();
   c6t_init();
   cinfo_init();
   cleds__init();
   cwellknown_init();
   gpio_init();
   rrt_init();
   techo_init();
}