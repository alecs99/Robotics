# **Pong Game**
## **Description**<br>
Pong is a 2 player game similar to table tennis which features two paddles and a ball. You also have a number of lives (depends of the level you play). The game ends when one of a player loses all of his lives. The winner is the player which has the highest score. Note: The player who has lives and the end of the game will receive a bonus (depending on the level you play). You get a point if the ball reached opponent's side without him touching it with his paddle. When a point is being scored the LED will light up. <br>
There are multiple levels you can try: <br>
- **Level 1**: Players have 3 lives and the score gets incremented by 1 every time a point is been scored. The bonus for having           lives after game over is 1 * number of lives. <br>
- **Level 2**: Players have 2 lives and the score gets incremented by 2 every time a point is been scored. The bonus for having           lives after game over is 3 * number of lives. <br>
- **Level 3**: Players have 1 live and the score gets incremented by 5 every time a point is been scored. The bonus for having lives       after game over is 4 * number of lives. <br>

The menu is very simple: You have play tab in order to start the game. The highscore tab where you can see the highest score ever done (the highest score is saved in EEPROM). In the settings you can select the level of the game. Also you can turn display on or off and change contrast. In the info tab you can see information about creator of the game, github link and name of the game.
## How to play: <br>
In order to start the game you must press the button of the player's 1 joystick when the play tab is been selected. Next the game will start. Move the joystick on Y-axis in order to move the paddle in the front of the ball.
## Hardware: <br>
a. 8x8 LED matrix <br>
b. LCD <br>
c. 2xJoystick <br>
d. MAX7219 Driver <br>
e. LED <br>
f. Arduino <br>
g. Cables <br>
