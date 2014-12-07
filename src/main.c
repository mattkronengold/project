#include <pebble.h>
#include "window2.h"
  
static Window *s_main_window;
//static Window *s_window2;
static TextLayer *s_textlayer_1;
//static TextLayer *s_textlayer_3;
static SimpleMenuLayer *s_menu;

static char name_buffer[32];


#define KEY_NAME 0
#define NUM_MENU_SECTIONS 1
#define NUM_MENU_ITEMS 2

static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

static SimpleMenuItem menu_items[NUM_MENU_ITEMS];

static void menu_select_callback(int index, void *ctx)
{
  //menu_items[index].title = "Selected!";
  //layer_mark_dirty(simple_menu_layer_get_layer(s_menu));
  show_window2();
}
  
static void main_window_load(Window *window) 
{  
 // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(3, 1, 140, 29));
  text_layer_set_text(s_textlayer_1, "Closest Food Location, Click for Address");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), (Layer *)s_textlayer_1);

  //s_menu
  int num_a_items = 0;
  
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = name_buffer,
    .callback = menu_select_callback,
  };
  
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Loading...2",
    .callback = menu_select_callback,
  };
  
  menu_sections[0] = (SimpleMenuSection){
    .num_items = NUM_MENU_ITEMS,
    .items = menu_items,
  };
  
  s_menu = simple_menu_layer_create(GRect(0, 35, 144, 117), window, menu_sections, NUM_MENU_SECTIONS, NULL);
  layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(s_menu));
}

static void main_window_unload(Window *window) 
{
  text_layer_destroy(s_textlayer_1);
  simple_menu_layer_destroy(s_menu);
  //text_layer_destroy(s_textlayer_3);
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context)
  {
  
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
    
    //text_layer_set_text(s_textlayer_2, name_buffer);
    
    // Look for next item
    
    t = dict_read_next(iterator);
  }
  
}

static void init() 
{
  //register callbacks
  
  app_message_register_inbox_received(inbox_received_callback);
  
  //open appmessage
  
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  

}

static void deinit() 
{
  window_destroy(s_main_window);

}

int main(void) 
{
  init();
  app_event_loop();
  deinit();

}