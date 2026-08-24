# Protótipo do Produto

## Descrição

O protótipo será composto por uma caixa contendo o ESP32, o sensor de som e o módulo relé.

O sensor de som ficará posicionado em uma abertura da caixa para facilitar a captação das palmas.

O ESP32 ficará conectado ao sensor através do GPIO 34 e ao módulo relé através do GPIO 26.

## Esboço do protótipo

```text
        ┌─────────────────────────────────┐
        │                                 │
        │       CAIXA DO DISPOSITIVO      │
        │                                 │
        │   ┌───────────────┐             │
        │   │   MAX9814     │             │
        │   │  MICROFONE    │             │
        │   └───────┬───────┘             │
        │           │                     │
        │           │ sinal analógico     │
        │           ▼                     │
        │   ┌───────────────┐             │
        │   │     ESP32     │             │
        │   │               │             │
        │   │ GPIO 34 ◄─────┤             │
        │   │ GPIO 26 ─────►│             │
        │   └───────┬───────┘             │
        │           │                     │
        │           │ GPIO 26             │
        │           ▼                     │
        │   ┌───────────────┐             │
        │   │     RELÉ      │             │
        │   └───────┬───────┘             │
        │           │                     │
        └───────────┼─────────────────────┘
                    │
                    ▼
                 LÂMPADA