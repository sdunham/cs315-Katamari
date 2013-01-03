cs315-Katamari
==============

Simple game created for CS315 (Computer Graphics), inspired by Katamari and Osmos.

##ABOUT OUR GAME
This game is a rough copy of Katamari Damacy, in which the player's character runs around a cityscape pushing a sphere-like object (called a "Katamari"). As your Katamari comes into contact with objects which are smaller than it, those objects "stick" to your Katamari and increase its overall diameter. If you run into objects which are larger than you, objects which you have collected previously are knocked off thus decreasing your overall diameter. The ultimate goal of Katamari Damacy is to reach a target diameter in each stage.

In our version of the game, the mechanics are somewhat simplified (and inspired by another game called Osmos). All objects which can affect the size of your "Katamari" are spheres. If your sphere (colored blue) intersects with a smaller "enemy" sphere (colored red or green), part of the overlap distance between the two spheres is added to the radius of the larger colliding sphere and removed from the smaller. Enemy spheres are colored green if your sphere is larger than them, and red if it is smaller. The goal of our game is to "collect" the radii of all enemy spheres (i.e. radius of all enemy spheres == 0). If the radius of your sphere drops to 0, you lose.

##CONTROLS
* Arrow Keys: Move your sphere around the city
* "a": Toggle between birds-eye and third-person camera modes
* Left Mouse Button:  Click and drag to rotate camera in birds-eye view
* Right Mouse Button:	Click and drag to zoom camera in/out in birds-eye view
* "1": Set difficulty to easy (fewest enemy spheres)
* "2": Set difficulty to medium (more enemy spheres)
* "3": Set difficulty to hard (LOTS of enemy spheres)
* "4": Enable super-secret techno mode (LOTS of enemy spheres, strobe lights, and fog enabled)
* "r": Reset game (your sphere and enemies)
* "f": Toggle scene fog (for added difficulty!)
* Escape Key: Exit the game

##FEATURES OF NOTE
* Phong shaded enemy spheres
* Background music and win/lose scenario sounds
* Player's Katamari emits spotlight (in addition to scene light)
* Texture-mapped model of a warning sign/barrier
* 3 difficulty settings, and super secret techno mode
* Tobor makes an appearance! 

##COMPATABLE PLATFORMS
This game was developed and tested on a Windows PC. Other platforms are not guaranteed to work properly (or at all).

##Installing & Playing the Game
1. **Install OpenGL**
You need not do anything for this step; OpenGL v1.1 software runtime is already included as part of the operating system for Windows 7, WinXP, Windows 2000, Windows 98, Windows 95 (OSR2) and Windows NT.
2. **Install GLUT**
The first step is to download GLUT. The necessary files are included in `installation/glut-3.7.6-bin.zip` or at the following URL:
http://www.xmission.com/~nate/glut/glut-3.7.6-bin.zip
3. **Copy the libraries and header files into their proper locations.**
*If you are running a 64-bit operating system (XP 64, Vista 64, or Windows 7 64):*
* Copy glut32.dll into "c:\Windows\SysWOW64"
* Copy glut.h into "c:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Include\gl\"
* Copy glut32.lib into "c:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Lib\"
*If you are running a 32-bit operating system:*
* Copy glut32.dll into c:\Windows\System
* Copy glut.h into "c:\Program Files\Microsoft SDKs\Windows\v7.0A\Include\gl\"
* Copy glut32.lib into "c:\Program Files\Microsoft SDKs\Windows\v7.0A\Lib"
4. **Run the game by running `\Katamari\Katamari.exe`**

##ONLINE RESOURCES CONSULTED
Texture-Mapped Meshes: http://nehe.gamedev.net/tutorial/model_loading/16004/
Simple Sphere-Sphere Collision Detection: http://www.swiftless.com/tutorials/opengl/collision.html
http://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/lighting.php
http://www.opengl.org/registry/doc/GLSLangSpec.Full.1.20.8.pdf
http://www.opengl.org/resources/libraries/glut/spec3/node54.html  - helped with implementing special keys
http://nehe.gamedev.net/tutorial/cool_looking_fog/19001/ - helped with fog

##CREATED BY
Scott Dunham, Selah-Mae Ross, Aimee Savage

##KNOWN BUGS
"There are no bugs, only features."
