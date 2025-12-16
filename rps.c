#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
this is the gui logic made using ai importing the library of gtk in use in the c language 
this is made using chatgpt ai 


┌──────────────────────────────┐
│ Rock Paper Scissors (GTK)    │
│ ┌──────────────────────────┐ │
│ │ Game log (read-only)     │ │
│ │ Computer: ...            │ │
│ │ You: rock                │ │
│ │ Result: You win          │ │
│ └──────────────────────────┘ │
│ ┌──────────────────────────┐ │
│ │ Type: rock / paper / ... │ │
│ └──────────────────────────┘ │
│        [ Play ]               │
└──────────────────────────────┘


*/



GtkWidget *text_view;
GtkWidget *entry;

// ---------------- Game Logic ----------------
int getComputerChoice() {
    return rand() % 3;
}

int decideWinner(int user, int computer) {
    if (user == computer) return 0;
    if ((user == 0 && computer == 2) ||
        (user == 1 && computer == 0) ||
        (user == 2 && computer == 1))
        return 1;
    return -1;
}

// ---------------- Helpers ----------------
void append_text(const char *msg) {
    GtkTextBuffer *buffer =
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, msg, -1);
    gtk_text_buffer_insert(buffer, &end, "\n", -1);
}

// ---------------- Button Handler ----------------
void on_play_clicked(GtkWidget *widget, gpointer data) {
    const char *input = gtk_entry_get_text(GTK_ENTRY(entry));
    int userChoice = -1;

    if (g_ascii_strcasecmp(input, "rock") == 0)
        userChoice = 0;
    else if (g_ascii_strcasecmp(input, "paper") == 0)
        userChoice = 1;
    else if (g_ascii_strcasecmp(input, "scissors") == 0)
        userChoice = 2;
    else {
        append_text("❌ Invalid input. Type rock, paper or scissors.");
        return;
    }

    int compChoice = getComputerChoice();
    int result = decideWinner(userChoice, compChoice);

    const char *choices[] = {"Rock", "Paper", "Scissors"};

    char buffer[256];
    sprintf(buffer, "🧍 You: %s", choices[userChoice]);
    append_text(buffer);

    sprintf(buffer, "🤖 Computer: %s", choices[compChoice]);
    append_text(buffer);

    if (result == 1)
        append_text("🎉 Result: You Win!");
    else if (result == -1)
        append_text("😢 Result: You Lose!");
    else
        append_text("😐 Result: Draw!");

    append_text("----------------------------");

    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

// ---------------- MAIN ----------------
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    srand(time(NULL));

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Rock Paper Scissors");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Main container
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 12);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Text view (game log)
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);

    PangoFontDescription *font =
        pango_font_description_from_string("Monospace 11");
    gtk_widget_override_font(text_view, font);

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), text_view);
    gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 0);

    // Entry
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry),
                                   "Type rock, paper or scissors");
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    // Button
    GtkWidget *button = gtk_button_new_with_label("Play");
    gtk_widget_set_margin_top(button, 5);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    g_signal_connect(button, "clicked",
                     G_CALLBACK(on_play_clicked), NULL);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
