#include <pebble.h>
#include "colordefs.h"

static TextLayer *s_time_layer;
static GFont s_time_font;
  
static TextLayer *s_day_layer;
static TextLayer *s_date_layer;

static char day_text[24] = "Wednesday";
static char date_text[32] = "September 03 2014";

static char time_text[] = "00:00";  

static void date_layer_create(Window *window) {
  // Day of week above the time
  s_day_layer = text_layer_create(GRect(0, 38, 144, 20));
  text_layer_set_background_color(s_day_layer, GColorClear);
  text_layer_set_text_color(s_day_layer, GColorWhite);
  text_layer_set_font(s_day_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  text_layer_set_text_alignment(s_day_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_day_layer));

  // Date (Month Day Year) below the time
  s_date_layer = text_layer_create(GRect(0, 100, 144, 40));
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, GColorWhite);
  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));
}

static void time_layer_create(Window *window) {
  s_time_layer = text_layer_create(GRect(0, 52, 144, 48));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, TIME_COLOR);
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_OUT_48));
  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
}

static void update_date_time(struct tm* pbltime) {
  time_t now;
  if (pbltime == NULL) {
    now = time(NULL);
    pbltime = localtime(&now);
  }
  if(clock_is_24h_style()) {
    strftime(time_text, sizeof(time_text), "%H:%M", pbltime);
    strftime(day_text, sizeof(day_text), "%A", pbltime);
  } else {
    strftime(time_text, sizeof(time_text), "%l:%M", pbltime);
    if (time_text[0] == ' ') memmove(time_text, &time_text[1], sizeof(time_text) - 1);
    strftime(day_text, sizeof(day_text), "%A %p", pbltime);
  }
  strftime(date_text, sizeof(date_text), "%B %d\n\r%Y", pbltime);

  text_layer_set_text(s_time_layer, time_text);
  text_layer_set_text(s_day_layer, day_text);
  text_layer_set_text(s_date_layer, date_text);  
}
