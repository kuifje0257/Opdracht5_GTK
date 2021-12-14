/*gcc `pkg-config --cflags --libs gtk+-2.0` GTK_Opdracht3.c -o GTK_Opdracht3 -lwiringPi*/
//Combobox toevoegen
#include <gtk/gtk.h>
#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
//LED1 => pin 12
//LED1 => pin 16
//Button => pin 11
//GND => pin 6
//GND => pin 9
int count = 0;
int GPIO12_State=0;
int GPIO16_State=0;
const int ledPin1 = 18; ///wPi 18= pin 12
const int ledPin2 = 23; //wPi 23= pin16
const int btnPin = 0; //wPi 0= pin 11

void end_program (GtkWidget *wid, gpointer ptr)
{
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    gtk_main_quit ();
}

void GPIO12_CHANGED (GtkWidget *wid, gpointer ptr)
{
    char buffer[30];

    GPIO12_State = !GPIO12_State; 
    if(GPIO12_State==1){
        sprintf (buffer, "State GPIO12: %d", GPIO12_State);
        gtk_label_set_text (GTK_LABEL (ptr), buffer);
        digitalWrite(ledPin1, HIGH);
    }
    if(GPIO12_State==0){
        sprintf (buffer, "State GPIO12: %d", GPIO12_State);
        gtk_label_set_text (GTK_LABEL (ptr), buffer);
        digitalWrite(ledPin1, LOW);
    }
}

void GPIO16_CHANGED (GtkWidget *wid, gpointer ptr)
{
    char buffer[30];

    GPIO16_State = !GPIO16_State; 
    if(GPIO16_State==1){
        sprintf (buffer, "State GPIO16: %d", GPIO16_State);
        gtk_label_set_text (GTK_LABEL (ptr), buffer);
        digitalWrite(ledPin2, HIGH);
    }
    if(GPIO16_State==0){
        sprintf (buffer, "State GPIO16: %d", GPIO16_State);
        gtk_label_set_text (GTK_LABEL (ptr), buffer);
        digitalWrite(ledPin2, LOW);
    }
}

void GPIO11_State (GtkWidget *wid, gpointer ptr)
{
    char buffer[30];
    if (digitalRead(btnPin)) // Button is released if this returns 1
    {
        sprintf (buffer, "State GPIO11: 1");
        gtk_label_set_text (GTK_LABEL (ptr), buffer);
    }
    else // If digitalRead returns 0, button is pressed
    {
        sprintf (buffer, "State GPIO11: 0");
        gtk_label_set_text (GTK_LABEL (ptr), buffer);
    }
}

void combo_changed (GtkWidget *wid, gpointer ptr)
{   
    int sel = gtk_combo_box_get_active (GTK_COMBO_BOX (wid));
    char *selected = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT (wid));

    printf ("The value of the combo is %s\n", selected);
    if(sel ==1){
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, HIGH);
    }
    if(sel ==0){
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin1, HIGH);
    }
}

int main (int argc, char *argv[])
{
    // Setup stuff:
    wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers
    
    pinMode(btnPin, INPUT);      // Set button as INPUT
    pullUpDnControl(btnPin, PUD_UP);
    pinMode(ledPin1, OUTPUT);     // Set regular LED as output
    pinMode(ledPin2, OUTPUT);     // Set regular LED as output

    gtk_init (&argc, &argv);
    //Aanmaken Widgets
    GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL); //Window
    GtkWidget *btn = gtk_button_new_with_label ("Exit"); //button
    GtkWidget *lbl = gtk_label_new ("My Assignment");//label 
    GtkWidget *lbl2 = gtk_label_new ("State GPIO12: 0");//label LED1
    GtkWidget *lbl3 = gtk_label_new ("State GPIO16: 0");//label LED2
    GtkWidget *lbl4 = gtk_label_new ("State GPIO11: 0");//label Button
    GtkWidget *lbl5 = gtk_label_new ("Combobox: ");//label Combobox
    GtkWidget *tbl = gtk_table_new (11, 11, TRUE); //tabel 0-11
    GtkWidget *btn2 = gtk_button_new_with_label ("Change GPIO12"); //LED button
    GtkWidget *btn3 = gtk_button_new_with_label ("Change GPIO16"); //LED button
    GtkWidget *btn4 = gtk_button_new_with_label ("Check State of button"); //ButtonState button
    
    //ComboBox (uitbreiding)
    GtkWidget *comb = gtk_combo_box_text_new (); //Combobox
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (comb), "GPIO 12");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (comb), "GPIO 16");
    gtk_combo_box_set_active (GTK_COMBO_BOX (comb), 0);
    g_signal_connect (comb, "changed", G_CALLBACK (combo_changed), NULL);
    
    //events
    g_signal_connect (btn, "clicked", G_CALLBACK (end_program),NULL);
    g_signal_connect (btn2, "clicked", G_CALLBACK (GPIO12_CHANGED), lbl2);
    g_signal_connect (btn3, "clicked", G_CALLBACK (GPIO16_CHANGED), lbl3);
    g_signal_connect (btn4, "clicked", G_CALLBACK (GPIO11_State), lbl4);
    g_signal_connect (win, "delete_event", G_CALLBACK (end_program),NULL);

    //widgets toevoegen aan tabel
    //Top Label
    gtk_table_attach_defaults (GTK_TABLE (tbl), lbl, 4, 7, 0, 1); // 1ste nummer < 2de nummer, 3de nummer < 4de nummer (eerste 2 zijn de breedte, laatste 2 zijn de hoogte)
    //GPIO Buttons
    gtk_table_attach_defaults (GTK_TABLE (tbl), btn2, 0, 4, 1, 3); 
    gtk_table_attach_defaults (GTK_TABLE (tbl), btn3, 7, 11, 1, 3);
    gtk_table_attach_defaults (GTK_TABLE (tbl), btn4, 0, 4, 5, 6);
    //GPIO Labels
    gtk_table_attach_defaults (GTK_TABLE (tbl), lbl2, 0, 4, 3, 4);
    gtk_table_attach_defaults (GTK_TABLE (tbl), lbl3, 7, 11, 3, 4);
    gtk_table_attach_defaults (GTK_TABLE (tbl), lbl4, 4, 7, 5, 6);
    gtk_table_attach_defaults (GTK_TABLE (tbl), lbl5, 0, 2, 7, 8);
    //Exit button
    gtk_table_attach_defaults (GTK_TABLE (tbl), btn, 10, 11, 10, 11);
    //Combobox
    gtk_table_attach_defaults (GTK_TABLE (tbl), comb, 2, 4, 7, 8);

    
    //box toevoegen aan window
    gtk_container_add (GTK_CONTAINER (win), tbl);

    gtk_widget_show_all (win);
    gtk_main ();
    return 0;
}