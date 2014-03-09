#include <pebble.h>

Window *window;
TextLayer *currency_layer, *price_layer;

void handle_init(void) {
	// Create a window and text layer
	window = window_create();
	currency_layer = text_layer_create(GRect(0, 0, 144, 154));
  price_layer = text_layer_create(GRect(0, 65, 144, 250));
	
	text_layer_set_text(currency_layer, "Bitcoin");
	text_layer_set_font(currency_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_background_color(currency_layer, GColorClear);
	text_layer_set_text_alignment(currency_layer, GTextAlignmentCenter);
  
  text_layer_set_text(price_layer, "$6000.00");
	text_layer_set_font(price_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
	text_layer_set_text_alignment(price_layer, GTextAlignmentCenter);
	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(currency_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(price_layer));

	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(currency_layer);
  text_layer_destroy(price_layer);
	
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
