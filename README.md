# MJPEGStreamer

This program is a example of cpp-mjpeg-streamer for Ubuntu22.04 and M5UnitV2.
https://github.com/nadjieb/cpp-mjpeg-streamer

### Compile
For Ubuntu

```
% cmake -B build/x64 -DTARGET_COMPILE=x64 .
% cmake --build build/x64
% ./bin/x64/mpegstreamer
```

For M5UnitV2(ARM)
```
% rm CMakeCache.txt 
% cmake -B build/arm -DTARGET_COMPILE=arm .
% cmake --build build/arm
% ./bin/x64/mpegstreamer
```
