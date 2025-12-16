#ifndef UI_H
#define UI_H

#include <gtk/gtk.h>
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

#endif /* UI_H */
