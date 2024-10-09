/**
 * @file gui.hpp
 * @author Aryan Gera
 * @brief GUI helper functions
 * @version 0.1.0
 * @date 2023-09-19
 *
 * @copyright Copyright (c) 2023
 *
 */

// This implementation of the LVGL GUI functions is based off
// of Team 81K's. Here is a link to their original implementation article:
// https://team81k.github.io/ProsLVGLTutorial/

#pragma once

#include "display/lv_core/lv_obj.h"

/**
 * @brief Console Object
 */
extern lv_obj_t *console;
/**
 * @brief Text Buffer for Console
 */
extern char buffer[100];

/**
 * @brief Create a Button object
 *
 * @param parent Parent Container
 * @param x X Position of Left Side of Button
 * @param y Y Position of Top Side of Button
 * @param width Width of Button
 * @param height Height of Button
 * @param id Button Unique Identifier
 * @param title Text of Button
 * @return lv_obj_t* Button object
 */
lv_obj_t *createBtn(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height, int id, const char *title);

/**
 * @brief Create a Button Style Object
 *
 * @param copy Base Style Copy
 * @param border Static Border Color
 * @param bodyRel Off Body Color on Released
 * @param bodyPr Off Body Color on Pressed
 * @param bodyTglRel On Body Color on Released
 * @param bodyTglPr On Body Color on Pressed
 * @param textColor Text Color
 * @return lv_style_t* Style Object
 */
lv_style_t *createBtnStyle(lv_style_t *copy, lv_color_t border, lv_color_t bodyRel, lv_color_t bodyPr, lv_color_t bodyTglRel, lv_color_t bodyTglPr, lv_color_t textColor);

/**
 * @brief Set the Button Style object
 *
 * @param btnStyle Style Object
 * @param btn Button Object
 */
void setBtnStyle(lv_style_t *btnStyle, lv_obj_t *btn);

/**
 * @brief Set Button to on or off
 *
 * @param btn Button Object
 * @param toggled Turning button On or Off
 */
void setBtnToggled(lv_obj_t *btn, bool toggled);

/**
 * @brief Initialize GUI
 */
void initGui();