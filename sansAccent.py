# coding=utf8
# -*- coding: utf8 -*-

import clearCorpus
import math
import string
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
        self.PIK = 0

    def __repr__(self):
        return "{nom fichier : "+self.nameFichier+" nombre de mots ： "+str(self.nbMots)+" nombre de caracteres : "+str(self.nbCaracteres)+" PIK:" + str(self.PIK) + " proba "+str(self.proba)+"}"

    def calculPiwi (self):
        file = open(self.nameFichier,"r")
        nbCar =0
        nbWord = 0
        tabPiWi= {}
        for i in list(string.ascii_lowercase):
            tabPiWi[i]=1
        for line in file:
            for word in line.split(" "):
                nbWord+=1
                for car in word:
                    if car in tabPiWi.keys():
                        nbCar+=1
                        tabPiWi[car]+=1
        #26 car on a mis un de base dans le tab
        nbCar += 26
        sommeProba = 0
        for k in tabPiWi:
            tabPiWi[k] = float(tabPiWi[k])/float(nbCar)
            sommeProba += tabPiWi[k]
        print sommeProba
        self.nbMots = nbWord
        self.nbCaracteres = nbCar
        self.proba = tabPiWi


#P la langue en entrée, et Qlist les langues de comparaison
def calculKoolpakCalber(P,Qlist):
    resKL = []
    for langueQ in Qlist:
        res = 0
        for car in P.proba:
            res += math.log(P.proba[car] / langueQ.proba[car]) * P.proba[car]
        resKL.append([res,langueQ.nameFichier])
    return resKL

fichiers = [Fichier('corpus/dutch.txt'),Fichier('corpus/english.txt'),Fichier('corpus/french.txt'),Fichier('corpus/italian.txt')]
nbMotCorpus = 0
#Calcul du nombre de mots total dans le corpus
for f in fichiers:
    nbMotCorpus += f.nbMots    
    
#Calcul des PIK de chaque fichier      
for f in fichiers:
    f.PIK = float(f.nbMots) / float(nbMotCorpus)
    
# print fichiers
# print calculKoolpakCalber(fichiers[2], [fichiers[0],fichiers[1], fichiers[3]])
print calculKoolpakCalber(fichiers[0], [fichiers[2],fichiers[1], fichiers[3]])

    



