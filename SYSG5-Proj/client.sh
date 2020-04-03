#!/bin/bash



echo "
 __          __  _                           _____ _ _            _  
 \\ \\        / / | |                         / ____| (_)          | |  
  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___| |    | |_  ___ _ __ | |_
   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ \` _ \\ / _ \\ |    | | |/ _ \\ '_ \\| __|
    \\  /\\  /  __/ | (_| (_) | | | | | |  __/ |____| | |  __/ | | | |_
     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|\\_____|_|_|\\___|_| |_|\\__|



"


echo "Please enter the number of commands you wanna save ?"

read numberOfCommands

HISTFILE=~/.bash_history  # Set the history file.
set -o history            # Enable the history.
history -a
history $numberOfCommands > history.txt          # Save the history.

gcc -w -Wall -o myclientFork clientFork.c
./myclientFork  192.168.121.128

exit

