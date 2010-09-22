#ifndef __SCREEN_H
#define __SCREEN_H

void cls();
void putch(const char c);
void puts(char *str);
void settextcolor(unsigned char forecolor, unsigned char backcolor);
void init_video();

#endif
