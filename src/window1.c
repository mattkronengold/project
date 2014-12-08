#include <pebble.h>
#include "window1.h"
#include "window2.h"

static Window *s_window1;
static TextLayer *s_textlayer;
static SimpleMenuLayer *s_menu;

#define KEY_NAME 0
#define KEY_TYPE 1

#define NUM_MENU_SECTIONS 1
#define NUM_MENU_ITEMS 2

static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

static SimpleMenuItem menu_items[NUM_MENU_ITEMS];

static void menu_select_callback1(int index, void *ctx)
{

    Tuplet type_tuple =  TupletCString(KEY_TYPE, "restaurant");
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_tuplet(iter, &type_tuple);
    dict_write_end(iter);
    app_message_outbox_send();
    show_window2();

}

static void menu_select_callback2(int index, void *ctx)
{
  
    Tuplet type_tuple =  TupletCString(KEY_TYPE, "gas_station");
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_tuplet(iter, &type_tuple);
    dict_write_end(iter);
    app_message_outbox_send();
    show_window2();
}
  
static void window1_load(Window *window) 
{  
  // s_textlayer
  s_textlayer = text_layer_create(GRect(3, 1, 140, 29));
  text_layer_set_text(s_textlayer, "Please Select a Type of Location");
  text_layer_set_text_alignment(s_textlayer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), (Layer *)s_textlayer);

  // s_menu
  int num_a_items = 0;
  
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Restaurant",
    .callback = menu_select_callback1,
  };
  
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Gas Station",
    .callback = menu_select_callback2,
  };
  
  menu_sections[0] = (SimpleMenuSection){
    .num_items = NUM_MENU_ITEMS,
    .items = menu_items,
  };
  
  s_menu = simple_menu_layer_create(GRect(0, 35, 144, 117), window, menu_sections, NUM_MENU_SECTIONS, NULL);
  layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(s_menu));
}

static void window1_unload(Window *window) 
{
  text_layer_destroy(s_textlayer);
  simple_menu_layer_destroy(s_menu);
}

void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Type sent to Pebble JS");
}


void show_window1(void) {  
  // Create main Window element and assign to pointer
  s_window1 = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_window1, (WindowHandlers) {
    .load = window1_load,
    .unload = window1_unload
  });
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_window1, true);
}

void hide_window1(void) {
  
  window_stack_remove(s_window1, true);
}