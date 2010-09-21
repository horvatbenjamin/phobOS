#ifndef __SCREEN_H
#define __SCREEN_H

void cls();
void putch(unsigned char c);
void puts(unsigned char *str);
void settextcolor(unsigned char forecolor, unsigned char backcolor);
void init_video();

#endif
