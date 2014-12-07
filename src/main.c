#include <pebble.h>
  
static Window *s_main_window;
//static TextLayer *s_time_layer;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_2;
static TextLayer *s_textlayer_3;

#define KEY_NAME 0

static void main_window_load(Window *window) 
{
  /*
  //create time layer
  s_time_layer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  text_layer_set_text(s_time_layer, "Loading");
  */

  //layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(3, 11, 140, 18));
  text_layer_set_text(s_textlayer_1, "Closest Food Location:");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(20, 33, 100, 102));
  text_layer_set_background_color(s_textlayer_2, GColorBlack);
  text_layer_set_text_color(s_textlayer_2, GColorWhite);
  text_layer_set_text(s_textlayer_2, "Loading...");
  text_layer_set_text_alignment(s_textlayer_2, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), (Layer *)s_textlayer_2);
  
  // s_textlayer_3
  s_textlayer_3 = text_layer_create(GRect(21, 110, 100, 32));
  text_layer_set_text(s_textlayer_3, "Press Up for Address");
  text_layer_set_text_alignment(s_textlayer_3, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), (Layer *)s_textlayer_3);
}

static void main_window_unload(Window *window) 
{
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_2);

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
    
    text_layer_set_text(s_textlayer_2, name_buffer);
    
    // Look for next item
    
    t = dict_read_next(iterator);
  }
  
}

static void init() 
{
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  //register callbacks
  
  app_message_register_inbox_received(inbox_received_callback);
  
  //open appmessage
  
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
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