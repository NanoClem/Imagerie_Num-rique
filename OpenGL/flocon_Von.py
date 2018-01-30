def koch(l,n):
                    # # Fractacle de Koch
    if n<=0:
        forward(l)
    else:
        koch(l/3,n-1)
        left(60)
        koch(l/3,n-1)
        right(120)
        koch(l/3,n-1)
        left(60)
        koch(l/3,n-1)

def flocon(l,n):
                    # # Flocon de Koch
    koch(l,n)
    right(120)
    koch(l,n)
    right(120)
    koch(l,n)

# programme principal
from turtle import *
etape=int(input("Entrez l\'ordre de l\'etape du flocon de Von Koch "))
taille1=float(input("Entrez la taille du cote du triangle initial "))
flocon(taille1,etape)
