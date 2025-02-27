# LeakProof - Detector Inteligente de Vazamento de Gás

## Descrição do Projeto
O *LeakProof* é um sistema de detecção de vazamento de gás desenvolvido utilizando o **Raspberry Pi Pico W**. O projeto simula a detecção de um vazamento utilizando um joystick como entrada de dados em substituição a um sensor de gás real. Caso seja detectada uma variação crítica na leitura do joystick, um alerta visual e sonoro é acionado.

## Demonstração do Projeto
Assista ao vídeo demonstrativo no YouTube: [Clique aqui](https://youtu.be/nvFKVmY12fA)

## Tecnologias Utilizadas
- **Microcontrolador:** Raspberry Pi Pico W
- **Linguagem de Programação:** C
- **IDE:** VS Code
- **Comunicação:** I2C para display OLED
- **Leitura de Dados:** ADC para capturar valores do joystick
- **Alertas:** LEDs e buzzer acionados por GPIOs

## Componentes Utilizados
- Raspberry Pi Pico W
- Joystick analógico
- Display OLED (I2C)
- LEDs (Vermelho, Verde e Azul)
- Buzzer
- Resistores e fios de conexão

## Funcionamento do Sistema
1. O Raspberry Pi Pico W lê os valores do joystick via **ADC**.
2. Os valores são comparados com um **limite predefinido**.
3. Se um vazamento for detectado:
   - O **buzzer** é ativado.
   - O **LED vermelho** acende.
   - O **display OLED** exibe a mensagem **"ALERTA: GÁS DETECTADO"**.
4. Se os valores estiverem normais:
   - O **LED verde** acende.
   - O display exibe **"RECEBENDO DADOS"**.

## Esquemático das Conexões
| Componente       | GPIO do Pico |
|-----------------|-------------|
| Joystick X      | 26 (ADC0)    |
| Joystick Y      | 27 (ADC1)    |
| LED Verde      | 11          |
| LED Azul       | 12          |
| LED Vermelho   | 13          |
| Buzzer        | 10          |
| Display OLED SDA | 14          |
| Display OLED SCL | 15          |

## Como Rodar o Projeto
1. Clone este repositório:
   ```sh
   git clone https://github.com/seu-usuario/leakproof
   ```
2. Abra o projeto na **IDE VS Code**.
3. Compile e envie o código para o **Raspberry Pi Pico W**.
4. Conecte os componentes de acordo com o esquemático.
5. Ligue o sistema e monitore os alertas no display e LEDs.

**Desenvolvido por:** Daniel Souza Silva - Embarcatech 2025
