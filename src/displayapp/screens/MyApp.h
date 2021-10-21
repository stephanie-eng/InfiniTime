#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include "systemtask/SystemTask.h"
#include <cstdint>
#include <vector>
#include "Screen.h"
#include "components/motor/MotorController.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {

      class MyApp : public Screen {
      public:
        MyApp(DisplayApp* app, Controllers::MotorController& motorController); 
        ~MyApp() override;

        void Refresh() override;
        void btnEventHandler(lv_obj_t* btn, lv_event_t event);

      private:
        bool playing_pattern = true;
        bool blink = false;
        TickType_t startTime = 0;
        unsigned int score = 0;
        unsigned int input_idx = 0;
        lv_style_t styleRed, styleBlue, styleGreen, styleYellow, styleWhite;
        lv_obj_t* scoreText, *btnRed, *btnBlue, *btnGreen, *btnYellow;
        std::vector<int> pattern;

        Controllers::MotorController& motorController;
        lv_task_t* taskRefresh;
        
        void updatePattern();
        void flashBtn(lv_obj_t* btn, lv_color_t color);
        bool checkCorrect(lv_obj_t* btn);
      };
    }
  }
}

