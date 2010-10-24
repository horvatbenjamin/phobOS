#include "system.h"

unsigned long _uptime_ = 0;
unsigned long _timer_ticks_ = 0;
#define _HZ_ 100

void irq0_handler(struct regs *r){
	_timer_ticks_++;
	if(_timer_ticks_%_HZ_ ==0) _uptime_++;
};

void set_timer_freq(int hz){
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outportb(0x43, 0x36);             /* Set our command byte 0x36 */
    outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
};

void timer_install(){
	set_timer_freq(_HZ_);
	irq_set_handler(0,irq0_handler);
};

void delay(int secs){
	int ticks=secs*_HZ_;
    unsigned long eticks;
    eticks = _timer_ticks_ + ticks;
    while(_timer_ticks_ < eticks);
};

