CC=gcc
RESULT=ergo
INSTALL=/usr/bin
CREATE_OBJ=@mkdir ./obj

all: ./obj/ $(RESULT)

./obj/:
	mkdir ./obj



obj/menu.o: modules/menu.c
	$(CC) -c modules/menu.c -o obj/menu.o

obj/help.o: modules/help.c 
	$(CC) -c modules/help.c -o obj/help.o

obj/open.o: modules/open.c
	$(CC) -c modules/open.c -o obj/open.o

obj/new_list.o: modules/new_list.c
	$(CC) -c modules/new_list.c -o obj/new_list.o

obj/rename_list.o: modules/rename_list.c
	$(CC) -c modules/rename_list.c -o obj/rename_list.o

obj/new_task.o: modules/new_task.c
	$(CC) -c modules/new_task.c -o obj/new_task.o

obj/rename_task.o: modules/rename_task.c
	$(CC) -c modules/rename_task.c -o obj/rename_task.o



obj/input.o: utils/input.c
	$(CC) -c utils/input.c -o obj/input.o

obj/lists.o: utils/lists.c
	$(CC) -c utils/lists.c -o obj/lists.o

obj/serial.o: utils/serial.c
	$(CC) -c utils/serial.c -o obj/serial.o

obj/setup.o: utils/setup.c
	$(CC) -c utils/setup.c -o obj/setup.o

obj/task.o: utils/task.c
	$(CC) -c utils/task.c -o obj/task.o

obj/tasks.o: utils/tasks.c
	$(CC) -c utils/tasks.c -o obj/tasks.o



obj/yyjson.o: yyjson/yyjson.c
	$(CC) -c yyjson/yyjson.c -o obj/yyjson.o



obj/main.o: main.c	
	$(CC) -c main.c -o obj/main.o

$(RESULT): obj/menu.o obj/help.o obj/open.o obj/new_list.o obj/rename_list.o obj/new_task.o obj/rename_task.o obj/input.o obj/lists.o obj/serial.o obj/setup.o obj/task.o obj/tasks.o obj/yyjson.o obj/main.o
	gcc obj/*.o -o $(RESULT)
	mkdir -p "$(HOME)/.config/cerber/tasks"

install: ./obj/ $(RESULT)
	cp ergo "$(INSTALL)/$(RESULT)"

uninstall:
	rm -rf "$(INSTALL)/$(RESULT)"

help:
	@echo
	@echo "  Help:"
	@echo
	@echo "  make           - compile the source code"
	@echo "  make install   - copy compiled binary to the path"
	@echo "  make uninstall - remove compiled binary from the path"
	@echo "  make clean     - clean compiled binary and object files"
	@echo

clean:
	rm -rf obj $(RESULT)
