# SteinerTreeGraph

Os algoritmos estão divididos em dois arquivos .c:

IntCompSteiner.c (Construtivo, Busca Local , GRASP e GRASP+PR)

GA_Heuristic.c

Ambos tem seus principais parâmetros definidos como argumento na linha de comando. 

Para o arquivo IntCompSteiner.c, temos as seguintes opções:
- nome do arquivo*
- semente
- tempo de execução
- Target para o tttplot
- boleno 0 ou 1(sim) para execução do Path-Relinking
- tamanho do conjunto elite

Para o arquivo GA_Heuristic.c, temos as seguintes opções:
- nome do arquivo*
- semente
- tempo de execução
- Target para o tttplot
- iterações para tttplot

*Necessário que os arquivos estejam no mesmo diretório que os arquivos .c, caso contrário ao invés dos nomes será necessário o caminho das instâncias.

A máquina onde os experimentos foram executados é a seguinte: Processador 1,8 GHz Intel Core i5, 8 GB 1600 MHz DDR3 e 128GB SSD.

Quanto ao formato das instâncias, estão descritas no relatório do trabalho.

