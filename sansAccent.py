# coding=utf8
# -*- coding: utf8 -*-

import clearCorpus
from clearCorpus import calculPiwi

#===============================================================================
# classe Fichier
#===============================================================================
class Fichier : 
    def __init__(self,nameFichier):
        self.nameFichier = nameFichier
        self.nbMots = 0
        self.nbCaracteres = 0
        self.proba = {} 
        self.calculPiwi()

    def __repr__(self):
        return "{nom fichier : "+self.nameFichier+" nombre de mots ： "+str(self.nbMots)+" nombre de caracteres : "+str(self.nbCaracteres)+" }"

    def calculPiwi (self):
        file = open(self.nameFichier,"r")
        nbCar =0
        nbWord = 0
        tabPiWi= {}
        for line in file:
            for word in line.split(" "):
                nbWord+=1
                print word
                for car in word:
                    nbCar+=1
                    print car
                    if car in tabPiWi.keys():
                        tabPiWi[car]+=1
                    else:
                        tabPiWi[car]=1
        self.nbMots = nbWord
        self.nbCaracteres = nbCar
        self.proba = tabPiWi


fichiers = [Fichier('corpus/dutch.txt'),Fichier('corpus/english.txt'),Fichier('corpus/french.txt'),Fichier('corpus/italian.txt')]

print fichiers


