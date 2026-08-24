# ESP32 - Controle de Lâmpada por Palmas

Projeto de Internet das Coisas desenvolvido com ESP32 para controle de uma lâmpada através de palmas, utilizando um sensor de som, comunicação Wi-Fi e protocolo MQTT.

## Objetivo

Desenvolver um dispositivo IoT capaz de detectar uma palma através de um microfone, alternar o estado de uma lâmpada e também permitir o controle remoto através de MQTT.

O ESP32 será responsável por:

- Detectar o som produzido por uma palma;
- Processar o sinal recebido pelo sensor;
- Alternar o estado da lâmpada através de um relé;
- Conectar-se à rede Wi-Fi;
- Publicar informações do sensor via MQTT;
- Receber comandos remotos via MQTT;
- Publicar a confirmação do estado do relé;
- Tentar reconectar automaticamente caso perca a conexão Wi-Fi ou MQTT.

## Funcionamento

O sistema funciona da seguinte maneira:

1. O microfone detecta uma variação de intensidade sonora.
2. O ESP32 realiza a leitura do sinal analógico.
3. Quando o sinal ultrapassa o limite configurado para uma palma, o ESP32 considera que houve uma palma.
4. O estado da lâmpada é alternado.
5. O ESP32 publica o novo estado através do MQTT.
6. Um dispositivo remoto também pode enviar um comando MQTT para ligar, desligar ou alternar a lâmpada.

## Componentes

### Controlador

- 1x ESP32 DevKit V1

### Sensor

- 1x módulo de microfone com amplificador MAX9814
- Tipo: sensor de som/microfone analógico
- Saída: sinal analógico
- Alimentação: 3,3 V

O MAX9814 foi escolhido porque fornece uma saída analógica que pode ser lida pelo ADC do ESP32, permitindo analisar a intensidade sonora.

### Atuador

- 1x módulo relé de 1 canal, compatível com ESP32
- Alimentação: 5 V
- Entrada de controle: GPIO digital

O relé será utilizado para controlar a lâmpada.

> Para os testes iniciais, recomenda-se utilizar uma carga de baixa tensão. A ligação de uma lâmpada diretamente à rede elétrica deve ser realizada somente com os cuidados e procedimentos de segurança adequados.

### Outros componentes

- Protoboard
- Jumpers macho-macho
- Jumpers macho-fêmea
- Fonte USB para o ESP32
- Cabo USB
- Resistores, caso necessários para adaptação do circuito
- Caixa/estrutura para acomodação do circuito

## Ligações

| Componente | ESP32 |
|---|---|
| MAX9814 VCC | 3V3 |
| MAX9814 GND | GND |
| MAX9814 OUT | GPIO 34 |
| Relé IN | GPIO 26 |
| Relé VCC | 5V |
| Relé GND | GND |

O GPIO 34 foi escolhido para a leitura analógica porque é um pino de entrada do ADC do ESP32.

O GPIO 26 será utilizado para controlar o relé.

## Arquitetura MQTT

Os tópicos utilizados pelo projeto são:

```text
grupoX/sensor/som
grupoX/comando/rele
grupoX/status/rele
grupoX/status/esp32

## Feedback da Aula 04

- Não tivemos feedback