#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include <cstdint>
#include "Screen.h"

namespace Pinetime {
  namespace Components {
    class LittleVgl;
  }
  namespace Applications {
    namespace Screens {

      class MyApp : public Screen {
      public:
        MyApp(DisplayApp* app);
        ~MyApp() override;

        // void Refresh() override;

        bool OnTouchEvent(TouchEvents event) override;

      private:
        unsigned int score = 0;
        lv_obj_t* scoreText;
      };
    }
  }
}

// #pragma once

// #include "displayapp/screens/Screen.h"
// #include <lvgl/lvgl.h>

// namespace Pinetime {
//   namespace Applications {
//     namespace Screens {
//       class MyApp : public Screen {
//       public:
//         MyApp(DisplayApp* app);
//         ~MyApp() override;
//       };
//     }
//   }
// }