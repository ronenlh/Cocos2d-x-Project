# Cocos2d-x-Project

The project uses Cocos2d-x 2.2.6. I had to set the deployment target to 8.0 since it is the minimum allowed in XCode 8, and I had to disable bitcode since there was otherwise a problem with compilation. I also had to compile using libc++.

The code runs on a Simulator and compiles for Generic iOS Devices. However, there's a runtime error when runing on a device that is not caused by my own code and haven't figured out the reason yet.

I tried my best to make the code well-structured and self-documenting. I didn't bothered at all on the visual elements. I made the graphic resources for 2x retina display, so it won't display properly on iPhone 5 and below or the 3x retina. Again, I was less concerned about the graphics than on proper code. 
