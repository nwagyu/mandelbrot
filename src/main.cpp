#include "eadkpp.h"
#include <complex>
#include <cmath>

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Mandelbrot";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

using namespace std::complex_literals;

constexpr int TileSize = 10;

void mandelbrot(int iteration, float centerX, float centerY, float zoom) {
  EADK::Display::Color tile[TileSize*TileSize];

  for (int tileX=0; tileX<EADK_SCREEN_WIDTH/TileSize; tileX++) {
    for (int tileY=0; tileY<EADK_SCREEN_HEIGHT/TileSize; tileY++) {
      for (int offsetX=0; offsetX<TileSize; offsetX++) {
        for (int offsetY=0; offsetY<TileSize; offsetY++) {
          int x = tileX*TileSize + offsetX;
          int y = tileY*TileSize + offsetY;

          std::complex<float> z = 0;
          std::complex<float> c = (3.5f*(x+centerX)/319.f-2.5f)/zoom + 1if*(-2.5f*(y+centerY)/221.f+1.25f)/zoom;
          int i=0;
          while (i < iteration && abs(z) < 2) {
            i++;
            z = z*z+c;
            float rgb = 255.0f*i/iteration;
            tile[offsetY*TileSize+offsetX] = EADK::Display::Color(rgb);
          }
        }
      }
      EADK::Display::pushRect(EADK::Display::Rect(tileX*TileSize,tileY*TileSize,TileSize,TileSize), tile);
    }
  }
  eadk_timing_msleep(1000);
}

int main(int argc, const char * argv[]) {
  int iteration = 10;
  int moveStep = 20;
  float centerX = 0.0f;
  float centerY = 0.0f;
  float zoom = 1.0f;

  mandelbrot(iteration, centerX, centerY, zoom);
  while (true) {
    int32_t timeout = 1000;
    eadk_event_t ev = eadk_event_get(&timeout);
    switch(ev) {
      case eadk_event_left:
        centerX -= moveStep*zoom;
        mandelbrot(iteration, centerX, centerY, zoom);
        break;
      case eadk_event_right:
        centerX += moveStep*zoom;
        mandelbrot(iteration, centerX, centerY, zoom);
        break;
      case eadk_event_up:
        centerY -= moveStep*zoom;
        mandelbrot(iteration, centerX, centerY, zoom);
        break;
      case eadk_event_down:
        centerY += moveStep*zoom;
        mandelbrot(iteration, centerX, centerY, zoom);
        break;
      case eadk_event_plus:
        zoom *= 1.5f;
        mandelbrot(iteration, centerX, centerY, zoom);
        break;
      case eadk_event_minus:
        zoom /= 1.5f;
        mandelbrot(iteration, centerX, centerY, zoom);
        break;
      case eadk_event_lower:
        if (iteration > 1) {
          iteration--;
        }
        mandelbrot(iteration, centerX, centerY, zoom);
        break;
      case eadk_event_greater:
        iteration++;
        mandelbrot(iteration, centerX, centerY, zoom);
        break;
    }
  }
}
