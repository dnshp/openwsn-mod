/**
\brief A CoAP resource which allows an application to GET/SET the state of the
   error LED.
*/

#include "opendefs.h"
#include "pwm.h"
#include "opencoap.h"
#include "packetfunctions.h"
#include "debugpins.h"
#include "leds.h"
#include "openqueue.h"
#include "opentimers.h"

//=========================== variables =======================================

pwm_vars_t pwm_vars;

const uint8_t pwm_path0[]       = "p";

//=========================== prototypes ======================================

owerror_t pwm_receive(
   OpenQueueEntry_t* msg,
   coap_header_iht*  coap_header,
   coap_option_iht*  coap_options
);
void     pwm_sendDone(
   OpenQueueEntry_t* msg,
   owerror_t error
);

//=========================== public ==========================================

void pwm_init() {
   
   // prepare the resource descriptor for the /l path
   pwm_vars.desc.path0len            = sizeof(pwm_path0)-1;
   pwm_vars.desc.path0val            = (uint8_t*)(&pwm_path0);
   pwm_vars.desc.path1len            = 0;
   pwm_vars.desc.path1val            = NULL;
   pwm_vars.desc.componentID         = COMPONENT_PWM;
   pwm_vars.desc.discoverable        = TRUE;
   pwm_vars.desc.callbackRx          = &pwm_receive;
   pwm_vars.desc.callbackSendDone    = &pwm_sendDone;
   
   // register with the CoAP module
   opencoap_register(&pwm_vars.desc);

   debugpins_init();
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
owerror_t pwm_receive(
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
         if (msg->payload[0]=='1') { //turn 0
            debugpins_exp_set(TIME_TICS, 655, 10);
         } else if (msg->payload[0]=='2') { //turn 90
            debugpins_exp_set(TIME_TICS, 655, 33);
         } else if (msg->payload[0]=='3') { //turn 180
            debugpins_exp_set(TIME_TICS, 655, 100);
         } else {
            debugpins_exp_clr();
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
void pwm_sendDone(OpenQueueEntry_t* msg, owerror_t error) {
   openqueue_freePacketBuffer(msg);
}
