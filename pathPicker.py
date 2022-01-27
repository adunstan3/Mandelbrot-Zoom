# import the pygame module, so you can use it
import pygame
import os
import platform
import subprocess
from subprocess import Popen, PIPE, check_output

from pathSmoother import *

# define a main function
def main():
    #Get user specifications for movie: Width, Height, Name
    print("Please input the image dimentions in pixels width then height as an int")
    print("Width:")
    width = int(input())
    print("Height:")
    height = int(input())
    print("Please input the name of your movie as a string no spaces:")
    movieName = input()

    #set starting conditions
    centerReal = -0.5
    centerImag = 0.0
    widthReal = 4.0
    frameRate = 30
    zoomSpeed = 1.0
    heightImag = (float(height)/width) * widthReal

    #write starting conditions to files
    f = open("frameCordinates.txt", "w")
    f.write(str(width)+", "+str(height)+", "+str(frameRate)+", "+str(zoomSpeed)+", "+str(movieName)+",\n")
    f.close()

    f = open("targets.txt", "w")
    f.write(str(width)+", "+str(height)+", "+str(frameRate)+", "+str(zoomSpeed)+", "+str(movieName)+",")
    f.write("\n{:.30f}, {:.30f}, {:.30f},".format(centerReal, centerImag, widthReal))
    f.close()

    #Generate the starting image
    p = Popen(['./Generate_Image'], shell=True, stdout=PIPE, stdin=PIPE)
    print(p.stdout.read())

    #Start the pygame window
    pygame.init()
    pygame.display.set_caption("Mandelbrot Zoom Path Picker")
    screen = pygame.display.set_mode((width,height))

    currentFrame = pygame.image.load("testFrame.bmp")
    currentFrameRect = currentFrame.get_rect()

    #Start the path picking main loop
    running = True
    while running:
        for event in pygame.event.get():
            # only do something if the event is of type QUIT
            if event.type == pygame.QUIT:
                running = False

            if event.type == pygame.MOUSEBUTTONDOWN:
                x, y = pygame.mouse.get_pos()
                print(x, y)

                #window cordinates +/- are not the same as complext plane cordinates +/-
                #we find the distance from the center of the screen the click was in pixels
                #then we divide by the screen dimentions to find percentage change which we multiply
                #by the frame dimentions to find the actual change
                centerReal += ((x - (width/2.0)) / width) * widthReal
                centerImag += (((height/2.0) - y) / height) * heightImag

                #check what key is pressed when the mouse is clicked
                keys=pygame.key.get_pressed()
                if keys[pygame.K_i]:
                    #The i key is pressed and the user wants to zoom in
                    widthReal *= .5
                    heightImag *= .5
                elif keys[pygame.K_o]:
                    #The o key is pressed and the user wants to zoom out
                    widthReal *= 2
                    heightImag *= 2

                #write the chosen target to the file
                f = open("targets.txt", "a")
                f.write("\n{:.30f}, {:.30f}, {:.30f},".format(centerReal, centerImag, widthReal))
                f.close()

                #generate the new frame for the screen and display it
                p = Popen(['./Generate_Image'], shell=True, stdout=PIPE, stdin=PIPE)
                print(p.stdout.read())
                currentFrame = pygame.image.load("testFrame.bmp")

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_z:
                    #the user pressed z and wants to undo the last action
                    #delete the last line of the file
                    f = open("targets.txt", "r")
                    lines = f.readlines()
                    f.close()

                    print(lines)

                    #Dont let the user delete the starting frame
                    if len(lines)>2:
                        #Write the new lines to the file
                        lines = lines[:-1]
                        #strip the end line off the end of the last line
                        lastLine = lines[-1]
                        lastLine = lastLine[:-1]
                        lines[-1] = lastLine
                        f = open("targets.txt", "w")
                        for line in lines:
                            f.write(line)
                        f.close()

                        #reset the frame variables to the old values
                        newValues = lines[-1]
                        newValues = newValues[:-2] #cut out the endline and ,
                        valuesArray = newValues.split(", ")
                        #convert strings to numbers and calculate the new heightImag
                        centerReal = float(valuesArray[0])
                        centerImag = float(valuesArray[1])
                        widthReal = float(valuesArray[2])
                        heightImag = (float(height)/width) * widthReal

                    #refresh the image on the screen
                    p = Popen(['./Generate_Image'], shell=True, stdout=PIPE, stdin=PIPE)
                    print(p.stdout.read())
                    currentFrame = pygame.image.load("testFrame.bmp")

                if event.key == pygame.K_d:
                    #The user has typed d so they are done. Shut down the route picker
                    running = False

        #refresh the screen and get ready for the next interaction
        screen.fill((0,0,0))
        screen.blit(currentFrame, currentFrameRect)
        pygame.display.flip()

    #Shut down the pygame window
    pygame.display.quit()
    pygame.quit()

    #The user has finished picking their route now turn the target path into frame cordinates
    smoothPath()

    #The smoothed path frame cordinates have been generated now generate the frames and turn them
    #into a movie with the c++ .exe
    os.system('./Generate_Movie')
    #p = Popen(['./Generate_Movie'], shell=True, stdout=None, stdin=PIPE)

    print("Your movie {} is done!".format(movieName))
    #open the finished movie!
    os.system('open movieClips/{}.mpg'.format(movieName))



if __name__=="__main__":
    main()
