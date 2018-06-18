disciplines = ('MC833', 'MC102', 'MC536', 'MC750', 'MC358', 'MC458', 'MC558', 'MC658', 'MC346', 'MC886')
professors = ('edmundo', 'zanoni', 'bruno', 'baranauskas', 'rezende', 'lehilton', 'christiane', 'flavio', 'wainer', 'rocha')

for i in range(0, 6):
    #lista todos os codigos
    if i == 0:
        for j in range(0, 50):
            f = open("%d.in" %j, "w")
            f.write( str(i+1) + "\n7\n")
            f.close
    #retorna ementa
    elif i == 1:
        k = -1
        for j in range(50, 100):
            f = open(str(j) + ".in", "w")
            if (j%5) == 0:
                k = k + 1
            f.write( str(i+1) + " " + str(disciplines[k]) + "\n7\n")
            f.close
    #retorna informacoes 1 disciplina
    elif i == 2:
        k = -1
        for j in range(100, 150):
            f = open(str(j) + ".in", "w")
            if (j%5) == 0:
                k = k + 1
            f.write( str(i+1) + " " + str(disciplines[k]) + "\n7\n")
            f.close
    #todas as informacoes de todas
    elif i == 3:
        for j in range(150, 200):
            f = open(str(j) + ".in", "w")
            f.write( str(i+1) + "\n7\n")
            f.close
    #escreve comentario
    elif i == 4:
        k = -1
        for j in range(200, 250):
            f = open(str(j) + ".in", "w")
            if (j%5) == 0:
                k = k + 1
            f.write( str(i+1) + " " + str(disciplines[k]) + " " + str(professors[k]) + " " + str(professors[k]) + "123 oiiii" "\n7\n")
            f.close
    #retorna comentario
    elif i == 5:
        k = -1
        for j in range(250, 300):
            f = open(str(j) + ".in", "w")
            if (j%5) == 0:
                k = k + 1
            f.write( str(i+1) + " " + str(disciplines[k]) + "\n7\n")
            f.close
