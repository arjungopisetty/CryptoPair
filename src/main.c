#include <pebble.h>
  
Window* window;

TextLayer *currency_layer, *bitcoin_layer, *dogecoin_layer, *litecoin_layer, *time_layer;
char bitcoin_buffer[64], dogecoin_buffer[64], litecoin_buffer[64], time_buffer[32];

enum {
  KEY_BPRICE = 0,
  KEY_DPRICE = 1,
  KEY_LPRICE = 2,
};

void process_tuple(Tuple *t)
{
  //Get key
  int key = t->key;
 
  //Get double value, if present
  int value = t->value->int32;
 
  //Decide what to do
  switch(key) {
    case KEY_BPRICE:
      // Bitcoin received
      snprintf(bitcoin_buffer, sizeof("100000000000000000000000"), "Bitcoin: %d", value);
      text_layer_set_text(bitcoin_layer, (char*) &bitcoin_buffer);
      break;
    case KEY_DPRICE:
      // Dogecoin received
      snprintf(dogecoin_buffer, sizeof("100000000000000000000000"), "Dogecoin (10000): %d", value);
      text_layer_set_text(dogecoin_layer, (char*) &dogecoin_buffer);
      break;
    case KEY_LPRICE:
      // Litecoin received
      snprintf(litecoin_buffer, sizeof("100000000000000000000000"), "Litecoin: %d", value);
      text_layer_set_text(litecoin_layer, (char*) &litecoin_buffer);
    
  }
 
  //Set time this update came in
  time_t temp = time(NULL);  
  struct tm *tm = localtime(&temp);
  strftime(time_buffer, sizeof("Last updated: XX:XX"), "Last updated: %H:%M", tm);
  text_layer_set_text(time_layer, (char*) &time_buffer);
}


static TextLayer* init_text_layer(GRect location, GColor colour, GColor background, const char *res_id, GTextAlignment alignment)
{
  TextLayer *layer = text_layer_create(location);
  text_layer_set_text_color(layer, colour);
  text_layer_set_background_color(layer, background);
  text_layer_set_font(layer, fonts_get_system_font(res_id));
  text_layer_set_text_alignment(layer, alignment);
 
  return layer;
}

void window_load(Window *window)
{
	currency_layer = init_text_layer(GRect(0, 0, 144, 154), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_28_BOLD", GTextAlignmentCenter);
	text_layer_set_text(currency_layer, "Cryptopair");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(currency_layer));

	bitcoin_layer = init_text_layer(GRect(0, 30, 144, 250), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_28", GTextAlignmentCenter);
	text_layer_set_text(bitcoin_layer, "Bitcoin: N/A");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(bitcoin_layer));

	dogecoin_layer = init_text_layer(GRect(0, 60, 144, 250), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentCenter);
	text_layer_set_text(dogecoin_layer, "Dogecoin (10000): N/A");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(dogecoin_layer));
  
  litecoin_layer = init_text_layer(GRect(0, 75, 144, 250), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_28", GTextAlignmentCenter);
	text_layer_set_text(litecoin_layer, "Litecoin: N/A");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(litecoin_layer));

	time_layer = init_text_layer(GRect(0, 120, 144, 100), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentCenter);
	text_layer_set_text(time_layer, "Last updated: N/A");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(time_layer));
}

void window_unload(Window *window)
{
  text_layer_destroy(currency_layer);
  text_layer_destroy(bitcoin_layer);
  text_layer_destroy(dogecoin_layer);
  text_layer_destroy(litecoin_layer);
  text_layer_destroy(time_layer); 
}

static void in_received_handler(DictionaryIterator *iter, void *context) 
{
  //Get data
  Tuple *t = dict_read_first(iter);
  if(t)
  {
    process_tuple(t);
  }
   
  //Get next
  while(t != NULL)
  {
    t = dict_read_next(iter);
    if(t)
    {
      process_tuple(t);
    }
  }
}

void send_int(uint8_t key, uint8_t cmd)
{
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
     
    Tuplet value = TupletInteger(key, cmd);
    dict_write_tuplet(iter, &value);
     
    app_message_outbox_send();
}

void tick_callback(struct tm *tick_time, TimeUnits units_changed)
{
    //Every minute
    if(tick_time->tm_min % 1 == 0)
    {
        //Send an arbitrary message, the response will be handled by in_received_handler()
        send_int(5, 5);
    }
}

void init()
{
  window = window_create();
  WindowHandlers handlers = {
    .load = window_load,
    .unload = window_unload
  };
  window_set_window_handlers(window, handlers);
 
  //Register AppMessage events
  app_message_register_inbox_received(in_received_handler);           
  app_message_open(512, 512);    //Large input and output buffer sizes
  
  //Register to receive minutely updates
  tick_timer_service_subscribe(MINUTE_UNIT, tick_callback);
  
  window_stack_push(window, true);
}
  
void deinit()
{
  window_destroy(window);
  
  tick_timer_service_unsubscribe();
}
  
int main(void)
{
  init();
  app_event_loop();
  deinit();
}