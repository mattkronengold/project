#include "main.h"
#include "window1.h"
#include "window2.h"
#include "window3.h"
  
static char name_buffer[10][250];
static int num_places;


#define KEY_TYPE 0
#define KEY_NAME1 1
#define KEY_NAME2 2
#define KEY_NAME3 3
#define KEY_NAME4 4
#define KEY_NAME5 5
#define KEY_NAME6 6
#define KEY_NAME7 7
#define KEY_NAME8 8
#define KEY_NAME9 9
#define KEY_NAME10 10
#define KEY_NUM_PLACES 11
#define KEY_INFO 12
#define KEY_ADDRESS 13
#define KEY_PHONE 14
#define KEY_HOURS 15
 
static void outbox_sent_callback(DictionaryIterator *iterator, void *context) 
{
  APP_LOG(APP_LOG_LEVEL_INFO, "Message sent to Pebble JS");
}

void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}
 
void inbox_received_callback(DictionaryIterator *iterator, void *context)
  {
  static int add = 0;
  
  APP_LOG(APP_LOG_LEVEL_INFO, "Message Received");

  //Read first item
  
  Tuple *t = dict_read_first(iterator);
  
  int keyIndex = 0;
  
  //For all items
  
  while(t != NULL)  {
    
    switch(t->key)  {
      case KEY_NUM_PLACES:
        num_places = (int)t->value->int32;
        APP_LOG(APP_LOG_LEVEL_INFO, "Num Places Received: %d", num_places);
        break;
      case KEY_ADDRESS:
        snprintf(address, sizeof(address), "%s", t->value->cstring);
        APP_LOG(APP_LOG_LEVEL_INFO, "Address Received: %s", address);
        break;
      case KEY_PHONE:
        snprintf(phone, sizeof(phone), "%s", t->value->cstring);
        APP_LOG(APP_LOG_LEVEL_INFO, "Phone Received: %s", phone);
        break;
      case KEY_HOURS:
        snprintf(hours, sizeof(hours), "%s", t->value->cstring);
        APP_LOG(APP_LOG_LEVEL_INFO, "Hours Received: %s", hours);
        break;
      default:
        keyIndex = (t->key)-1;
        snprintf(name_buffer[keyIndex], sizeof(name_buffer[keyIndex]), "%s", t->value->cstring);
        add = 1;
        break;
    }

    // Look for next item
    
    t = dict_read_next(iterator);
  }
  
  //Pass info to Window2_5
  
  
  
  //Rename Menu Items
  
 
  if(add ==1)
  {
    APP_LOG(APP_LOG_LEVEL_INFO, "Populating Menu with Names");
    add_items(name_buffer,num_places);
    add = 0;
  }
}

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