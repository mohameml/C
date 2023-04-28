#! /usr/bin/env python3

"""
Définition de la classe Quiz
"""

import sys, os, random, yaml
from misc import BANNER, RED, GREEN, empty_screen, jolify, push_files, try_pull
from question import Question, QTYPES

class Quiz:

    def __init__(self,
                 yaml_filename,
                 progress_filename,
                 use_git=True,
                 run_all=False,
                 run_random=False):
        self.raw_data = None
        self.title = None
        self.questions = None
        self.cur_score = None
        self.tot_score = None
        self.progress = None
        self.progress_filename = progress_filename
        self.use_git = use_git
        self.run_all = run_all
        self.run_random = run_random

        with open(yaml_filename, "r") as data_file:
            self.raw_data = yaml.load(data_file)

        with open(progress_filename, "r") as progress_file:
            self.progress = yaml.load(progress_file)

        self.title = self.raw_data['title']
        self.questions = []
        quiz_progress = self.progress[self.raw_data['lvl']]['quiz']
        for q in self.raw_data['questions']:
            question = Question(QTYPES.MULTIPLE, q['title'], q['description'], q['answers'])
            question.best_score = quiz_progress['questions'][question.title]['score']
            self.questions.append(question)

        if self.run_random:
            random.shuffle(self.questions)

        self.cur_score = quiz_progress['score']
        tot_score = quiz_progress['tot_score']
        self.tot_score = tot_score if tot_score > 0 else sum([len(q['answers']) for q in self.raw_data['questions']])

    def print_intro(self):
        """ Affiche l'écran de départ. """
        empty_screen()
        print("{}\n".format(BANNER))
        print("\t\t** {} **\n".format(self.title))
        print("\t\t** Progression générale: {}/{} **\n".format(
            self.cur_score,
            self.tot_score))
        input("Appuyez sur Entrée pour démarrer le quiquiz : ")

    def play(self):
        for q in self.questions:
            if not self.run_all and q.best_score == len(q.answers):
                continue
            base_count = self.cur_score - q.best_score
            ret = q.play(self.cur_score, self.tot_score)
            self.cur_score = base_count + q.best_score
            if ret == 'q':
                break

        # on arrive là soit si l'utilisateur a tapé 'q', soit si on a
        # traité toutes les questions du quiz.
        self.save_progress()

    def save_progress(self):
        quiz_progress = self.progress[self.raw_data['lvl']]['quiz']
        quiz_progress['score'] = self.cur_score
        quiz_progress['tot_score'] = self.tot_score
        for q in self.questions:
            question_progress = quiz_progress['questions'][q.title]
            question_progress['score'] = q.best_score
            for id, _ in enumerate(q.answers):
                question_progress['answers'][id] = "correct" if q.is_correct(id) else "wrong"
        with open(self.progress_filename, "w") as progress_file:
            yaml.dump(self.progress,
                      progress_file,
                      default_flow_style=False,
                      allow_unicode=True,
                      encoding="utf-8")
        if self.use_git:
            push_files([ self.progress_filename ],
                       "[progress] Quiz {}".format(self.title))


def main():
    q = Quiz("../base/quiz/data.yaml", "progress.yaml")
    q.print_intro()
    q.play()


if __name__ == "__main__":
    main()
