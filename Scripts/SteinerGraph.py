import networkx as nx
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
G=nx.Graph()

edges=open("Solution.txt", "r")
lista=[]
for lin in edges.readlines():
    x=(str(lin.split("\t")[0]),str(lin.split("\t")[1]))
    G.add_node(str(lin.split("\t")[0]))
    G.add_node(str(lin.split("\t")[1]))
    G.add_nodes_from(x)
    G.add_edge(*x)

nx.draw(G,with_labels=True)
plt.savefig("Solution_Steiner.png")
plt.show()
