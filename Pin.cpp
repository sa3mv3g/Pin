#include "Arduino.h"
#include "Pin.h"

Pin::Pin(uint8_t pin_number, uint8_t pin_type): 
	pno(pin_number), 
	pty(pin_type),
	DebounceTime(50),
	state_changed_time(0)
{
  pinMode(pin_number, pin_type);
  if(pin_type == INPUT_PULLUP) prev_state = curr_state = HIGH;
  else if(pin_type == INPUT) prev_state = curr_state = LOW;
}

Pin::Pin(uint8_t pin_number, uint8_t pin_type, uint16_t debounce_time): 
	pno(pin_number), 
	pty(pin_type),
	DebounceTime(debounce_time),
	state_changed_time(0)
{
  pinMode(pin_number, pin_type);
  if(pin_type == INPUT_PULLUP) prev_state = curr_state = HIGH;
  else if(pin_type == INPUT) prev_state = curr_state = LOW;
}

uint8_t Pin::State(){
	uint8_t _curr_state = digitalRead(pno);
	if(_curr_state != _prev_state) state_changed_time = millis();
	if( (millis() - state_changed_time) > DebounceTime){
		//if(curr_state != _curr_state){
		prev_state = curr_state;
		curr_state = _curr_state;
		//}
	}
	_prev_state = _curr_state;
	return (prev_state << 1) | curr_state;
}

uint8_t Pin::PinNumber(){
	return pno;
}
void Pin::setState(uint8_t cs, uint8_t ps){
	prev_state = ps;
	curr_state = cs;
}

uint8_t Pin::DidRose(){
	uint8_t s = State();
	return PIN_RISING(s);
}

uint8_t Pin::DidFall(){
	uint8_t s = State();
	return PIN_FALLING(s);
}
uint8_t Pin::DidChange(){
	uint8_t s = State();
	return PIN_CHANGE(s);
}