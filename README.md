# Projeto Interrupções com Matriz de LEDs e Botões na BitDogLab

Projeto educativo utilizando o microcontrolador RP2040 para demonstrar o uso de interrupções, debouncing e controle de LEDs WS2812 em uma matriz 5x5.

## 🎯 Objetivos
- **Implementar interrupções** para tratamento de botões.
- **Resolver bouncing** via software.
- **Controlar LEDs convencionais** e matriz de LEDs endereçável.
- **Exibir números** em formato digital na matriz LED.

## ⚙️ Funcionalidades Principais
- ✅ **Piscar contínuo do LED vermelho** em 5Hz.
- ➕ **Botão A**: Incrementa número (0-9).
- ➖ **Botão B**: Decrementa número (0-9).
- 🎨 **Efeitos visuais customizados** para cada dígito.
- ⚡ **Debouncing** implementado via software.

## 🛠 Hardware Necessário
| Componente       | GPIO  |
|-------------------|-------|
| Matriz WS2812 5x5 | GPIO7 |
| LED RGB (vermelho)| GPIO13|
| Botão A           | GPIO5 |
| Botão B           | GPIO6 |

## 🚀 Como Executar
1. **Clonar o repositório**:
   ```bash
   git clone https://github.com/coelhoisaque/atividade-aula27-01.git
   ```
2. **Configurar o ambiente Pico SDK**:
   - Certifique-se de que o Raspberry Pi Pico SDK está corretamente instalado e configurado no seu ambiente de desenvolvimento.
3. **Compilar o projeto**:
   ```bash
   mkdir build && cd build
   cmake ..
   make -j4
   ```
4. **Conectar a placa BitDogLab** ao seu computador.
5. **Enviar o arquivo `ws2812.uf2`** gerado para a placa.

## 📚 Estrutura do Código
```plaintext
├── ws2812.c          # Lógica principal do projeto
├── ws2812.pio        # Programa PIO para controle dos LEDs WS2812
├── CMakeLists.txt    # Configuração de build
└── diagram.json      # Esquema de conexões Wokwi
```

## 📌 Dependências
- **Raspberry Pi Pico SDK**
- Bibliotecas necessárias:
  - `hardware/pio`
  - `pico_stdlib`
  - `hardware/gpio`

## 🎥 Demonstração
Assista ao vídeo de demonstração do projeto em funcionamento:

[![Vídeo de Demonstração](https://img.youtube.com/vi/JxUtQq1yMBE/maxresdefault.jpg)](https://youtu.be/JxUtQq1yMBE)

