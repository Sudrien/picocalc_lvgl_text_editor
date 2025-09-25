/**
 * PicoCalc LVGL Graphics Demo
 * 
 * Demo App Uses LVGL to show demos on the PicoCalc.
 * Implements basic keyboard input and display driver. 
 * 
 * Author: HsuahHanLai
 * https://www.hsuanhanlai.com/
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"


#include "lv_conf.h"
#include "lvgl/lvgl.h"
#include "lv_port_indev_picocalc_kb.h"
#include "lv_port_disp_picocalc_ILI9488.h"
/*#include "lvgl/demos/lv_demos.h"*/


#define ILI9488 1
/*#define USE_DEFAULT_DEMO 0*/

#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) /*will be 2 for RGB565 */


const unsigned int LEDPIN = 25;




// The event handler
static void textarea_event_handler(lv_event_t *e) {
    lv_obj_t *textarea = lv_event_get_target(e);
    printf("Textarea: '%s'\n", lv_textarea_get_text(textarea));
}


int main()
{
    // Initialize standard I/O
    stdio_init_all();

    // Initialize LED
    gpio_init(LEDPIN);
    gpio_set_dir(LEDPIN, GPIO_OUT);

    // Initialize LVGL
    lv_init();

    // Initialize the custom display driver
    lv_port_disp_init();

    // Initialize the keyboard input device (implementation in lv_port_indev_kbd.c)
    lv_port_indev_init();

    // Create a screen
    lv_obj_t *screen = lv_obj_create(NULL);

    //filename label
    lv_obj_t *filename = lv_label_create(screen);
    lv_label_set_text(filename, "filename goes here");
    lv_obj_align(filename, LV_ALIGN_TOP_LEFT, 0, 0);

    // The textarea
    lv_obj_t *input = lv_textarea_create(screen);
    lv_obj_set_width(input, 320);
    lv_obj_set_height(input, 250);    /// 20
    lv_obj_align(input, LV_ALIGN_TOP_LEFT, 0, 20);
    lv_obj_set_style_border_width(input, 0, 0);
    lv_obj_set_style_border_width(input, 0, LV_STATE_FOCUSED);
    lv_obj_set_style_anim_time(input, 1000, LV_PART_CURSOR|LV_STATE_FOCUSED);
    // Textarea event handler
    lv_obj_add_event_cb(input, textarea_event_handler, LV_EVENT_READY, input);


    lv_obj_t *f_key_container = lv_obj_create(screen);
    lv_obj_set_size(f_key_container, 320, 50);
    lv_obj_align(f_key_container, LV_ALIGN_TOP_LEFT, 0, 270);
    lv_obj_set_flex_flow(f_key_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(f_key_container, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // Button labels
    const char* labels[] = {"F1", "F2", "F3", "F4", "F5"};

    // Create 5 buttons
    for(int i = 0; i < 5; i++) {
        lv_obj_t *btn = lv_btn_create(f_key_container);
        lv_obj_set_size(btn, 55, 40);
        
        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, labels[i]);
        lv_obj_center(label);
    }


   // Load the screen
   lv_scr_load(screen);

   // Main loop
   while (1)
   {
       lv_timer_handler();
       lv_tick_inc(20); // Increment LVGL tick by 5 milliseconds
       sleep_ms(5); // Sleep for 5 milliseconds}
   }
}
