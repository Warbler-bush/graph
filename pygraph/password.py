import numpy as np

def build(n, forb):
    grand = pow(2,n)
    matr = np.zeros((grand,n))
    is0 = True
    for i in range(0,n):
        num = pow(2,n-(i+1))
        numdec = num
        for j in range(0,grand):
            if is0:
                matr[j][i] = 0
            else:
                matr[j][i] = 1
            numdec -= 1
            if numdec == 0:
                numdec = num
                is0 = not is0

    tro = 0
    for i in range(0,grand):
        stringa = str(matr[i]).replace("[","").replace("]","").replace(".","").replace(" ","")
        if forb in stringa:
            tro += 1

    return grand - tro

filei = open("inputp.txt", "r")
fileo = open("output.txt", "w")

ncase = int(filei.readline().splitlines()[0])

for i in range(0, ncase):
    line = list(map(int, filei.readline().splitlines()[0].split(" ")))

    passlen = line[0]
    forblen = line[1]

    forb = filei.readline().splitlines()[0]

    res = build(passlen, forb)
    fileo.write("Case #" + str(i + 1) + ": " + str(res) + "\n")

