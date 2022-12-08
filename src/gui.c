#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
//#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include "neural_network/neural_network.h"


GtkWidget *window;
GtkWidget *fixed1;
GtkBuilder *builder;
GtkWidget *image1;
GtkWidget *file1;


int GUI(int argc, char *argv[])
{
    gtk_init(&argc, &argv); // init Gtk


    builder = gtk_builder_new_from_file("OCR_GUI.glade");
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    image1 = GTK_WIDGET(gtk_builder_get_object(builder, "image1"));
    file1 = GTK_WIDGET(gtk_builder_get_object(builder, "file1"));


    gtk_widget_show(window);

    image1 = NULL;

    gtk_main();

    return EXIT_SUCCESS;
}

void on_file_set1(GtkFileChooserButton *f)
{
    printf("loading image...\n");
    gchar* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f));
    int hor = 150, ver = 8;
    if (image1)
        gtk_container_remove(GTK_CONTAINER(fixed1), image1); // remove old slide
    image1 = gtk_image_new_from_file(filename);
    gtk_container_add(GTK_CONTAINER(fixed1), image1);
    gtk_widget_show(image1);
    gtk_fixed_move(GTK_FIXED(fixed1), image1, hor, ver);
    Neural_Network_Main((char*)filename);
    g_free(filename);
}
