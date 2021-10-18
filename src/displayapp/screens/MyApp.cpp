#include "MyApp.h"
#include "../DisplayApp.h"
#include <lvgl/lvgl.h>
#include <string>

using namespace Pinetime::Applications::Screens;

MyApp::MyApp(DisplayApp* app) : Screen(app) {
  // format score text
  scoreText = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_width(scoreText, LV_HOR_RES);
  lv_label_set_align(scoreText, LV_ALIGN_IN_LEFT_MID);
  lv_obj_align(scoreText, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 10);
  lv_label_set_recolor(scoreText, true);
  lv_label_set_text_fmt(scoreText, "Score #FFFF00 %i#", score);
};

MyApp::~MyApp() {
  lv_obj_clean(lv_scr_act());
}

bool MyApp::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  score++;
  lv_label_set_text_fmt(scoreText, "Score #FFFF00 %i#", score);
  return true;
}

// #include "MyApp.h"
// #include "displayapp/DisplayApp.h"

// using namespace Pinetime::Applications::Screens;

// MyApp::MyApp(DisplayApp* app) : Screen(app) {
//   lv_obj_t* title = lv_label_create(lv_scr_act(), NULL);  
//   lv_label_set_text_static(title, "My test application");
//   lv_label_set_align(title, LV_LABEL_ALIGN_CENTER);
//   lv_obj_align(title, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);
// }

// MyApp::~MyApp() {
//   lv_obj_clean(lv_scr_act());
// }