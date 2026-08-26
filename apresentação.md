## Apresentação:
Jogo da velha em C++

---

### Tecnologias utilizadas: 
C++ para lógica geral (motor do jogo);
QT  para a interface gráfica;
QMake como motor de build;

---

### Modos de jogo: 
- Versus: jogador vs jogador;
- Fácil: bot com jogadas aleatórias;
- Médio: bot com metade das jogadas aleatórias, metade algoritmica;
- Difícil: bot com jogadas algoritmicas;
- Neo: jogador vs jogador com limitação de peças.

---

### Algoritmo do modo díficil:
#### minimax:
Algoritmo baseado em backtracking, utilizado para definir jogadas otimizadas principalmente em jogos "versus" baseados em turnos é também muito efetivo no xadrez.

---

Constrói uma árvore de jogadas possíveis, com nós que representam os estados de jogo, juntamente com os possíveis movimentos seguintes, então aplica valores a cada nó de jogada possível.

--- 

Com as jogadas mapeadas, dois tipos de "jogadores" pensam na próxima jogada: Um busca maximizar o score final, enquanto o outro busca minimizar o score do oponente.

---

![](assets/Sem%20título-2026-07-31-1629(1).svg)