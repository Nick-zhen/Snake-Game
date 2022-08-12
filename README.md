# Snake-Game
## Set up enviroment  
 1. Install SFML(https://www.sfml-dev.org/tutorials/2.5/start-linux.php)  
  Because I just wanna use VS code on mac. I would recommend to look at Linux instructions for installing SFML using a tool in Mac called **brew**. 
  ```shell
  brew search sfml
  ```
  we should find sfml does exist

  ```shell
  brew install sfml
  ```
  Lets see the pwd of this library
  ```shell
  brew info sfml
  ```
  The pwd for my computer is /usr/local/Cellar/sfml/2.5.1_1 (625 files, 9.7MB) *. 
  Why is this important? because we will link this pwd and lib when we compile the c++ project. For example 
  ```shell
  g++ sfml.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include -o prog -L/usr/local/Cellar/sfml/2.5.1_1/lib/ -lsfml-graphics -lsfml-window -lsfml-system
  ```
2. Set up enviroment for VS code
  Install easy c++ project in vs code extension. 
  In the folder, click F1 => create a easy c++ project. Then you will some new files like Makefile  
 
## Lets' coding!
