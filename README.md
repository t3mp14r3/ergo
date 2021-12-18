# ergo
Simple task lists manager

## Description
This is a small, terminal, written in C task lists manager to help you organize your tasks, ideas etc.

Please note, that the project is in the early stage of development, so there are can and probably will be bugs and errors, on this note, please submit an issue, if you find something working in the code, or while using the program, also, if you have some feature idea, suggest it as well, thank you in advance.


## Installation
Clone the repository
```
git clone github.com/t3mp14r3/ergo.git
```

Compile the source code and install the binary (might require sudo)
```
make install
```

Alternatively you can just compile the code and then put the binary in your own path. You can also change the installation directory by modifying the INSTALL variable in the Makefile
```
make
```

To clean the source directory you can run
```
make clean
```

To uninstall ergo, you can use the uninstall rule (might require sudo)
```
make uninstall
```

## Controls
Lists menu
+ `j`     - go down
+ `k`     - go up
+ `enter` - select list
+ `n`     - create new list
+ `d`     - delete list
+ `r`     - rename list
+ `q`     - quit

Tasks menu
+ `j`     - go down
+ `k`     - go up
+ `space` - check/uncheck task
+ `enter` - check/uncheck task
+ `n`     - create new task
+ `d`     - delete task
+ `r`     - rename task
+ `q`     - quit to menu

You can also use the help command, by pressing `h` in both menus.


## Workflow details
To store the lists of tasks ergo uses `.json` files. They are being stored by default in `$HOME/.config/cerber/tasks/`. To work with json data I use the [yyjson](https://github.com/ibireme/yyjson) library, and for terminal graphics i use my own [visual](https://github.com/t3mp14r3/visual) tiny single header lib, so if something doesn't print correctly, plese, submit an issue.


## ToDo
- [ ] Make the configuration more flexible
- [ ] Add description to the tasks
- [ ] Add sublist inside the task lists


