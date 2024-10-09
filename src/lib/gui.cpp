/**
 * @file gui.cpp
 * @author Aryan Gera
 * @brief Definition of GUI helper function
 * @version 0.1.0
 * @date 2023-11-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "lib/gui.hpp"
#include "config.hpp"
#include "display/lv_misc/lv_color.h"
#include "lib/auton.hpp"

#include "display/lv_objx/lv_btn.h"
#include "display/lv_objx/lv_label.h"
#include <cstdlib>

// #include "logo.c"

lv_obj_t *createBtn(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height, int id, const char *title) {
  lv_obj_t *btn = lv_btn_create(parent, NULL);
  lv_obj_set_pos(btn, x, y);
  lv_obj_set_size(btn, width, height);
  lv_obj_set_free_num(btn, id);

  lv_obj_t *label = lv_label_create(btn, NULL);
  lv_label_set_text(label, title);
  lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

  return btn;
}

lv_style_t *createBtnStyle(lv_style_t *copy, lv_color_t border, lv_color_t bodyRel, lv_color_t bodyPr, lv_color_t bodyTglRel, lv_color_t bodyTglPr, lv_color_t textColor) {
  lv_style_t *btnStyle = (lv_style_t *)std::malloc(sizeof(lv_style_t) * 4);
  for (int i = 0; i < 4; i++)
    lv_style_copy(&btnStyle[i], copy);

  btnStyle[0].body.border.width = 2;
  btnStyle[0].body.border.color = border;
  btnStyle[0].body.main_color = bodyRel;
  btnStyle[0].body.grad_color = bodyRel;
  btnStyle[0].text.color = textColor;

  btnStyle[1].body.border.width = 2;
  btnStyle[1].body.border.color = border;
  btnStyle[1].body.main_color = bodyPr;
  btnStyle[1].body.grad_color = bodyPr;
  btnStyle[1].text.color = textColor;

  btnStyle[2].body.border.width = 2;
  btnStyle[2].body.border.color = border;
  btnStyle[2].body.main_color = bodyTglRel;
  btnStyle[2].body.grad_color = bodyTglRel;
  btnStyle[2].text.color = textColor;

  btnStyle[3].body.border.width = 2;
  btnStyle[3].body.border.color = border;
  btnStyle[3].body.main_color = bodyTglPr;
  btnStyle[3].body.grad_color = bodyTglPr;
  btnStyle[3].text.color = textColor;

  return btnStyle;
}

void setBtnStyle(lv_style_t *btnStyle, lv_obj_t *btn) {
  lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btnStyle[0]);
  lv_btn_set_style(btn, LV_BTN_STYLE_PR, &btnStyle[1]);
  lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &btnStyle[2]);
  lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &btnStyle[3]);
}

void btnSetToggled(lv_obj_t *btn, bool toggled) {
  if (toggled != (lv_btn_get_state(btn) >= 2))
    lv_btn_toggle(btn);
}

// lv_obj_t *btnRed = createBtn(lv_scr_act(), 240, 0, 120, 60, 100, "Red");
// lv_obj_t *btnBlue = createBtn(lv_scr_act(), 360, 0, 120, 60, 101, "Blue");

lv_obj_t *btnFarQ = createBtn(lv_scr_act(), 0, 0, 240, 40, 0, "Close Qual Half WP");
lv_obj_t *btnCloseQ = createBtn(lv_scr_act(), 0, 40, 240, 40, 1, "Close Elim Bowl");
// lv_obj_t *btnFarE = createBtn(lv_scr_act(), 320, 0, 80, 40, 2, "C Rush Top");
// lv_obj_t *btnCloseE = createBtn(lv_scr_act(), 320, 40, 80, 40, 3, "6 Ball HWP");
lv_obj_t *btnAwp = createBtn(lv_scr_act(), 240, 0, 240, 40, 4, "6 Rush Mid Ball");
lv_obj_t *btnSkills = createBtn(lv_scr_act(), 240, 40, 240, 40, 5, "6 Rush Wing Slap");

// Config Colors
lv_color_t border_color = LV_COLOR_MAKE(86, 109, 140);
lv_color_t bg_pressed = LV_COLOR_MAKE(86 / 2, 109 / 2, 140 / 2);
lv_color_t bg_static = LV_COLOR_MAKE(0, 0, 0);
lv_color_t text_color = LV_COLOR_MAKE(255, 255, 255);

lv_style_t *style = createBtnStyle(&lv_style_plain, border_color, bg_static, bg_pressed, border_color, border_color, text_color);

// lv_obj_t *logObj = lv_img_create(lv_scr_act(), NULL);
// LV_IMG_DECLARE(logo);

void refreshButtons() {

  // btnSetToggled(btnRed, false);
  // btnSetToggled(btnBlue, false);

  btnSetToggled(btnFarQ, false);
  // btnSetToggled(btnFarE, false);
  btnSetToggled(btnCloseQ, false);
  // btnSetToggled(btnCloseE, false);
  btnSetToggled(btnAwp, false);
  btnSetToggled(btnSkills, false);

  switch (auton) {
  case 0:
    btnSetToggled(btnSkills, true);
    break;
  case 1:
    btnSetToggled(btnFarQ, true);
    break;
  case 2:
    btnSetToggled(btnCloseQ, true);
    break;
  case 3:
    // btnSetToggled(btnFarE, true);
    break;
  case 4:
    // btnSetToggled(btnCloseE, true);
    break;
  case 5:
    btnSetToggled(btnAwp, true);
    break;
  }

  // switch (color) {
  // case 0:
  //   btnSetToggled(btnRed, true);
  //   break;
  // case 1:
  //   btnSetToggled(btnBlue, true);
  //   break;
  // }
}

static lv_res_t btn_click_action(lv_obj_t *btn) {

  uint8_t id = lv_obj_get_free_num(btn);

  if (id > 99) {
    // color = id % 100;
    // btnSetToggled(btnRed, false);
    // btnSetToggled(btnBlue, false);
  } else {
    auton = id;
    btnSetToggled(btnFarQ, false);
    // btnSetToggled(btnFarE, false);
    btnSetToggled(btnCloseQ, false);
    // btnSetToggled(btnCloseE, false);
    btnSetToggled(btnAwp, false);
    btnSetToggled(btnSkills, false);
  }
  btnSetToggled(btn, true);

  return LV_RES_OK;
}

char buffer[100];
lv_obj_t *console;

// void autonLimTaskDef(void *param) {
//   int val, prevVal;
//   while (true) {
//     val = ((autonPoten.get_value() + 256) % 4096) / 512;
//     auton = val;
//     if (auton > 5) {
//       auton = 0;
//     }
//     if (prevVal != val) {
//       refreshButtons();
//     }
//     prevVal = val;
//     pros::delay(100);
//   }
// };

void initGui() {
  // pros::Task autonLimTask(autonLimTaskDef);
  console = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(console, "");
  lv_obj_align(console, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 0);

  // lv_img_set_src(logObj, &logo);
  // lv_obj_set_pos(logObj, 0, 0);

  // setBtnStyle(style, btnRed);
  // setBtnStyle(style, btnBlue);
  setBtnStyle(style, btnFarQ);
  // setBtnStyle(style, btnFarE);
  setBtnStyle(style, btnCloseQ);
  // setBtnStyle(style, btnCloseE);
  setBtnStyle(style, btnAwp);
  setBtnStyle(style, btnSkills);

  // // lv_btn_set_action(btnRed, LV_BTN_ACTION_CLICK, btn_click_action);
  // // lv_btn_set_action(btnBlue, LV_BTN_ACTION_CLICK, btn_click_action);
  // // lv_btn_set_action(btnFarE, LV_BTN_ACTION_CLICK, btn_click_action);
  // // lv_btn_set_action(btnCloseE, LV_BTN_ACTION_CLICK, btn_click_action);

  // lv_btn_set_action(btnFarQ, LV_BTN_ACTION_CLICK, btn_click_action);
  // lv_btn_set_action(btnCloseQ, LV_BTN_ACTION_CLICK, btn_click_action);
  // lv_btn_set_action(btnAwp, LV_BTN_ACTION_CLICK, btn_click_action);
  // lv_btn_set_action(btnSkills, LV_BTN_ACTION_CLICK, btn_click_action);

  refreshButtons();
}