#include <pebble.h>
#include "window2_5.h"
#include "window3.h"
#include "main.h"

static Window *s_window2_5;
static TextLayer *s_textlayer;
static SimpleMenuLayer *s_menu;

#define NUM_MENU_SECTIONS 1
#define NUM_MENU_ITEMS 3
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem menu_items[NUM_MENU_ITEMS];

static void menu_select_callback(int index, void *ctx)
{
  
  show_window3();
  
  if(index == 0)
    {
    window3_add_text("Phone Number",phone);
  }
  
  if(index == 1)
    {
    window3_add_text("Address",address);
  }
  
  if(index == 2)
  {
    if(strcmp("open_true", hours) == 0)
    { 
      window3_add_text("Hours","Open Now"); 
    }
    
    if(strcmp("open_false", hours) == 0)
    { 
      window3_add_text("Hours","Closed"); 
    }
    
    if(strcmp("no_hours", hours) == 0)
    { 
      window3_add_text("Hours","Hours Not Available"); 
    }

  }
}

static void window2_5_load(Window *window) 
{  
  // s_textlayer
  
  s_textlayer = text_layer_create(GRect(3, 1, 140, 29));
  text_layer_set_text(s_textlayer, "Information");
  text_layer_set_text_alignment(s_textlayer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), (Layer *)s_textlayer);

  //s_menu

  menu_items[0] = (SimpleMenuItem){
        .title = "Phone Number",
        .callback = menu_select_callback,
  };
  
  menu_items[1] = (SimpleMenuItem){
        .title = "Address",
        .callback = menu_select_callback,
  };
  
  menu_items[2] = (SimpleMenuItem){
        .title = "Hours",
        .callback = menu_select_callback,
  };
  
  menu_sections[0] = (SimpleMenuSection){
    .num_items = 3,
    .items = menu_items,
  };
  
  s_menu = simple_menu_layer_create(GRect(0, 35, 144, 117), s_window2_5, menu_sections, NUM_MENU_SECTIONS, NULL);
  
  layer_add_child(window_get_root_layer(s_window2_5), simple_menu_layer_get_layer(s_menu));
}

static void window2_5_unload(Window *window) 
{
  text_layer_destroy(s_textlayer);
  simple_menu_layer_destroy(s_menu);
}

void show_window2_5(void) 
{
  // Create main Window element and assign to pointer
  s_window2_5 = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_window2_5, (WindowHandlers) {
    .load = window2_5_load,
    .unload = window2_5_unload,
  });
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_window2_5, true);
}

void deinit_window2_5(void) 
{
  window_destroy(s_window2_5);
}