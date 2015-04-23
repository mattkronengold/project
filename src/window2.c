#include <pebble.h>
#include "window2.h"
#include "window2_5.h"
#include "window3.h"
#include "no_locations.h"

static Window *s_window2;
static TextLayer *s_textlayer;
static SimpleMenuLayer *s_menu;
static char name_buffer[10][250];
static int num_places;

#define NUM_MENU_SECTIONS 1
#define NUM_MENU_ITEMS 10
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem menu_items[NUM_MENU_ITEMS];

#define KEY_PLACE 12
  
static void menu_select_callback(int index, void *ctx)
{
    int sendIndex = index + 1;
    
    Tuplet type_tuple =  TupletInteger(KEY_PLACE, sendIndex);
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_tuplet(iter, &type_tuple);
    dict_write_end(iter);
    app_message_outbox_send();
    show_window2_5();
}

void add_items(char name_bufferx[10][250], int num_placesx)
{
  for(int k = 0; k < 10; k ++)
    snprintf(name_buffer[k], sizeof(name_buffer[k]), "%s", name_bufferx[k]);

  num_places = num_placesx;
  
  if(num_places == 0)
    show_no_locations();
  
  else
  {
    window_stack_pop(false);
    vibes_short_pulse();
    show_window2();
  }
}

static void window2_load(Window *window) 
{  
  // s_textlayer
  
  s_textlayer = text_layer_create(GRect(3, 1, 140, 29));
  text_layer_set_text(s_textlayer, "Locations");
  text_layer_set_text_alignment(s_textlayer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), (Layer *)s_textlayer);

  //s_menu
  
  int k = 0;

  while(k < num_places)
  {
      menu_items[k] = (SimpleMenuItem){
        .title = name_buffer[k],
        .callback = menu_select_callback,
  };
    k++;
  }
  
  menu_sections[0] = (SimpleMenuSection){
    .num_items = k,
    .items = menu_items,
  };
  
  s_menu = simple_menu_layer_create(GRect(0, 35, 144, 117), s_window2, menu_sections, NUM_MENU_SECTIONS, NULL);
  
  layer_add_child(window_get_root_layer(s_window2), simple_menu_layer_get_layer(s_menu));
}

static void window2_unload(Window *window) 
{
  text_layer_destroy(s_textlayer);
  simple_menu_layer_destroy(s_menu);
}

void show_window2(void) 
{
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

void deinit_window2(void) 
{
  window_destroy(s_window2);
}