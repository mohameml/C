"""
Définition d'une classe représentant une question d'un quiz.
"""

import textwrap, sys, string
from misc import GREEN, RED, YELLOW, jolify, empty_screen, print_color, getchar

class QTYPES:
    # 1 seul choix possible parmi N
    SINGLE =  1
    # M choix possibles parmi N
    MULTIPLE = 2
    # définir un nombre d'étoiles par compétence ([**   ] par ex)
    SKILL = 3


class Question:

    def __init__(self, qtype, title, desc, answers, picked_items=None, footer=None):
        self.title = title
        self.desc = jolify(desc.replace("\\\\", "\\"))
        self.answers = answers
        self.best_score = 0
        self.sol = [1 if "ok" in answer else 0 for answer in answers]
        self.picked_items = picked_items if picked_items is not None else [0 for _ in answers]
        self.qtype = qtype
        self.custom_footer = footer

    def is_correct(self, id):
        return self.sol[id] == self.picked_items[id]

    def print_header(self, cur, tot):
        msg = ""
        if tot:
            msg = "[Score actuel: {}/{} bonnes réponses!]".format(cur, tot)
        style = "=" * ((80 - len(msg)) // 2)
        print_color(GREEN, style + msg + style)

    def print_footer(self):
        msg = ""
        if self.qtype == QTYPES.MULTIPLE:
            msg = "[Record personnel pour cette question: {}/{}]]".format(
                self.best_score,
                len(self.answers)
            )
        style = "=" * ((80 - len(msg)) // 2)
        print_color(GREEN, "\n" + style + msg + style + "\n")

    def print_help(self):
        msg = None
        if self.qtype == QTYPES.SKILL:
            msg = "mettre à jour le niveau de maitrise d'une compétence"
        else:
            msg = "(dé)sélectionner une réponse"
        tips = "%%%% <1-{}> pour {}\n".format(format(len(self.answers), 'x'), msg)
        tips += "%%%% <RET> pour valider et passer à la suite\n"
        if "update" not in sys.argv[0]:
            tips += "%%%% <s> pour sauter cette question\n"
            tips += "%%%% <q> pour quitter\n"
        print(tips)

    def print_ui(self, cur_score, tot_score, show_feedback=False, warning=None):
        wrapper = textwrap.TextWrapper(width=70,
                                       drop_whitespace=False,
                                       replace_whitespace=False)

        # On efface tout!
        empty_screen()

        # On affiche d'abord la bannière avec le score.
        self.print_header(cur_score, tot_score)

        # Ensuite le titre de la question
        print("\n*** {} ***\n".format(self.title))

        # Puis l'énoncé de la question
        print("{}".format(self.desc))

        # Et ensuite la liste des réponses possibles
        for id, answer in enumerate(self.answers):
            answer_str = answer['ko'] if 'ko' in answer else answer['ok']
            # Indentation bon marché
            answer_str = answer_str.replace("\n", "\n       ")
            answer_str_lines = wrapper.wrap(answer_str)
            # On affiche l'item ligne par ligne... D'abord la
            # première, formatée différemment :
            arrow = "  "
            if self.picked_items[id] == 1 and self.qtype != QTYPES.SKILL:
                arrow = "->"
            stars = ""
            if self.qtype == QTYPES.SKILL:
                lvl = "*" * self.picked_items[id]
                emptys = " " * (5 - len(lvl))
                stars = "[{}{}]".format(lvl, emptys)
            print("{}  {}. {} {}".format(arrow,
                                         format(id + 1, 'x'),
                                         stars,
                                         answer_str_lines[0]))
            # Puis toutes les autres.
            for linenum in range(1, len(answer_str_lines)):
                print("       {}".format(answer_str_lines[linenum]))
                # Est-ce qu'on affiche la solution?
            if show_feedback:
                feedback = answer['feedback']
                feedback_lines = wrapper.wrap(feedback)
                #print_color(YELLOW, repr(feedback_lines))
                color = GREEN if self.is_correct(id) else RED
                print_color(color, "    [{}] {}".format(
                    "faux" if "ko" in answer else "vrai",
                    feedback_lines[0]))
                for linenum in range(1, len(feedback_lines)):
                    print_color(color, "           {}".format(feedback_lines[linenum]))
                print("")

        # Toutes les réponses sont à l'écran, on affiche le footer.
        if self.custom_footer:
            print(self.custom_footer)
        self.print_footer()

        # Si on n'est pas en mode correction, on affiche l'aide.
        if not show_feedback:
            self.print_help()

        # Si la dernière saisie de l'utilisateur était merdique, on
        # lui dit.
        if warning:
            print_color(YELLOW, "Warning: {}\n".format(warning))

    def play(self, cur=0, tot=0, feedback=True):
        usr_input = ""
        msg = ""

        self.print_ui(cur, tot)

        while True:
            usr_input = getchar()
            if usr_input in string.hexdigits:
                digit = int(usr_input, 16) - 1
                if digit not in range(0, len(self.answers)):
                    msg = "l'entier saisi n'appartient pas à [1;{}] ({})".format(
                        len(self.answers),
                        digit + 1)
                else:
                    if self.qtype == QTYPES.SKILL:
                        self.picked_items[digit] += 1
                        if self.picked_items[digit] == 6:
                            self.picked_items[digit] = 0
                    else:
                        self.picked_items[digit] = 1 - self.picked_items[digit]
                    if self.qtype == QTYPES.SINGLE:
                        for id in range(len(self.picked_items)):
                            if id != digit:
                                self.picked_items[id] = 0
            elif usr_input == 'q' or usr_input == 's':
                return usr_input
            elif usr_input == '\r':
                self.print_ui(cur, tot, show_feedback=feedback)
                if feedback:
                    ok = sum([1 if s == self.picked_items[id] else 0 for id, s in enumerate(self.sol)])
                    msg = "==> score : {}/{}".format(ok, len(self.answers))
                    if ok > self.best_score:
                        self.best_score = ok
                        msg += "   ** nouveau record! **"
                    else:
                        msg += "   ** record personnel: {}/{} **".format(self.best_score, len(self.answers))
                    print(msg)
                    print("")
                    input(">> Appuyez sur Entrée pour passer à la question suivante << ")
                break
            else:
                msg = "saisie invalide ({}). Merci de recommencer.".format(usr_input)
            self.print_ui(cur, tot, warning=msg)
