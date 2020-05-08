#!/bin/bash



echo "
 __          __  _                           _____ _ _            _  
 \\ \\        / / | |                         / ____| (_)          | |  
  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___| |    | |_  ___ _ __ | |_
   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ \` _ \\ / _ \\ |    | | |/ _ \\ '_ \\| __|
    \\  /\\  /  __/ | (_| (_) | | | | | |  __/ |____| | |  __/ | | | |_
     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|\\_____|_|_|\\___|_| |_|\\__|



"

HISTFILE=~/.bash_history  # Set the history file.
	set -o history            # Enable the history.
	history -a

echo "Avez-vous déjà mis à jour le fichier ~/.bashrc et redémarrer la session ?(O/N)"
read reponse

if [ $reponse == N ] || [ $reponse == n ]
then
	echo 'shopt -s histappend
export PROMPT_COMMAND="history -a; history -c; history -r; $PROMPT_COMMAND"' >> ~/.bashrc
	echo "Vous devez redémarrer votre session pour rendre les changements effectifs !"

elif [ $reponse = O ] || [ $reponse = o ]
then
        echo "Please enter the number of commands you wanna save ?"

	read numberOfCommands

	
	history $numberOfCommands > history.txt          # Save the history.

	gcc -w -o myclientFork clientFork.c
	./myclientFork  $1
	exit
fi



echo "Voulez vous tout de même démarrer sans les changements ?(O/N)"

read suite

if [ $suite == O ] || [ $suite == o ]
then 
	echo "Please enter the number of commands you wanna save ?"

	read numberOfCommands

	
	history $numberOfCommands > history.txt          # Save the history.

	gcc -w -o myclientFork clientFork.c
	./myclientFork  $1

fi
exit

