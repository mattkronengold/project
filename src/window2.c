#include <pebble.h>
#include "window2.h"

static Window *s_window2;
static TextLayer *s_textlayer;
static TextLayer *s_textlayer_2;
static SimpleMenuLayer *s_menu;

#define KEY_NAME 0
#define KEY_TYPE 1

#define NUM_MENU_SECTIONS 1
#define NUM_MENU_ITEMS 2

static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

static SimpleMenuItem menu_items[NUM_MENU_ITEMS];

static void menu_select_callback(int index, void *ctx)
{
  menu_items[index].title = "Selected";
  layer_mark_dirty(simple_menu_layer_get_layer(s_menu));
}
  
static void window2_load(Window *window) 
{  
  // s_textlayer
  s_textlayer = text_layer_create(GRect(3, 1, 140, 29));
  text_layer_set_text(s_textlayer, "Locations");
  text_layer_set_text_alignment(s_textlayer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), (Layer *)s_textlayer);
  
    // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(20, 33, 100, 71));
  text_layer_set_background_color(s_textlayer_2, GColorBlack);
  text_layer_set_text_color(s_textlayer_2, GColorWhite);
  text_layer_set_text(s_textlayer_2, "Text layer");
  text_layer_set_text_alignment(s_textlayer_2, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), (Layer *)s_textlayer_2);

  // s_menu
  int num_a_items = 0;
  
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Loading...",
    .callback = menu_select_callback,
  };
  
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Loading...",
    .callback = menu_select_callback,
  };
  
  menu_sections[0] = (SimpleMenuSection){
    .num_items = NUM_MENU_ITEMS,
    .items = menu_items,
  };
  
  s_menu = simple_menu_layer_create(GRect(0, 35, 144, 117), window, menu_sections, NUM_MENU_SECTIONS, NULL);
  layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(s_menu));
}

static void window2_unload(Window *window) 
{
  text_layer_destroy(s_textlayer);
  simple_menu_layer_destroy(s_menu);
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context)
  {
  static char name_buffer[32];
  
  //Read first item
  
  Tuple *t = dict_read_first(iterator);
  
  //For all items
  
  while(t != NULL)  {
    //Which key was received?
    switch(t->key)  {
      case KEY_NAME:
        snprintf(name_buffer, sizeof(name_buffer), "%s", t->value->cstring);
        break;
      default:
        APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int) t-> key);
        break;
    }
    
    text_layer_set_text(s_textlayer, name_buffer);
    
    // Look for next item
    
    t = dict_read_next(iterator);
  }
  
}

static void appmsg_in_dropped(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "In dropped: %i", reason);
}

void show_window2(void) {
  
  //register callbacks
  
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(appmsg_in_dropped);
  
  //open appmessage
  
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
  // Create main Window element and assign to pointer
  s_window2 = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_window2, (WindowHandlers) {
    .load = window2_load,
    .unload = window2_unload
  });
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_window2, true);
}



void hide_window2(void) {
  
  window_stack_remove(s_window2, true);
}