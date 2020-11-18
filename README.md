# CC7711 - INTELIGENCIA ARTIF.E ROBOTICA -Controle Robô
## Nome: Lucas Machado Serain RA: 22.217.007-8

## Enunciado
Desenvolve o módulo de controle do robô para que ele toque em todos os blocos do mundo e identifique quais deles ão móveis.

Ao detectar um módulo móvel, o robô deve piscars todos os seus leds por três veses e depois manter acesso a quantidade de leda igual a quantidade de blocos móveis que ele detectou (um bloco = 1 led acesso e dpoies acende o segundo led quando identificar um segundo bloco móvel).

## Solução proposta
### Identificar colisão
Para detectar a colisão, utilizei o componente gyro, descrito na documentação do e-puck.
Esse componente, através do método /i wb_gyro_get_values, retorna um vetor de 3 dimensões, contendo a velocidade em rad/seg, de cada roda do robo.
Após análise, conclui que quando os valores x e y desse vetor se aproximavam de 0, significava que o robo estava colidindo com algum objeto,
redundo assim sua velocidade.

Com base nisso, adicionei um if verificando se a velocidade X e Y estavam proximas de zero, caso sim, faço a verificação dos 7 sensores distribuidos pelo robo.

Quando a colisão é detectada no lado esquerdo do robô, então desacelero na direita e acelero na esquerda, fazendo com que ele vire.

### Colisão com caixas móveis
Para realizar a colisão com caixas móveis, utilizei supervisores, tanto para o robo, quanto para a caixa, com esse componente, é possível saber a posição de ambos no mundo da simulação.

Com as posições detectadas, faço um calculo de distancia do eixo x e y entre o robo e a caixa, e caso esse valor seja baixo, ativo os colisores,
pisco todos os leds e seto os leds com numeros de caixas identificadas.

Também marco a caixa como verificada para que não contabilize nas proximas iterações.

### Fluxograma

 ``` mermaid
graph TD
    A[Inicio] --> B[Declara variaveis];
    B --> C[Inicializa componentes do robo];
    C --> D[Inicializa sensores];
    D --> E[Inicializa LEDS];
    E --> F[Calcula media das duas rodinhas atraves do Gyro]
    F --> G{media >= - 0.059 && media <=0.058}
    G --> |Sim| H{Sensor 0 ativado?};
    H --> |Sim| I[Acelerar direita];
    I --> F
    H --> |Não| J{Sensor n ativado?};
    J --> |Sim| I[Acelerar direita/esquerda];
    G --> |Não| Z[Obter posição robo];
    Z -->L[Obter posição caixa movel];
    L -->M[Calcula diferença posição x da caixa e robo]
    M -->N[Calcula diferença posição y da caixa e robo]
    N -->O{distanciaX>-0.110797 && distanciaX< -0.086810 && distanciaY< 0.00527}
    O --> |Sim| P[Ativa flag de caixa movel];
    P -->Q[Ativa os todos os leds 3x]
    Q -->S[Ativa contador de caixa atingida]
    S -->T[Ativa LEDS com base em numero de caixas colididas]
    T --> F

```


### GITHUB e link do video
https://github.com/lucasserain/CC7711-INTELIGENCIA-ARTIF.E-ROBOTICA_E-PUCK
https://www.youtube.com/watch?v=-RhLlX5aQgU
