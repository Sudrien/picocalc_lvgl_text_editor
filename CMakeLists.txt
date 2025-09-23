cmake_minimum_required(VERSION 3.16)

# Setup board for Pico 1
# set(PICO_BOARD pico)

# Setup board for Pico 2W
set(PICO_BOARD pico2)

include(pico_sdk_import.cmake)

project(picocalc_lvgl_text_editor)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}
)



add_subdirectory(i2ckbd)
add_subdirectory(lcdspi)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/lvgl lvgl)


add_executable(picocalc_lvgl_text_editor
    main.c
    lv_port_indev_picocalc_kb.c
    lv_port_disp_picocalc_ILI9488.c
)

target_compile_options(picocalc_lvgl_text_editor PRIVATE -DPICOMITE
										-DPICO_HEAP_SIZE=0x1000 
										-DGUICONTROLS
										-DPICO_CORE0_STACK_SIZE=0x1000
										)

target_compile_definitions(picocalc_lvgl_text_editor PRIVATE LV_USE_DEMO_WIDGETS=1)

target_include_directories(picocalc_lvgl_text_editor PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/lib/lvgl/lvgl
    ${CMAKE_CURRENT_LIST_DIR}/lib/lvgl/lvgl/src
    ${CMAKE_CURRENT_LIST_DIR}/lib/lvgl/lvgl/demos
)


target_link_libraries(picocalc_lvgl_text_editor
  pico_stdlib
  hardware_flash
  hardware_irq
  hardware_adc
  hardware_pwm
  hardware_i2c
  hardware_spi
  hardware_dma
  hardware_exception
  hardware_pio
  pico_multicore
  i2ckbd
  lcdspi
  lvgl
  lvgl_demos
)

pico_enable_stdio_usb(picocalc_lvgl_text_editor 0)
pico_enable_stdio_uart(picocalc_lvgl_text_editor 1)
pico_add_extra_outputs(picocalc_lvgl_text_editor)
