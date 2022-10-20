Arkanoid game based on task provided by Dragons Lake on their Framework.

Rules
It is required to use our framework. We do not accept solutions created using other
libraries (like SFML, SDL2 etc). Functionality provided by Framework should be enough to
do all required drawing. You can load TGA, JPG and PNG images as sprites with it.
We have included all necessary assets in the folder “Data”. You can use these or any
other assets which you want.
Window size should be possible to set from the command-line, e.g.: game -window
800x600
Overview
The player controls a platform which can move left and right. The goal is to destroy all
blocks by deflecting the ball with the platform.
Note: it is not required to make level switching for this task (one game level is enough).
However, you can make more levels if you want.
Player
The player can move a platform using left and right arrow keyboard buttons. Initially the
player can choose the angle of the ball by pressing the left mouse button (the ball should be
launched in the direction of the mouse cursor).
Ball
The ball moves linearly with a constant speed. It reflects from edges, blocks and the
player's platform.
Environment
The level consists of blocks, which could be destroyed by a single hit. The ball should
reflect from blocks after their destruction.
Win/loss conditions
The player loses when the ball is not caught by the platform. Victory can be achieved by
destroying all blocks and catching the ball with the platform after.
The game should be restarted after victory/loss.

https://user-images.githubusercontent.com/106614474/196943648-67fbeea8-750f-4887-ae0e-5bed32337a02.mp4
