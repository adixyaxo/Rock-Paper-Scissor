#include <gtk/gtk.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "ui.h"

/* ================= GTK WIDGETS ================= */
static GtkWidget *window;
static GtkWidget *text_view;
static GtkWidget *entry;
static GtkTextBuffer *buffer;

static gboolean input_ready = FALSE;
static char input_buffer[512];

static void play_click_sound(void)
{
    system("paplay /usr/share/sounds/freedesktop/stereo/message.oga &");
}


/* ================= CSS ================= */
static void load_css(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(
        provider,
        "* {"
        "  font-family: 'JetBrains Mono', 'Monospace';"
        "  font-size: 14px;"
        "}"
        "window {"
        "  background: #0f1117;"
        "}"
        "textview {"
        "  background: #0f1117;"
        "  color: #e6e6e6;"
        "  border: none;"
        "  padding: 12px;"
        "}"
        "entry {"
        "  background: #161925;"
        "  color: #ffffff;"
        "  border-radius: 8px;"
        "  padding: 10px;"
        "  border: 1px solid #2a2f45;"
        "}"
        "entry:focus {"
        "  border-color: #5e81ac;"
        "}"
        ,
        -1,
        NULL
    );

    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

/* ================= CALLBACK ================= */
static void on_enter_pressed(GtkWidget *widget, gpointer data)
{
    const char *text = gtk_entry_get_text(GTK_ENTRY(entry));

    snprintf(input_buffer, sizeof(input_buffer), "%s", text);
    input_ready = TRUE;

    play_click_sound();

    gtk_entry_set_text(GTK_ENTRY(entry), "");

    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);

    gtk_text_buffer_insert(buffer, &end, "➜ ", -1);
    gtk_text_buffer_insert(buffer, &end, input_buffer, -1);
    gtk_text_buffer_insert(buffer, &end, "\n", -1);
    scroll_to_bottom();
}

/* ================= UI INIT ================= */
void ui_init(int *argc, char ***argv)
{
    gtk_init(argc, argv);
    load_css();

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Rock Paper Scissors");
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 12);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    /* -------- Output Area -------- */
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(
        GTK_SCROLLED_WINDOW(scroll),
        GTK_POLICY_NEVER,
        GTK_POLICY_AUTOMATIC
    );
    gtk_container_add(GTK_CONTAINER(scroll), text_view);
    gtk_box_pack_start(GTK_BOX(main_box), scroll, TRUE, TRUE, 0);

    /* -------- Input Area -------- */
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(
        GTK_ENTRY(entry),
        "Type your input and press Enter"
    );
    gtk_box_pack_start(GTK_BOX(main_box), entry, FALSE, FALSE, 0);

    g_signal_connect(entry, "activate", G_CALLBACK(on_enter_pressed), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
}

static void scroll_to_bottom(void)
{
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_view_scroll_to_iter(
        GTK_TEXT_VIEW(text_view),
        &end,
        0.0,
        FALSE,
        0,
        0
    );
}

/* ================= PRINT ================= */
void printui(const char *text)
{
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, text, -1);
    scroll_to_bottom();
}

/* ================= FORMAT ================= */
const char *formatui(const char *fmt, ...)
{
    static char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    return buf;
}

/* ================= SAFE INPUT ================= */
void scanui_int(const char *prompt, int *out)
{
    printui(prompt);
    input_ready = FALSE;

    while (!input_ready)
        gtk_main_iteration_do(FALSE);

    *out = atoi(input_buffer);
}

void scanui_char(const char *prompt, char *out)
{
    printui(prompt);
    input_ready = FALSE;

    while (!input_ready)
        gtk_main_iteration_do(FALSE);

    *out = input_buffer[0];
}

void scanui_str(const char *prompt, char *out, size_t out_size)
{
    printui(prompt);
    input_ready = FALSE;

    while (!input_ready)
        gtk_main_iteration_do(FALSE);

    snprintf(out, out_size, "%s", input_buffer);
}

void clearui(void)
{
    gtk_text_buffer_set_text(buffer, "", -1);
}


/* ================= LOOP ================= */
void ui_start(void)
{
    gtk_main();
}

void ui_quit(void)
{
    gtk_main_quit();
}
