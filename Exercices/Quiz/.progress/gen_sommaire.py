#! /usr/bin/env python3

import os, sys, textwrap, yaml

from prephtml import HTML


def gen(dst):
    """
    Crée un sommaire HTML pour les exercices du parcours.
    Cette page est générée en parcourant le fichier de progression progress.yaml.
    Les compétences sont représentées sous la forme d'un tableau dont chaque ligne contient:
    - la catégorie associée ;
    - la description de la compétence ;
    - une liste d'exercices sous la forme de liens hypertexte vers leurs pages gitlab.
    """

    def get_category(gskill, skill):
        """Retourne la catégorie de skill à partir du dictionnaire gskill"""
        for cat in gskill:
            for s in gskill[cat]:
                if s == skill:
                    return cat
        print("Badaboom! skill {} absente!".format(skill))

    wrapper = textwrap.TextWrapper(
        width=30, drop_whitespace=False, replace_whitespace=False
    )

    parcours = os.path.basename(dst)
    progress = None
    current_folder = os.path.dirname(sys.argv[0])
    with open(os.path.join(current_folder, "progress.yaml"), "r") as yaml_file:
        progress = yaml.load(yaml_file, Loader=yaml.FullLoader)

    exos = progress[parcours]["exos"]
    carte = progress["carte"]

    skills = dict()
    max_length = 0
    for e in exos.keys():
        length = len(e)
        if length > max_length:
            max_length = length
        for s in exos[e]["skills"]:
            cat = get_category(carte, s)
            if cat not in skills:
                skills[cat] = dict()
            if s not in skills[cat]:
                skills[cat][s] = dict()
            skills[cat][s][e] = exos[e]

    sommaire = HTML(
        "html",
        '<meta http-equiv="content-type" content="text/html; charset=utf-8" />\n<link rel="stylesheet" href="../.progress/sommaire.css" type="text/css" />',
        escape=False,
    )
    sommaire.title("Sommaire des exercices")

    # on trie les compétences par ordre d'apparition dans le fichier YAML
    # c'est comme ça qu'on garantit un certain ordre dans le sommaire des exos
    # skills = sorted(skills.items(), key=lambda comp: comp[1][0])

    tab = sommaire.table(border="1", id="sommaire")
    html_table = tab.tr
    html_table.th("Catégorie")
    html_table.th("Maitrise")
    html_table.th("Compétence")
    html_table.th("Liste d'exercices")

    link_color = ["brightgreen", "brightgreen", "yellow", "yellow", "red"]
    mastery = [":zero:", ":one:", ":two:", ":three:", ":four:", ":five:"]

    for cat in skills:
        html_table = tab.tr
        nb_skills = len(skills[cat]) + 1
        rspan = str(nb_skills)
        html_table.td(cat, rowspan=rspan, escape=False)

        for skill in skills[cat]:
            html_table = tab.tr
            level = carte[get_category(carte, skill)][skill]
            stars = ""
            for _ in range(level):
                stars += "<img src=../.progress/star.png />"
            html_table.raw_text('<td width="50">{}</td>'.format(stars))
            html_table.td(skill, escape=False)
            liens = {"brightgreen": "", "yellow": "", "red": ""}
            for name, exo in skills[cat][skill].items():
                lvl = link_color[exo["lvl"] - 1]
                liens[
                    lvl
                ] += """<a href={}><img src=\"https://img.shields.io/static/v1.svg?label={}&message={}&color={}\" /></a> """.format(
                    os.path.join("exercices", name), name, exo["maitrise"], lvl
                )
            html_table.td(
                liens["brightgreen"] + liens["yellow"] + liens["red"], escape=False
            )

    with open(os.path.join(dst, "sommaire.md"), "w") as f_sommaire:
        f_sommaire.write(str(sommaire))


def main():
    """Point d'entrée du programme."""
    dst = sys.argv[1]
    gen(dst)


if __name__ == "__main__":
    main()
