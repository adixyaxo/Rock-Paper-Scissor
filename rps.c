#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>

GtkWidget *result_label;

const char *choices[] = {"Rock", "Paper", "Scissors"};

void play_game(GtkWidget *widget, gpointer user_data)
{
    int user_choice = GPOINTER_TO_INT(user_data);
    int computer_choice = rand() % 3;

    const char *result;

    if (user_choice == computer_choice)
        result = "Draw!";
    else if (
        (user_choice == 0 && computer_choice == 2) ||
        (user_choice == 1 && computer_choice == 0) ||
        (user_choice == 2 && computer_choice == 1))
        result = "You Win!";
    else
        result = "You Lose!";

    char text[200];
    snprintf(
        text, sizeof(text),
        "You chose: %s\nComputer chose: %s\n\nResult: %s",
        choices[user_choice],
        choices[computer_choice],
        result
    );

    gtk_label_set_text(GTK_LABEL(result_label), text);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    srand(time(NULL));

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Rock Paper Scissors");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 300);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *title = gtk_label_new("Rock Paper Scissors");
    gtk_widget_set_name(title, "title");
    gtk_box_pack_start(GTK_BOX(vbox), title, FALSE, FALSE, 5);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);

    GtkWidget *rock_btn = gtk_button_new_with_label("Rock");
    GtkWidget *paper_btn = gtk_button_new_with_label("Paper");
    GtkWidget *scissors_btn = gtk_button_new_with_label("Scissors");

    gtk_box_pack_start(GTK_BOX(hbox), rock_btn, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), paper_btn, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), scissors_btn, TRUE, TRUE, 0);

    g_signal_connect(rock_btn, "clicked", G_CALLBACK(play_game), GINT_TO_POINTER(0));
    g_signal_connect(paper_btn, "clicked", G_CALLBACK(play_game), GINT_TO_POINTER(1));
    g_signal_connect(scissors_btn, "clicked", G_CALLBACK(play_game), GINT_TO_POINTER(2));

    result_label = gtk_label_new("Make your choice!");
    gtk_label_set_justify(GTK_LABEL(result_label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), result_label, TRUE, TRUE, 10);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
