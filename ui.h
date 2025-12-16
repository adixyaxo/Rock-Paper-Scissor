#ifndef UI_H
#define UI_H

// Initialize GTK window and widgets
void ui_init(int *argc, char ***argv);

// Start GTK loop (non-blocking game safe)
void ui_start();

// UI replacements
void printui(const char *format, ...);
void scanui(const char *format, void *out);
const char *formatui(const char *fmt, ...);

// Cleanup
void ui_quit();

#endif
