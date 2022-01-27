# Mandelbrot Zoom Generator

This is a program which genrates videos of mandelbrot zooms. The io is done in python with pygame, 
and the calculations are done in c++. The c++ library easy bmp is used to genrate bmp images, and 
the program ffmpeg is used to compress the images into a movie. 

You will need to download ffmpeg, and the python libraries scipy, and pygame. To run the program 
run pathPicker.py. This will prompt you for input in the terminal, and then display a window. The 
window will let you explore the mandelbrot set visualy and pick a path for the movie generator to follow. 
To change the center of the frame without zooming click on the new center point. To change the center 
while zooming in hold 'i' while clicking. To zoom out hold 'o' while clicking. When you are done choosing
your zoom path press d. The IO window will close and the terminal will start displaying percentages letting 
you know how far along the video genration is. When the video has finished generating the movie will be saved
to the movie clips folder, and the program will open it for you to play. 

If you are running into problems here are some tips: 
- pygame doesn't like python environments, I have to run it on the base environment to get it to work properly
- pygame has several non python dependencies: brew install sdl sdl_image sdl_mixer sdl_ttf portmidi mercurial 
- Sometimes base pygame doesn't work on new operating systems: pip3 install pygame==2.0.0.dev12
- make sure that all the folders and text files are in the same position as they are in the git repository
they are writen to by the program and are very important
