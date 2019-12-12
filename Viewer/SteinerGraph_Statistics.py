import networkx as nx
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import seaborn as sns

edges3=open("result_rand_0_0_100.txt", "r")

custo3=[]
for lin in edges3.readlines():
    print(lin.split("\t"))
    custo3.append(float(lin.split("\t")[1]))

custo3=pd.DataFrame(custo3)

edges4=open("result_rand_0_5_100.txt", "r")

custo4=[]
for lin in edges4.readlines():
    print(lin.split("\t"))
    custo4.append(float(lin.split("\t")[1]))

custo4=pd.DataFrame(custo4)


edges5=open("result_rand_1_0_100.txt", "r")

custo5=[]
for lin in edges5.readlines():
    print(lin.split("\t"))
    custo5.append(float(lin.split("\t")[1]))

custo5=pd.DataFrame(custo5)


edges6=open("result_rand_0_2_100.txt", "r")

custo6=[]
for lin in edges6.readlines():
    print(lin.split("\t"))
    custo6.append(float(lin.split("\t")[1]))

custo6=pd.DataFrame(custo6)

edges8=open("result_rand_0_8_100.txt", "r")

custo8=[]
for lin in edges8.readlines():
    print(lin.split("\t"))
    custo8.append(float(lin.split("\t")[1]))

custo8=pd.DataFrame(custo8)


print(np.min(custo5[0]))
print(np.max(custo5[0]))
#plt.hist(custo4[0],bins=np.arange(np.min(custo4[0]),np.max(custo4[0]),step=1),label='Random alfa 1 - 1000 turns')

#plt.hist(custo6[0],bins=np.arange(np.min(custo6[0]),np.max(custo6[0]),step=1),label='Random alfa 1 - 2000 turns')
#plt.hist(custo3[0],label='Greedy')
#plt.hist(custo6[0],bins=np.arange(np.min(custo6[0]),np.max(custo6[0]),step=4),label='Random alfa 0.2 - 500 turns')
#plt.hist(custo4[0],bins=np.arange(np.min(custo4[0]),np.max(custo4[0]),step=4),label='Random alfa 0.5 - 500 turns')
#plt.hist(custo5[0],bins=np.arange(np.min(custo5[0]),np.max(custo5[0]),step=4),label='Random alfa 1.0 - 500 turns')
#plt.xticks(np.arange(np.min(custo3[0])-5,np.max(custo5[0]),step=5))
#plt.hist(custo8[0],bins=np.arange(np.min(custo8[0]),np.max(custo8[0]),step=1),label='Random alfa 1 - 500 turns')
#plt.hist(custo4[0],label='Random alfa 0.5 - 100 turns')
    
#plt.axvline(x=np.min(custo3[0]),label='Greed',c='r')

#plt.legend()
#plt.xlabel("Custo")
#plt.ylabel("Ocorrencia")
#plt.title("Analise de Custo entre Heuristicas")
#plt.show()

y=[np.mean(custo6[0]),np.mean(custo4[0]),np.mean(custo8[0]),np.mean(custo5[0])]
x=[0.2,0.5,0.8,1.0]
plt.plot(x,y,c='red')

#y=[np.max(custo3[0]),np.max(custo6[0]),np.max(custo4[0]),np.max(custo8[0]),np.max(custo5[0])]
#x=[0.0,0.2,0.5,0.8,1.0]
#plt.plot(x,y,c='black',label='Melhor Custo')
plt.xlim(0.2,1)
#plt.legend()
plt.xlabel("Alpha")
plt.ylabel("Time")
plt.show()

edges3=open("result_rand_0_0_100.txt", "r")

custo3=[]
for lin in edges3.readlines():
    print(lin.split("\t"))
    custo3.append(float(lin.split("\t")[1]))

custo3=pd.DataFrame(custo3)

edges4=open("result_rand_0_5_100.txt", "r")

custo4=[]
for lin in edges4.readlines():
    print(lin.split("\t"))
    custo4.append(float(lin.split("\t")[1]))

custo4=pd.DataFrame(custo4)





edges5=open("result_rand_1_0_100.txt", "r")

custo5=[]
for lin in edges5.readlines():
    print(lin.split("\t"))
    custo5.append(float(lin.split("\t")[1]))

custo5=pd.DataFrame(custo5)


edges6=open("result_rand_0_2_100.txt", "r")

custo6=[]
for lin in edges6.readlines():
    print(lin.split("\t"))
    custo6.append(float(lin.split("\t")[1]))

custo6=pd.DataFrame(custo6)

print(np.mean(custo6[0]))
print(np.mean(custo5[0]))
print(np.mean(custo4[0]))
print(np.mean(custo3[0]))
