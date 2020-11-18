# CC7711-INTELIGENCIA-ARTIF.E-ROBOTICA_E-PUCK

## Projeto para a discicplina de Inteligencia Artitficial

## Fluxograma

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
