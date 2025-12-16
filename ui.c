#include <gtk/gtk.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "ui.h"

/* ---------- GTK WIDGETS ---------- */
static GtkWidget *window;
static GtkWidget *text_view;
static GtkWidget *entry;
static GtkTextBuffer *buffer;

static gboolean input_ready = FALSE;
static char input_buffer[256];

/* ---------- CALLBACK ---------- */
static void on_enter_pressed(GtkWidget *widget, gpointer data)
{
    const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
    strncpy(input_buffer, text, sizeof(input_buffer));
    input_ready = TRUE;

    gtk_entry_set_text(GTK_ENTRY(entry), "");

    // Echo input to log window
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, ">> ", -1);
    gtk_text_buffer_insert(buffer, &end, input_buffer, -1);
    gtk_text_buffer_insert(buffer, &end, "\n", -1);
}

/* ---------- UI INIT ---------- */
void ui_init(int *argc, char ***argv)
{
    gtk_init(argc, argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Rock Paper Scissor");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    /* Text View (Game Log) */
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), text_view);
    gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 5);

    /* Input Entry */
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter your choice...");
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 5);

    g_signal_connect(entry, "activate", G_CALLBACK(on_enter_pressed), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
}

/* ---------- PRINT UI ---------- */
void printui(const char *format, ...)
{
    char text[512];
    va_list args;
    va_start(args, format);
    vsnprintf(text, sizeof(text), format, args);
    va_end(args);

    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, text, -1);
}

/* ---------- SCAN UI ---------- */
void scanui(const char *format, void *out)
{
    input_ready = FALSE;

    while (!input_ready)
        gtk_main_iteration_do(FALSE);

    if (strcmp(format, "%d") == 0)
        *(int *)out = atoi(input_buffer);
    else if (strcmp(format, "%c") == 0)
        *(char *)out = input_buffer[0];
    else if (strcmp(format, "%s") == 0)
        strcpy((char *)out, input_buffer);
}

/* ---------- START LOOP ---------- */
void ui_start()
{
    gtk_main();
}

void ui_quit()
{
    gtk_main_quit();
}
