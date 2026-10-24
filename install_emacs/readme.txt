Ce dossier contient:
comment installer le même environnement et le même emacs sur WSL2 Debian 13


Dans votre terminal Debian
Premièrement si ce n'est pas déjà fait:

sudo apt update
sudo apt upgrade


Deuxiemement installer emacs graphique et scheme 12.1 (version actuellement utilisée en tps en 2026)

sudo apt install emacs-gtk mit-scheme

vous pouvez vérifier si ils ont bien été installé avec
emacs --version
scheme --version

Si le dossier .emacs.d n'est pas dans votre répertoire lancez emacs une première fois


Le fichier .emacs que l'on a installé en tp requière le module quack.
Ce module est bien installé sur les ordis de l'isima mais pas pour nous.

J'ai mis dans le même dossier que ce readme.txt le dossier "lisp" contenant "quack.el"
mettre via mv le dossier "lisp" dans ".emacs.d"

Dans le dossier actuel se trouve également une version modifiée du fichier ".emacs" du tp
La modification indique juste au fichier que les modules qu'il veut load comme 'quack' sont dans "~/.emacs.d/lisp"


Il y a également un fichier qui fait tout pour vous (installation d'emacs scheme et environnement)







