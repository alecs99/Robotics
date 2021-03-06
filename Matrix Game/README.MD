# **Pong Game**
## **Description**<br>
Pong is a 2 player game similar to table tennis which features two paddles and a ball. You also have a number of lives (depends of the level you play). The game ends when one of a player loses all of his lives or after 60 seconds of gameplay. The winner is the player which has the highest score. Note: The player who has lives and the end of the game will receive a bonus (depending on the level you play). You get a point if the ball reached opponent's side without him touching it with his paddle.  <br>
There are multiple levels you can try: <br>
- **Level 1**: Players have 3 lives and the score gets incremented by 1 every time a point is been scored. The bonus for having           lives after game over is 1 * number of lives. <br>
- **Level 2**: Players have 2 lives and the score gets incremented by 2 every time a point is been scored. The bonus for having           lives after game over is 3 * number of lives. <br>
- **Level 3**: Players have 1 live and the score gets incremented by 5 every time a point is been scored. The bonus for having lives       after game over is 4 * number of lives. <br>

The menu is very simple: You have play tab in order to start the game. The highscore tab where you can see the highest score ever done (the highest score is saved in EEPROM). In more menu you can select settings and info tab. In the settings menu you can do some minor changes such as: change the level you want to play, turn the LCD light on or off and change the contrast of the LCD. In the info tab you can see information about the developer of the game, the actual game name, developer's github and the @UnibucRobotics tag.
## How to play: <br>
In order to start the game you must press the button of the player's 1 joystick when the play tab is been selected. Next the game will start. Move the joystick on Y-axis in order to move the paddle in the front of the ball. In the LCD there will be displayed score,lives for each and every player, time since the round started and level. After one of the players is out of lives or 60 seconds have passed on the LCD display you will see who won and the final scores. Have fun!
## Hardware: <br>
a. 8x8 LED matrix <br>
b. LCD <br>
c. 2xJoystick <br>
d. MAX7219 Driver <br>
e. Arduino <br>
f. Cables <br>
g. 2xBreadboard <br>

<a href="https://youtu.be/xmJq6CRY1m0">Video presenting the game is here</a>

<a href="https://drive.google.com/open?id=1FL6eEFwPrHL9MFPk1oTyJvakSpnL2dt5">An image with the  final assembly</a>

