#include "MyApp.h"
#include "../DisplayApp.h"
#include <lvgl/lvgl.h>
#include <string>
#include <random>

using namespace Pinetime::Applications::Screens;

static void btn_event_handler(lv_obj_t* obj, lv_event_t event) {
  auto myApp = static_cast<MyApp*>(obj->user_data);
  myApp->btnEventHandler(obj, event);
}

MyApp::MyApp(DisplayApp* app, Controllers::MotorController& motorController)
  : Screen(app), motorController {motorController} {

  srand (time (NULL));
  // srand(123);

  // format score text
  scoreText = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_width(scoreText, LV_HOR_RES);
  lv_label_set_align(scoreText, LV_ALIGN_IN_LEFT_MID);
  lv_obj_align(scoreText, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 10);
  lv_label_set_recolor(scoreText, true);
  lv_label_set_text_fmt(scoreText, "Score #FFFF00 %i#", score);

  // Set button styles
  static lv_style_t styleRed;
  lv_style_init(&styleRed);
  lv_style_set_bg_color(&styleRed, LV_STATE_DEFAULT, LV_COLOR_RED);
  lv_style_set_border_width(&styleRed, LV_STATE_DEFAULT, 2);
  lv_style_set_border_color(&styleRed, LV_STATE_DEFAULT, LV_COLOR_WHITE);

  // static lv_style_t styleBlue;
  lv_style_init(&styleBlue);
  lv_style_set_bg_color(&styleBlue, LV_STATE_DEFAULT, LV_COLOR_BLUE);
  lv_style_set_border_width(&styleBlue, LV_STATE_DEFAULT, 2);
  lv_style_set_border_color(&styleBlue, LV_STATE_DEFAULT, LV_COLOR_WHITE);

  // static lv_style_t styleGreen;
  lv_style_init(&styleGreen);
  lv_style_set_bg_color(&styleGreen, LV_STATE_DEFAULT, LV_COLOR_GREEN);
  lv_style_set_border_width(&styleGreen, LV_STATE_DEFAULT, 2);
  lv_style_set_border_color(&styleGreen, LV_STATE_DEFAULT, LV_COLOR_WHITE);

  // static lv_style_t styleYellow;
  lv_style_init(&styleYellow);
  lv_style_set_bg_color(&styleYellow, LV_STATE_DEFAULT, LV_COLOR_YELLOW);
  lv_style_set_border_width(&styleYellow, LV_STATE_DEFAULT, 2);
  lv_style_set_border_color(&styleYellow, LV_STATE_DEFAULT, LV_COLOR_WHITE);

  // Create buttons
  btnRed = lv_btn_create(lv_scr_act(), nullptr);
  btnRed->user_data = this;
  lv_obj_add_style(btnRed, LV_STATE_DEFAULT, &styleRed);
  lv_obj_set_event_cb(btnRed, btn_event_handler);
  lv_obj_set_height(btnRed, 90);
  lv_obj_set_width(btnRed, 90);
  lv_obj_align(btnRed, lv_scr_act(), LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);

  btnBlue = lv_btn_create(lv_scr_act(), nullptr);
  btnBlue->user_data = this;
  lv_obj_add_style(btnBlue, LV_STATE_DEFAULT, &styleBlue);
  lv_obj_set_event_cb(btnBlue, btn_event_handler);
  lv_obj_set_height(btnBlue, 90);
  lv_obj_set_width(btnBlue, 90);
  lv_obj_align(btnBlue, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, 0, 60);

  btnGreen = lv_btn_create(lv_scr_act(), nullptr);
  btnGreen->user_data = this;
  lv_obj_add_style(btnGreen, LV_STATE_DEFAULT, &styleGreen);
  lv_obj_set_event_cb(btnGreen, btn_event_handler);
  lv_obj_set_height(btnGreen, 90);
  lv_obj_set_width(btnGreen, 90);
  lv_obj_align(btnGreen, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 60);

  btnYellow = lv_btn_create(lv_scr_act(), nullptr);
  btnYellow->user_data = this;
  lv_obj_add_style(btnYellow, LV_STATE_DEFAULT, &styleYellow);
  lv_obj_set_event_cb(btnYellow, btn_event_handler);
  lv_obj_set_height(btnYellow, 90);
  lv_obj_set_width(btnYellow, 90);
  lv_obj_align(btnYellow, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

  updatePattern();
  startTime = xTaskGetTickCount();
  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
}

MyApp::~MyApp() {
  lv_task_del(taskRefresh);
  lv_obj_clean(lv_scr_act());
}

void MyApp::updatePattern() {
  pattern.push_back(rand() % 4);
  input_idx = 0;
  playing_pattern = true;
}

void MyApp::Refresh() {
  if (playing_pattern) {
    switch (pattern[input_idx]) {
      case 0:
        flashBtn(btnRed, LV_COLOR_RED);
      case 1:
        flashBtn(btnBlue, LV_COLOR_BLUE);
      case 2:
        flashBtn(btnGreen, LV_COLOR_GREEN);
      case 3:
        flashBtn(btnYellow, LV_COLOR_YELLOW);
    }
    if (input_idx == pattern.size()) {
      playing_pattern = false;
      input_idx = 0;
    }
  }
}

void MyApp::flashBtn(lv_obj_t* btn, lv_color_t color) {
  if (xTaskGetTickCount() - startTime > configTICK_RATE_HZ / static_cast<uint16_t>(2) && !blink) {
    startTime = xTaskGetTickCount();
    lv_obj_set_style_local_bg_color(btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    blink = true;
  } else if (xTaskGetTickCount() - startTime > configTICK_RATE_HZ / static_cast<uint16_t>(2) && blink) {
    startTime = xTaskGetTickCount();
    input_idx++;
    lv_obj_set_style_local_bg_color(btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
    blink = false;
  }
}

void MyApp::btnEventHandler(lv_obj_t* btn, lv_event_t event) {
  if (event != LV_EVENT_CLICKED) {
    return;
  }
  if (playing_pattern) {
    return;
  }
  motorController.RunForDuration(10);
  bool correct = checkCorrect(btn);
  if (input_idx < pattern.size() && correct) {
    input_idx++;
  }
  if (input_idx == pattern.size() && correct) {
    score++;
    lv_label_set_text_fmt(scoreText, "Score #FFFF00 %i#", score);
    updatePattern();
  }
  if (!correct){
    // Wrong answer
    score = 0;
    lv_label_set_text_fmt(scoreText, "Score #FFFF00 %i#", score);
    pattern.clear();
    updatePattern();
  }
}

bool MyApp::checkCorrect(lv_obj_t* btn){
  if (btn == btnRed){
    if (pattern[input_idx] == 0){
      return true;
    }
  } else if(btn == btnBlue){
    if (pattern[input_idx] == 1){
      return true;
    }
  } else if(btn == btnGreen){
    if (pattern[input_idx] == 2){
      return true;
    }
  } else if(btn == btnYellow){
    if (pattern[input_idx] == 3){
      return true;
    }
  }
  return false;
}