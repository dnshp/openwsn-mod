/**
\brief A CoAP resource which allows an application to GET/SET the state of the
   error LED.
*/

#include "opendefs.h"
#include "gpio.h"
#include "opencoap.h"
#include "packetfunctions.h"
#include "leds.h"
#include "openqueue.h"
#include "debugpins.h"

//=========================== variables =======================================

gpio_vars_t gpio_vars;

const uint8_t gpio_path0[]       = "g";

//=========================== prototypes ======================================

owerror_t gpio_receive(
   OpenQueueEntry_t* msg,
   coap_header_iht*  coap_header,
   coap_option_iht*  coap_options
);
void     gpio_sendDone(
   OpenQueueEntry_t* msg,
   owerror_t error
);

//=========================== public ==========================================

void gpio_init() {
   
   // prepare the resource descriptor for the /l path
   gpio_vars.desc.path0len            = sizeof(gpio_path0)-1;
   gpio_vars.desc.path0val            = (uint8_t*)(&gpio_path0);
   gpio_vars.desc.path1len            = 0;
   gpio_vars.desc.path1val            = NULL;
   gpio_vars.desc.componentID         = COMPONENT_GPIO;
   gpio_vars.desc.discoverable        = TRUE;
   gpio_vars.desc.callbackRx          = &gpio_receive;
   gpio_vars.desc.callbackSendDone    = &gpio_sendDone;
   
   // register with the CoAP module
   opencoap_register(&gpio_vars.desc);
}

//=========================== private =========================================

/**
\brief Called when a CoAP message is received for this resource.

\param[in] msg          The received message. CoAP header and options already
   parsed.
\param[in] coap_header  The CoAP header contained in the message.
\param[in] coap_options The CoAP options contained in the message.

\return Whether the response is prepared successfully.
*/
owerror_t gpio_receive(
      OpenQueueEntry_t* msg,
      coap_header_iht*  coap_header,
      coap_option_iht*  coap_options
   ) {
   owerror_t outcome;
   
   switch (coap_header->Code) {
      case COAP_CODE_REQ_GET:
         // reset packet payload
         msg->payload                     = &(msg->packet[127]);
         msg->length                      = 0;
         
         // add CoAP payload
         packetfunctions_reserveHeaderSize(msg,2);
         msg->payload[0]                  = COAP_PAYLOAD_MARKER;

         if (leds_error_isOn()==1) {
            msg->payload[1]               = '1';
         } else {
            msg->payload[1]               = '0';
         }
            
         // set the CoAP header
         coap_header->Code                = COAP_CODE_RESP_CONTENT;
         
         outcome                          = E_SUCCESS;
         break;
      
      case COAP_CODE_REQ_PUT:
      
         // change the LED's state
         if (msg->payload[0]=='1') {
            debugpins_gpio1_toggle();
         } else if (msg->payload[0]=='2') {
            debugpins_gpio2_toggle();
         } else if (msg->payload[0]=='3') {
            debugpins_gpio3_toggle();
         } else if (msg->payload[0]=='4') {
            debugpins_gpio4_toggle();
         } else {
            leds_error_toggle();
         }
         
         // reset packet payload
         msg->payload                     = &(msg->packet[127]);
         msg->length                      = 0;
         
         // set the CoAP header
         coap_header->Code                = COAP_CODE_RESP_CHANGED;
         
         outcome                          = E_SUCCESS;
         break;
         
      default:
         outcome                          = E_FAIL;
         break;
   }
   
   return outcome;
}

/**
\brief The stack indicates that the packet was sent.

\param[in] msg The CoAP message just sent.
\param[in] error The outcome of sending it.
*/
void gpio_sendDone(OpenQueueEntry_t* msg, owerror_t error) {
   openqueue_freePacketBuffer(msg);
}
