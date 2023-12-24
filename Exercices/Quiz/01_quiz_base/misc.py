import textwrap
import os

BANNER = """
   (                        _             _             _
  `-`-.       ___ _ __  ___(_) __ _ _   _(_) __ _ _   _(_)____
  '( @ >     / _ \ '_ \/ __| |/ _` | | | | |/ _` | | | | |_  /
   _) (     |  __/ | | \__ \ | (_| | |_| | | (_| | |_| | |/ /
  /    )     \___|_| |_|___/_|\__, |\__,_|_|\__, |\__,_|_/___|
 /_,'  /                         |_|           |_|
   \  /
===m""m============================================================
"""

RED = '\033[31m'
GREEN = '\033[32m'
YELLOW = '\033[43m'
ENDC = '\033[0m'


def print_color(color, string):
    """ Affiche la chaine string en couleur. """
    colors = [RED, GREEN, YELLOW]
    if color not in colors:
        color = ENDC
    print(color + string + ENDC)


def jolify(string):
    """
    Formate la chaine passée en paramètre pour qu'elle occupe 80
    colonnes de largeur max. Evite de reformater le code, si la chaine
    en contient.
    """
    wrapper = textwrap.TextWrapper(width=80,
                                   drop_whitespace=False,
                                   replace_whitespace=False)

    current_str = ""
    final_str = ""
    lines = string.split("\n");
    for line in lines:
        if "<pre>" in line:
            if current_str != "":
                final_str += wrapper.fill(current_str) + "\n"
            current_str = ""
        elif "</pre>" in line:
            final_str += current_str + "\n"
            current_str = ""
        else:
            current_str += line + "\n"
    final_str += wrapper.fill(current_str)

    return final_str


def empty_screen():
    """ clear, quoi. """
    os.system("clear")


def getchar():
    """
    Récupère _un_ caractère depuis stdin, et retourne tout de suite
    """
    if os.name == 'nt':
        import msvcrt
        c = msvcrt.getch()
    else:
        import tty, termios, sys
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            c = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return c

def try_pull(cmd):
    print("On regarde d'abord si votre dépôt git est à jour...")
    ret = os.system("git pull")
    if ret:
        print("[abort] Votre dépôt git local n'est pas à jour!")
        print("        Merci de lancer `git pull` avant le lancer `{}`.".format(cmd))
        exit(1)

def push_files(files, msg):
    """
    Pousse une nouvelle version du fichier f dans le
    dépôt.

    Essaye de pousser les fichiers dans le dépôt git courant.
    En gros, ça fait :
    - git add file1 file2 ... fileN
    - git commit -m msg
    - git push

    Le git pull doit être fait avant avec try_pull pour éviter les
    conflits (de canard).
    """
    ret = 0
    for f in files:
        print("git add {}".format(f))
        ret += os.system("git add {}".format(f))
    if ret:
        print("[abort] git add {} a rencontré une erreur.".format(" ".join(files)))
        exit(2)

    ret = os.system('git commit -m "{}"'.format(msg))
    if ret:
        exit(3)

    ret = os.system("git push")
    if ret:
        print("[abort] git push a rencontré une erreur.")
        exit(4)

    print("")
