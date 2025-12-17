#ifndef UI_H
#define UI_H

#include <stddef.h>

/* UI lifecycle */
void ui_init(int *argc, char ***argv);
void ui_start(void);
void ui_quit(void);

/* Output */
void printui(const char *text);
const char *formatui(const char *fmt, ...);

/* Input */
void scanui_int(const char *prompt, int *out);
void scanui_char(const char *prompt, char *out);
void scanui_str(const char *prompt, char *out, size_t out_size);
void welcome(void);
void victory(void);
void tie_sound(void);
void data_sound(void);
void lost_sound(void);
void win_sound(void);
void notvictory(void);
/* NEW: clear screen */
void clearui(void);

#endif
