Overcooked Game Recreation
Welcome to the Overcooked Game Recreation! This project is a console-based simulation of the popular cooperative cooking game, Overcooked. It is built using the C programming language and the ncurses library, which provides a text-based graphical interface.

Table of Contents
Overview
Features
Installation
Usage
Gameplay
Credits
Overview
In this project, we recreate the Overcooked experience where players manage a kitchen, prepare orders, and try to keep up with a steady flow of incoming requests. The game is simulated in a terminal window using ncurses to handle the text-based user interface.

Features
Order Management: Orders appear randomly and need to be managed by preparing dishes.
Preparation Stations: Manage preparation and cooking stations with limited capacity.
Multithreading: Use of pthreads to handle multiple tasks concurrently, such as generating orders and processing commands.
Real-Time Updates: Dynamic updates of game state displayed in the terminal.
Installation
Clone the Repository

sh
Copy code
git clone https://github.com/yourusername/projeto_hovercooked.git
Navigate to the Project Directory

sh
Copy code
cd projeto_hovercooked
Compile the Program

Use the following command to compile the program:

sh
Copy code
gcc -o jogo main.c -lncurses -lpthread
Run the Game

Execute the game with:

sh
Copy code
./jogo
Usage
Upon running the game, you will be presented with a terminal-based interface that allows you to interact with the game.

Controls
1: Select an order to prepare.
2: Move prepared items to the ready station.
F4 or Q: Quit the game.
Gameplay
Objective
The objective of the game is to manage incoming orders, prepare dishes, and complete them within the allotted time. The game lasts for 60 seconds.

Game Mechanics
Incoming Orders: Orders appear randomly on the screen. You need to select and prepare them using available stations.
Preparation Stations: You have a limited number of preparation stations. Use these to prepare the dishes.
Completion: Move the prepared dishes to the ready station. If you run out of time or fail to manage orders, the game ends.
Win/Loss Conditions
Win: All orders are processed before the time runs out.
Loss: Time runs out and not all orders are processed.
Credits
Author: Your Name
Libraries: Uses ncurses for terminal handling and pthread for multithreading.
Feel free to modify any sections as needed! If there are specific features or installation details you'd like to add, just let me know.
