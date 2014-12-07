#include <pebble.h>
#include "window1.h"

int main(void) 
{
  show_window1();
  app_event_loop();
  hide_window1();
}