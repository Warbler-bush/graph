filei = open("input.txt", "r")
fileo = open("output.txt", "w")

ncase = int(filei.readline().splitlines()[0])
i = 0
for i in range(0,ncase):
    

    fileo.writelines("Case #" + str(i + 1) + ": " + str(i-1) + "\n")