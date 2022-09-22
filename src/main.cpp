#include "eadkpp.h"
#include <complex>
#include <cmath>

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Mandelbrot";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

using namespace std::complex_literals;

constexpr int DisplayWidth = 320;
constexpr int DisplayHeight = 240;
constexpr int TileSize = 10;

int main(int argc, const char * argv[]) {
  int iteration = 10;

  EADK::Display::Color tile[TileSize*TileSize];

  for (int tileX=0; tileX<320/TileSize; tileX++) {
    for (int tileY=0; tileY<240/TileSize; tileY++) {
      for (int offsetX=0; offsetX<TileSize; offsetX++) {
        for (int offsetY=0; offsetY<TileSize; offsetY++) {
          int x = tileX*TileSize + offsetX;
          int y = tileY*TileSize + offsetY;

          std::complex<float> z = 0;
          std::complex<float> c = (3.5f*x/319.f-2.5f) + 1if*(-2.5f*y/221.f+1.25f);
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
