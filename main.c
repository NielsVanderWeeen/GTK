#include <gtk/gtk.h>
#include <PJ_RPI.h>

void readGpio(GtkWidget *wid, gpointer ptr){
  char state[40];
  int GPIO17 = GPIO_READ(17);
  int GPIO18 = GPIO_READ(18);
  sprintf(state, "Pin 17: %d\nPin 18: %d", GPIO17>>17, GPIO18>>18);
  gtk_label_set_text (GTK_LABEL (ptr), state);
}

void setGpio(GtkWidget *wid, gpointer ptr){
  int x = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid));

  if(x == 1){
      GPIO_SET = 1 << 27;
  } else {
      GPIO_CLR = 1 << 27;
  }
}

void setGpio2(GtkWidget *wid, gpointer ptr){
  int x = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid));

  if(x == 1){
      GPIO_SET = 1 << 22;
  } else {
      GPIO_CLR = 1 << 22;
  }
}

void main (int argc, char *argv[])
{
  if(map_peripheral(&gpio) == -1){
    printf("failed to map the physical GPIO registers into the virtual memory");
  }
 
  INP_GPIO(17);
  INP_GPIO(18);
  OUT_GPIO(27);
  OUT_GPIO(22);

  gtk_init (&argc, &argv);
  GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  GtkWidget *box = gtk_box_new (FALSE, 5);
  GtkWidget *lbl = gtk_label_new ("Opdracht GTK");
  GtkWidget *btn = gtk_button_new_with_label ("Get State");
  g_signal_connect (btn, "clicked", G_CALLBACK (readGpio), lbl);
  g_signal_connect (win, "delete_event", G_CALLBACK (readGpio), 
  NULL);

  GtkWidget *chk = gtk_check_button_new_with_label ("Change State GPIO 27");
  g_signal_connect(chk, "toggled", G_CALLBACK(setGpio), NULL);
  GtkWidget *chk2 = gtk_check_button_new_with_label ("Change State GPIO 22");
  g_signal_connect(chk, "toggled", G_CALLBACK(setGpio2), NULL);

  gtk_box_pack_start (GTK_BOX (box), lbl, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (box), chk, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (box), chk2, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (box), btn, TRUE, TRUE, 0);
  gtk_container_add (GTK_CONTAINER (win), box);
  gtk_widget_show_all (win);
  gtk_main ();
}