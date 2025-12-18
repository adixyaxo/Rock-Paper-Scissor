#include <gtk/gtk.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ui.h"

/* ================= GTK WIDGETS ================= */
static GtkWidget *window;
static GtkWidget *text_view;
static GtkWidget *entry;
static GtkTextBuffer *buffer;
static gboolean input_ready = FALSE;
static char input_buffer[512];

/* ================= ANIMATION STATE ================= */
static gdouble win_opacity = 0.0;

/* ================= TEXT TAGS ================= */
static GtkTextTag *tag_body;
static GtkTextTag *tag_prompt;
static GtkTextTag *tag_system;
static GtkTextTag *tag_result;
static GtkTextTag *tag_error;

/* ================= UTIL ================= */
static void scroll_to_bottom(void)
{
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(text_view), &end, 0, FALSE, 0, 0);
}

/* ================= SOUND ================= */
static void play_click_sound(void)
{
    system("ffplay -nodisp -autoexit ./click.mp3 >/dev/null 2>&1 &");
}

void welcome(void)     { system("ffplay -nodisp -autoexit ./welcome.mp3 >/dev/null 2>&1 &"); }
void tie_sound(void)   { system("ffplay -nodisp -autoexit ./tie.mp3 >/dev/null 2>&1 &"); }
void data_sound(void)  { system("ffplay -nodisp -autoexit ./data.mp3 >/dev/null 2>&1 &"); }
void lost_sound(void)  { system("ffplay -nodisp -autoexit ./youlost.mp3 >/dev/null 2>&1 &"); }
void win_sound(void)   { system("ffplay -nodisp -autoexit ./youwon.mp3 >/dev/null 2>&1 &"); }
void victory(void)     { system("ffplay -nodisp -autoexit ./victory.mp3 >/dev/null 2>&1 &"); }
void notvictory(void)  { system("ffplay -nodisp -autoexit ./lost.mp3 >/dev/null 2>&1 &"); }

/* ================= WINDOW FADE ================= */
static gboolean fade_in(gpointer data)
{
    win_opacity += 0.03;
    if (win_opacity >= 1.0) {
        gtk_widget_set_opacity(window, 1.0);
        return FALSE;
    }
    gtk_widget_set_opacity(window, win_opacity);
    return TRUE;
}

/* ================= CSS ================= */
static void load_css(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_css_provider_load_from_data(
        provider,
        "* {"
        "  font-family: 'JetBrains Mono', monospace;"
        "  color: #a20000ff;"
        "}"

        "window {"
        "  background: linear-gradient(180deg, #0b0d12, #07080c);"
        "}"

        "textview {"
        "  background: transparent;"
        "  padding: 20px;"
        "  line-height: 1.6;"
        "}"

        "entry {"
        "  background: rgba(28,32,48,0.95);"
        "  color: #ffffff;"
        "  border-radius: 10px;"
        "  padding: 12px;"
        "  border: 1px solid #3a4060;"
        "}"

        "entry:focus {"
        "  border-color: #9ccfd8;"
        "}",
        -1,
        NULL
    );

    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}


/* ================= TYPOGRAPHY ================= */
static void init_typography(void)
{
    /* Normal text */
    tag_body = gtk_text_buffer_create_tag(
        buffer, "body",
        "foreground", "#000000",
        "size-points", 14.0,
        NULL
    );

    /* Prompt / user input prefix */
    tag_prompt = gtk_text_buffer_create_tag(
        buffer, "prompt",
        "foreground", "#000000",
        "weight", PANGO_WEIGHT_BOLD,
        "size-points", 15.0,
        NULL
    );

    /* System messages / instructions */
    tag_system = gtk_text_buffer_create_tag(
        buffer, "system",
        "foreground", "#000000",
        "style", PANGO_STYLE_ITALIC,
        "size-points", 13.5,
        NULL
    );

    /* Game results / success */
    tag_result = gtk_text_buffer_create_tag(
        buffer, "result",
        "foreground", "#000000",
        "weight", PANGO_WEIGHT_BOLD,
        "size-points", 15.0,
        NULL
    );

    /* Errors / loss */
    tag_error = gtk_text_buffer_create_tag(
        buffer, "error",
        "foreground", "#000000",
        "weight", PANGO_WEIGHT_BOLD,
        "size-points", 14.5,
        NULL
    );
}



/* ================= PRINT HELPERS ================= */
static void printui_typed(const char *text, GtkTextTag *tag)
{
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);

    for (const char *c = text; *c; c++) {
        gtk_text_buffer_insert_with_tags(buffer, &end, c, 1, tag, NULL);
        while (gtk_events_pending())
            gtk_main_iteration_do(FALSE);
        usleep(6000);
    }
    scroll_to_bottom();
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
    gtk_text_buffer_insert_with_tags(buffer, &end, "⸸ ", -1, tag_prompt, NULL);
    gtk_text_buffer_insert_with_tags(buffer, &end, input_buffer, -1, tag_body, NULL);
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

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(box), 12);
    gtk_container_add(GTK_CONTAINER(window), box);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    g_assert(buffer != NULL);
    init_typography();

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), text_view);
    gtk_box_pack_start(GTK_BOX(box), scroll, TRUE, TRUE, 0);

    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Type your input and press Enter");
    gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 0);

    g_signal_connect(entry, "activate", G_CALLBACK(on_enter_pressed), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_widget_set_opacity(window, 0.0);
    g_timeout_add(16, fade_in, NULL);
}

/* ================= PUBLIC PRINT ================= */
void printui(const char *text)
{
    printui_typed(text, tag_body);
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

/* ================= INPUT ================= */
void scanui_int(const char *prompt, int *out)
{
    printui_typed(prompt, tag_system);
    input_ready = FALSE;
    while (!input_ready) gtk_main_iteration_do(FALSE);
    *out = atoi(input_buffer);
}

void scanui_char(const char *prompt, char *out)
{
    printui_typed(prompt, tag_system);
    input_ready = FALSE;
    while (!input_ready) gtk_main_iteration_do(FALSE);
    *out = input_buffer[0];
}

void scanui_str(const char *prompt, char *out, size_t size)
{
    printui_typed(prompt, tag_system);
    input_ready = FALSE;
    while (!input_ready) gtk_main_iteration_do(FALSE);
    snprintf(out, size, "%s", input_buffer);
}

/* ================= CLEAR ================= */
void clearui(void)
{
    GtkTextIter s, e;
    gtk_text_buffer_get_start_iter(buffer, &s);
    gtk_text_buffer_get_end_iter(buffer, &e);
    gtk_text_buffer_delete(buffer, &s, &e);
}

/* ================= LOOP ================= */
void ui_start(void) { gtk_main(); }

void ui_quit(void)  { gtk_main_quit(); }
