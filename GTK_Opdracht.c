/*gcc `pkg-config --cflags --libs gtk+-2.0` GTK_Opdracht.c -o GTK_Opdracht -lwiringPi*/
//basic
#include <gtk/gtk.h>

int count = 0;
int GPIO12_State;
int GPIO16_State;

void end_program (GtkWidget *wid, gpointer ptr)
{
 gtk_main_quit ();
}

void count_button (GtkWidget *wid, gpointer ptr)
{
 char buffer[30];
 count++;
 sprintf (buffer, "Button pressed %d times", count);
 gtk_label_set_text (GTK_LABEL (ptr), buffer);
}


int main (int argc, char *argv[])
{
    gtk_init (&argc, &argv);
    GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL); //Window
    GtkWidget *btn = gtk_button_new_with_label ("Exit"); //button
    GtkWidget *lbl = gtk_label_new ("My Assignment");//label 
    GtkWidget *lbl2 = gtk_label_new ("State GPIO12:");//label 
    GtkWidget *lbl3 = gtk_label_new ("State GPIO16:");//label 
    GtkWidget *tbl = gtk_table_new (11, 11, TRUE); //tabel 0-11
    GtkWidget *btn2 = gtk_button_new_with_label ("Count button"); //Count button
    
    //ComboBox (uitbreiding)
    
    //events
    g_signal_connect (btn, "clicked", G_CALLBACK (end_program),NULL);
    g_signal_connect (btn2, "clicked", G_CALLBACK (count_button), lbl);
    g_signal_connect (win, "delete_event", G_CALLBACK (end_program),NULL);

    //widgets toevoegen aan tabel
    gtk_table_attach_defaults (GTK_TABLE (tbl), lbl, 4, 6, 0, 1); // 1ste nummer < 2de nummer, 3de nummer < 4de nummer (eerste 2 zijn de breedte, laatste 2 zijn de hoogte)
    gtk_table_attach_defaults (GTK_TABLE (tbl), btn2, 0, 4, 1, 3); 
    gtk_table_attach_defaults (GTK_TABLE (tbl), btn, 10, 11, 10, 11); //exit button
    
    //box toevoegen aan window
    gtk_container_add (GTK_CONTAINER (win), tbl);

    gtk_widget_show_all (win);
    gtk_main ();
    return 0;
}


/*
void combo_changed (GtkWidget *wid, gpointer ptr)
{
 int sel = gtk_combo_box_get_active (GTK_COMBO_BOX (wid));
 char *selected = gtk_combo_box_text_get_active_text (
 GTK_COMBO_BOX_TEXT (wid));
 printf ("The value of the combo is %d %s\n", sel, selected);
}
*/

/*GtkWidget *comb = gtk_combo_box_text_new (); //Combobox
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (comb), "GPIO 17");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (comb), "GPIO 27");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (comb), "Option 3");
    gtk_combo_box_set_active (GTK_COMBO_BOX (comb), 0);

    g_signal_connect (comb, "changed", G_CALLBACK (combo_changed), NULL);*/