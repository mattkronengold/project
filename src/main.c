#include <pebble.h>
#include "window1.h"
#include "window2.h"
#include "window3.h"
  
static void init()
{
  //register callbacks
  
  app_message_register_outbox_sent(outbox_sent_callback);
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  
  //open appmessage
  
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit()
{
  deinit_window1();
  deinit_window2();
  deinit_window3();
}

int main(void) 
{
  init();
  show_window1();
  app_event_loop();
  deinit();
}