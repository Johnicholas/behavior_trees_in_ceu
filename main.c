#include <assert.h>
#include <stdio.h>

static int x_coord = 0;
static int y_coord = 0;
static int x_target = 0;
static int y_target = 0;
static int moving_in_x = 0;
static int moving_in_y = 0;

void move_x(int distance) {
  x_target = x_coord + distance;
  moving_in_x = 1;
}

void move_y(int distance) {
  y_target = y_coord + distance;
  moving_in_y = 1;
}

int x() {
  return x_coord;
}

int y() {
  return y_coord;
}

// #define CEU_DEBUG_TRAILS
#include "_ceu_app.c"

extern void ceu_app_init (tceu_app* app);

int main (int argc, char *argv[])
{
    byte CEU_DATA[sizeof(CEU_Main)];
    tceu_app app;
    app.data = (tceu_org*) &CEU_DATA;
    app.init = &ceu_app_init;

    app.init(&app);
    ceu_sys_go(&app, CEU_IN_START, (tceu_evtp)0);
    while (app.isAlive) {
      if (moving_in_x) {
        if (x_coord < x_target) {
          x_coord += 1;
        } else if (x_coord > x_target) {
          x_coord -= 1;
        } else {
          assert(x_coord == x_target);
          moving_in_x = 0;
          ceu_sys_go(&app, CEU_IN_X_DONE, (tceu_evtp)0);
        }
      }
      if (moving_in_y) {
        if (y_coord < y_target) {
          y_coord += 1;
        } else if (y_coord > y_target) {
          y_coord -= 1;
        } else {
          assert(y_coord == y_target);
          moving_in_y = 0;
          ceu_sys_go(&app, CEU_IN_Y_DONE, (tceu_evtp)0);
        }
      }
    }

    return 0;
}
