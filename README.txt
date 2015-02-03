mexReadDPX
=======================

Read DPX file in MATLAB using MATLAB MEX functions

=======================

Here I provide two MEX functions to read DPX file in MATLAB,

1. image = mexReadDPX8(filename) 
"mexReadDPX8" reads a 8-bits/10-bits/12-bits/16-bits DPX image from a file specified by the string "filename".
The return value "image" is an H-by-W-by-3 array in format UINT8 containing the image data.
 
2. image = mexReadDPX16(filename) 
"mexReadDPX8" reads a 8-bits/10-bits/12-bits/16-bits DPX image from a file specified by the string "filename".
The return value "image" is an H-by-W-by-3 array in format UINT16 containing the image data.

Function "mexReadDPX8" will compress the input DPX file to 8 bits, that means for each color channel, the color value will range from 0 to 255. But function "mexReadDPX16" will re-range the input DPX file to 16 bits, that means for each color channel, the color value will range from 0 to 65535.

If you don't want to have quality loss, please use "mexReadDPX16".

========================

MEX file generation platform:
1. Window8 x64; 
2. Matlab 2014b x64;
3. Visual Studio 2012

If you are working on other platform, you may need to re-compile 
"mexReadDPX8.mexw64" 
		or 
"mexReadDPX16.mexw64"

Run this in MATLAB command window:
mex mexReadDPX8.cpp DPX.cpp DPXHeader.cpp InStream.cpp Reader.cpp Codec.cpp ElementReadStream.cpp
		or
mex mexReadDPX16.cpp DPX.cpp DPXHeader.cpp InStream.cpp Reader.cpp Codec.cpp ElementReadStream.cpp

=========================

Here I provide two DPX file: 
"imageFromBlackmagic.dpx"
"imageFromWebsite.dpx"

Example of how to use it:
1. add "mexReadDPX8.mexw64" or "mexReadDPX8.mexw64" to your MATLAB searching path.
2. read DPX file in 8 bits:
		imageA = mexReadDPX8('imageFromBlackmagic.dpx');
   Now you get an array in format "1080x1920x3 uint8".
3. display this image: 
		figure;imshow(imageA);
4. read DPX file in 16 bits:
		imageB = mexReadDPX16('imageFromWebsite.dpx');
   Now you get an array in format "1556x2048x3 uint16".
5. display this image: 
		figure;imshow(imageB);
		
		
===========================

This code is based on SMPTE DPX v2 Image Format reader/writer
https://code.google.com/p/dpx/

If you have any question and feedback, please send email to tflsguoyu@gmail.com