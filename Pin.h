#ifndef Pin_h
#define Pin_h

#include "Arduino.h"

#define PIN_PREVIOUS_STATE(a) (a>>1)&1
#define PIN_CURRENT_STATE(a) a&1
#define PIN_CHANGE(a) ((a>>1)&1)^(a&1)
#define PIN_RISING(a) (((a>>1)&1)^(a&1))&(a&1)
#define PIN_FALLING(a) (((a>>1)&1)^(a&1))&(~a&1)

class Pin{
  private:
  unsigned long state_changed_time;
  uint8_t prev_state, curr_state, _prev_state;
  uint8_t pno, pty;
  
  public:
  uint16_t DebounceTime;
  Pin(uint8_t pin_number, uint8_t pin_type);
  Pin(uint8_t pin_number, uint8_t pin_type, uint16_t debounce_time);
  /*
  @funcname : State
  @param: nil
  @description: 
    this will find the state of the pin, HIGH or LOW
    this will also include debouncing method.
  @return:
   uint8_t :  bit 0 gives the current state 
              bit 1 gives the previous state
  */
  uint8_t State();
  /*
  @funcname: PinNumber
  @param : none
  @description:
	this will return the pin number 
  @return:
	pin number
  */
  uint8_t PinNumber();
  void setState(uint8_t cs, uint8_t ps);
  /*
  @function: DidRose
  @param: none
  @description:
	return true if rising edge detected
  @return:
	uint8_t: 0 means no rising edge deteced
			 1 means rising edge detected
  */
  uint8_t DidRose();
  /*
  @function: DidFall
  @param: none
  @description:
	return true if falling edge detected
  @return:
	uint8_t: 0 means no falling edge deteced
			 1 means falling edge detected
  */
  uint8_t DidFall();
  /*
  @function: DidChange
  @param: none
  @description:
	return true if falling edge detected
  @return:
	uint8_t: 0 means no edge deteced
			 1 means edge detected
  */
  uint8_t DidChange();
};

#endif