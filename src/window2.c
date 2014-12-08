#include <pebble.h>
#include "window2.h"
#include "loading.h"

static Window *s_window2;
static TextLayer *s_textlayer;
static SimpleMenuLayer *s_menu;
#define NUM_MENU_SECTIONS 1
#define NUM_MENU_ITEMS 10
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem menu_items[NUM_MENU_ITEMS];
static char name_buffer[10][250];
static int num_places;

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

  /*
static void menu_select_callback(int index, void *ctx)
{
  menu_items[index].title = "Selected";
  layer_mark_dirty(simple_menu_layer_get_layer(s_menu));
}
*/

static void window2_load(Window *window) 
{  
   APP_LOG(APP_LOG_LEVEL_INFO, "Show Text Layer");
  // s_textlayer
  
  s_textlayer = text_layer_create(GRect(3, 1, 140, 29));
  text_layer_set_text(s_textlayer, "Locations");
  text_layer_set_text_alignment(s_textlayer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), (Layer *)s_textlayer);

  
  // s_menu
  
  int k = 0;
  
   APP_LOG(APP_LOG_LEVEL_INFO, "Create Menu Items");
  //while(k < num_places)
    //{
      menu_items[k] = (SimpleMenuItem){
        .title = name_buffer[k],
  };
    k++;
  //}
  
   APP_LOG(APP_LOG_LEVEL_INFO, "Create Menu Sections");
  menu_sections[0] = (SimpleMenuSection){
    .num_items = k,
    .items = menu_items,
  };
 APP_LOG(APP_LOG_LEVEL_INFO, "Create Menu");
  s_menu = simple_menu_layer_create(GRect(0, 35, 144, 117), window, menu_sections, NUM_MENU_SECTIONS, NULL);
  
   APP_LOG(APP_LOG_LEVEL_INFO, "Show Menu");
  layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(s_menu));
  
}

static void window2_unload(Window *window) 
{
  text_layer_destroy(s_textlayer);
  simple_menu_layer_destroy(s_menu);
}

void show_window2(void) {
  
  
  // Create main Window element and assign to pointer
  s_window2 = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_window2, (WindowHandlers) {
    .load = window2_load,
    .unload = window2_unload,
  });
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_window2, true);
}

void hide_window2(void) {
  
  window_stack_remove(s_window2, true);
}

void inbox_received_callback(DictionaryIterator *iterator, void *context)
  {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Message Received");

  //Read first item
  
  Tuple *t = dict_read_first(iterator);
  
  int index = 0;
  
  //For all items
  
  while(t != NULL)  {
    
    switch(t->key)  {
      case KEY_NUM_PLACES:
        num_places = (int)t->value->int32;
        break;
      default:
        snprintf(name_buffer[index], sizeof(name_buffer[index]), "%s", t->value->cstring);
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Name Received: %s", name_buffer[index]);
        break;
    }

    // Look for next item
    
    t = dict_read_next(iterator);
    
    index++;
  }
  
  APP_LOG(APP_LOG_LEVEL_INFO, "About to show window2");
  //APP_LOG(APP_LOG_LEVEL_INFO, "Number of names = %d", num_places);
  next_screen();
}