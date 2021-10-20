#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include "systemtask/SystemTask.h"
#include <cstdint>
#include <vector>
#include "Screen.h"

namespace Pinetime {
  // namespace Components {
  //   class LittleVgl;
  // }
  namespace Applications {
    namespace Screens {

      class MyApp : public Screen {
      public:
        MyApp(DisplayApp* app);
        ~MyApp() override;

        void Refresh() override;
        void updatePattern();
        void btnRedEventHandler(lv_event_t event);

      private:
        bool playing_pattern = true;
        TickType_t startTime = 0;
        unsigned int score = 0;
        unsigned int input_idx = 0;
        lv_style_t styleRed, styleBlue, styleGreen, styleYellow, styleWhite;
        lv_obj_t* scoreText, *btnRed, *btnBlue, *btnGreen, *btnYellow;
        std::vector<int> pattern;

      };
    }
  }
}

