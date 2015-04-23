#include <pebble.h>
#include "window3.h"

static Window *s_window3;
static GFont s_res_gothic_24_bold;
static GFont s_res_gothic_18_bold;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_2;

void window3_add_text(char title[250], char info[250])
{
  text_layer_set_text(s_textlayer_1,title);
  text_layer_set_text(s_textlayer_2,info);
}

static void window3_load(Window *window) 
{
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(3, 1, 140, 29));
  text_layer_set_text(s_textlayer_1, "");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(20, 39, 102, 118));
  text_layer_set_background_color(s_textlayer_2, GColorBlack);
  text_layer_set_text_color(s_textlayer_2, GColorWhite);
  text_layer_set_text(s_textlayer_2, "Loading...");
  text_layer_set_text_alignment(s_textlayer_2, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_2, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(window), (Layer *)s_textlayer_2);
}

static void window3_unload(Window *window)
{
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_2);
}

void show_window3(void) 
{
  s_window3 = window_create();
  
  window_set_window_handlers(s_window3, (WindowHandlers) {
    .load = window3_load,
    .unload = window3_unload,
  });
  
  window_stack_push(s_window3, true);
}

void deinit_window3(void) 
{
  window_destroy(s_window3);
}