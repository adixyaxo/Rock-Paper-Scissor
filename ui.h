#ifndef UI_H
#define UI_H

void ui_init(int *argc, char ***argv);
void ui_start();
void ui_quit();

void printui(const char *text);  // or const char *format, ... depending on final version
const char *formatui(const char *fmt, ...);
void scanui(const char *prompt, void *out);

#endif
