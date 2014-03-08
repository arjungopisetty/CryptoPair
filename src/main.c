#include <pebble.h>

Window *window;
TextLayer *exchange_layer, *price_layer;

void handle_init(void) {
	// Create a window and text layer
	window = window_create();
	exchange_layer = text_layer_create(GRect(0, 0, 144, 154));
  price_layer = text_layer_create(GRect(50, 50, 120, 170));
	
	text_layer_set_text(exchange_layer, "Bitstamp");
	text_layer_set_font(exchange_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(exchange_layer, GTextAlignmentCenter);
  
  text_layer_set_text(price_layer, "$600");
	text_layer_set_font(price_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(price_layer, GTextAlignmentCenter);
	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(exchange_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(price_layer));

	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(exchange_layer);
  text_layer_destroy(price_layer);
	
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
