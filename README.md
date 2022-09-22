# Mandelbrot

[![Build](https://github.com/nwagyu/mandelbrot/actions/workflows/build.yml/badge.svg)](https://github.com/nwagyu/mandelbrot/actions/workflows/build.yml)

This is an app that will draw the [Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set) on your NumWorks calculator.

## About this app

This app uses the same algorithm as the sample `mandelbrot.py` Python script that ships with the NumWorks calculator. But it is roughly 100x faster!

## Install the app

Installing is rather easy:
1. Download the latest `mandelbrot.nwa` file from the [Releases](https://github.com/nwagyu/mandelbrot/releases) page
2. Head to [my.numworks.com/apps](https://my.numworks.com/apps) to send the `nwa` file on your calculator

## How to use the app

Well, there isn't much to do. Just launch it and watch. You can press the "Home" button to exit.

## Build and run the app

To build this sample app, you will need to install the [embedded ARM toolchain](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain) and [nwlink](https://www.npmjs.com/package/nwlink).

```shell
brew install numworks/tap/arm-none-eabi-gcc node # Or equivalent on your OS
npm install -g nwlink
make run
```
