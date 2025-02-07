# Projeto de Controle de Display OLED e LEDs Neopixel com Raspberry Pi Pico

João Vitor S. Amorim

# VIDEO EXPLICATIVO:

  https://drive.google.com/file/d/1_jr9mcL1o8ER95EGifqHQOYrNAUupktw/view?usp=sharing



# Descrição do Projeto
Este projeto demonstra o uso de um Raspberry Pi Pico para controlar um display OLED SSD1306 e uma matriz de LEDs Neopixel. Através de botões de entrada, o estado dos LEDs é alterado e exibido no display OLED. Além disso, caracteres recebidos via UART são exibidos no display e também representados na matriz de LEDs Neopixel.

# Requisitos de Hardware para o projeto:

1. Controle do Display OLED SSD1306:

 - Inicialização e configuração do display via I2C.

 - Desenho de caracteres e strings no display.

 - Atualização do display com os estados dos LEDs e caracteres recebidos via UART.

2. Controle da Matriz de LEDs Neopixel:

- Inicialização dos LEDs Neopixel utilizando PIO do Raspberry Pi Pico.

- Renderização de caracteres em uma matriz de LEDs.

- Atualização da matriz com base nos caracteres recebidos via UART.

3. Manipulação de Botões com Debounce:

- Configuração dos pinos GPIO como entrada para os botões e ativação dos resistores de pull-up.

- Tratamento de interrupções com debounce para evitar leituras erradas.

- Alteração do estado dos LEDs vermelhos, verdes e azuis com base nas interrupções dos botões.

4. Comunicação UART:

- Recebimento de caracteres via UART.

- Exibição dos caracteres recebidos no display OLED e na matriz de LEDs.

# Arquivos do Projeto
1. definido.h: Define os pinos GPIO para os botões e LEDs, constantes de tempo de debounce e dimensões do display OLED.

# font.h:

- Contém as definições da fonte utilizada para desenhar caracteres no display OLED.

# ssd1306.c: 

- Biblioteca para controle do display OLED SSD1306, incluindo funções de inicialização, configuração e desenho de pixels e formas.

# Ppixel.c:

- Biblioteca para controle da matriz de LEDs Neopixel, incluindo funções para inicialização e renderização de matrizes booleanas e RGB.


# main.c: 

- Código principal que inicializa o GPIO, display, Neopixel e trata das interrupções dos botões. Além disso, recebe caracteres via UART e atualiza o display OLED e a matriz de LEDs com esses caracteres.

# Funcionalidades
- Controle do Display OLED SSD1306:

- Inicialização e configuração do display via I2C.

- Desenho de caracteres e strings no display.

- Atualização do display com os estados dos LEDs e caracteres recebidos via UART.

# Controle da Matriz de LEDs Neopixel:

- Inicialização dos LEDs Neopixel utilizando PIO do Raspberry Pi Pico.

- Renderização de caracteres em uma matriz de LEDs.

- Atualização da matriz com base nos caracteres recebidos via UART.


# Alteração do estado dos LEDs vermelhos, verdes e azuis com base nas interrupções dos botões.

- Comunicação UART:

- Recebimento de caracteres via UART.

- Exibição dos caracteres recebidos no display OLED e na matriz de LEDs.

# Como Usar:

1. Configuração do Hardware:

- Conecte o display OLED SSD1306 aos pinos I2C do Raspberry Pi Pico.

- Conecte os LEDs Neopixel ao pino definido em Ppixel.h.

- Conecte os botões de entrada aos pinos definidos em definido.h.

- Compilação e Upload:

- Compile o código utilizando o SDK do Raspberry Pi Pico.

- Faça o upload do binário compilado para o Raspberry Pi Pico.

# Execução:

- Após a inicialização, o display OLED exibirá as mensagens de status dos LEDs.

- Pressione os botões para alterar o estado dos LEDs e observe as alterações no display e na matriz de LEDs.

- Envie caracteres via UART para que sejam exibidos no display e na matriz de LEDs.

# Conclusão

Este projeto oferece uma implementação robusta e funcional para controle de um display OLED SSD1306 e LEDs Neopixel utilizando um Raspberry Pi Pico. Ele integra diversas funcionalidades, incluindo manipulação de botões com debounce, comunicação UART e renderização gráfica, proporcionando uma base sólida para aplicações mais complexas.