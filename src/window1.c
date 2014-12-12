#include <pebble.h>
#include "window1.h"
#include "window2.h"
#include "window3.h"
#include "loading.h"

static Window *s_window1;
static TextLayer *s_textlayer;
static SimpleMenuLayer *s_menu;

#define KEY_TYPE 0

#define NUM_MENU_SECTIONS 1
#define NUM_MENU_ITEMS 12
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem menu_items[NUM_MENU_ITEMS];
static char menu_titles[NUM_MENU_ITEMS][250];

static void menu_select_callback_all(int index, void *ctx)
{
    Tuplet type_tuple =  TupletCString(KEY_TYPE, menu_titles[index]);
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_tuplet(iter, &type_tuple);
    dict_write_end(iter);
    app_message_outbox_send();
    show_loading();
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
  
  snprintf(menu_titles[num_a_items], sizeof(menu_titles[num_a_items]), "airport");
  
   menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Airport",
    .callback = menu_select_callback_all,
  };
  
  snprintf(menu_titles[num_a_items], sizeof(menu_titles[num_a_items]), "atm");
  
   menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "ATM",
    .callback = menu_select_callback_all,
  };
  
  snprintf(menu_titles[num_a_items], sizeof(menu_titles[num_a_items]), "bank");
  
   menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Bank",
    .callback = menu_select_callback_all,
  };
  
  snprintf(menu_titles[num_a_items], sizeof(menu_titles[num_a_items]), "bar");
  
   menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Bar",
    .callback = menu_select_callback_all,
  };
  
  snprintf(menu_titles[num_a_items], sizeof(menu_titles[num_a_items]), "doctor");
  
   menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Doctor",
    .callback = menu_select_callback_all,
  };
  
  snprintf(menu_titles[num_a_items], sizeof(menu_titles[num_a_items]), "gas_station");
  
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Gas Station",
    .callback = menu_select_callback_all,
  };
  
  snprintf(menu_titles[num_a_items], sizeof(menu_titles[num_a_items]), "gym");
  
   menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Gym",
    .callback = menu_select_callback_all,
  };
  
  snprintf(menu_titles[num_a_items], sizeof(menu_titles[num_a_items]), "movie_theater");
  
   menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Movie Theater",
    .callback = menu_select_callback_all,
  };
  
  snprintf(menu_titles[num_a_items], sizeof(menu_titles[num_a_items]), "park");
  
   menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Park",
    .callback = menu_select_callback_all,
  };
  
  snprintf(menu_titles[num_a_items], sizeof(menu_titles[num_a_items]), "pharmacy");
  
   menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Pharmacy",
    .callback = menu_select_callback_all,
  };
  
  snprintf(menu_titles[num_a_items], sizeof(menu_titles[num_a_items]), "restaurant");
    
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Restaurant",
    .callback = menu_select_callback_all,
  };
  
  snprintf(menu_titles[num_a_items], sizeof(menu_titles[num_a_items]), "synagogue");
  
   menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Synagogue",
    .callback = menu_select_callback_all,
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

void deinit_window1(void) 
{
  window_destroy(s_window1);
}