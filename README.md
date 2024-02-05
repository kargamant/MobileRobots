# MobileRobots
Cool auto-game project about robots discovering a planet🚀🤖

![for_github](https://github.com/kargamant/MobileRobots/assets/54020145/4be8d0ba-1c69-400b-96e5-8826d22df6d0)  


# What is game about?
Group of robots is set on square field with 3 types of cells: ground, obstacles and points of interest.  
The last ones are what robots are hunting for. To win you need to collect all of them.

### Cells
![image](https://github.com/kargamant/MobileRobots/assets/54020145/994e275f-f2b6-4dc8-81d3-1d5adf5945ee)  

### Robots
There are several classes of robots that were developed.  _CommandCentre, RobotCommander, RobotDestroyer, Kamikaze and many more._  
In sand box mode they can be purchased at robot store for ai-coins(to be said later).

![for_github2](https://github.com/kargamant/MobileRobots/assets/54020145/6fe1b769-8a39-488e-b40b-6e3109eeaa22)  

### Modules
Sensors, energy generators, cpus and even guns can be set on robots.    
Also can be purchased in module store during game.  

![for_github3](https://github.com/kargamant/MobileRobots/assets/54020145/b81b5a0e-529f-40ae-9493-9ac49f8a83c0)  

# How is it played?
There are 2 modes avaliable: sand-box and ai.  
**Sand-box mode** is a basic single player mode. You control robots.
**Ai mode** is an auto play mode. Ai plays for you.

# Sand-box mode
A normal single player mode. It was mostly used for testing purposes, so not always stable.  
Some robots are randomly spawned on field, but you can purchase more for coins that are given at start of the game.  
Also coins can be spent on modules in module store. Spend them wisely, cause some robots might remain uneffective😢.  
To play it you have to build the project and run it with -sand-box flag.  
`$ ./main -sand-box`

### Controls are the following
left mouse click - choose a cell, robot to see information about it.  
right mouse click - choose a module to see information about it.  
<kbd>&#8592;</kbd> <kbd>&#8594;</kbd> <kbd>&#8593;</kbd> <kbd>&#8595;</kbd> - to move a robot that you have chosen.
<kbd>p</kbd> - to open robot store.  
<kbd>m</kbd> - to open module store.  
<kbd>s</kbd> - to subdue a robot(if a rulling robot is being handled).  
<kbd>r</kbd> - to release a robot(if a rulling robot is being handled).  
<kbd>d</kbd> - to destroy a robot(if a destroying robot is being handled).  
<kbd>c</kbd> - to connect module to power(if an energy generator is being handled).  
<kbd>o</kbd> - to turn on module.  
<kbd>g</kbd> - to get report from subordinate(if a rulling robot is being handled).  
<kbd>e</kbd> - to dissconect module(if an energy generator is being handled).  

# AI mode
Ai plays for you.  
Developed algorithm was based on **A-star path-finding** algorithm and developed **priority system** for every robot class.  
To play game with this mode run:  
`$ ./main -ai`  
This mode is availiable with following flags:  
`-mthread` - game will be played with multi thread ai algorithm instead of regular one.  
`-wmode` - turns on graphics(unavailiable with multi thread mode, because multi thread algorithm was developed for big fields that can't normally fit into window).  

### One more thing...  
### Gameplay ofcourse  
![mobile_robots_gponline-video-cutter com-ezgif com-video-to-gif-converter](https://github.com/kargamant/MobileRobots/assets/54020145/3e57fc91-fa54-4a52-9894-ffae5cea5c98)

