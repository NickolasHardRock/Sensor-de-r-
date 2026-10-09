# Assistente de estacionamento com Arduino

## Identificação acadêmica

- **Curso:** Analise e Desenvolvimento de Sistemas
- **Unidade curricular:** IOT
- **Aluno:** Nickolas
  
## Explicação do projeto

Este projeto funciona como um assistente de estacionamento em miniatura. Um sensor ultrassônico HC-SR04 mede a distância até um obstáculo à frente do veículo. A distância é indicada por um LED RGB e por um buzzer piezoelétrico:

| Distância medida | LED | Buzzer |
|---|---|---|
| Acima de 100 cm | Verde: distância segura | Silencioso |
| De 41 a 100 cm | Amarelo: o obstáculo está perto | Bipes intermitentes |
| Até 40 cm | Vermelho: está muito perto | Bipes mais rápidos |

À medida que o obstáculo se aproxima, o intervalo entre os bipes diminui. A leitura também é enviada ao Monitor Serial a 9600 baud.

## Componentes

- Placa RoboCore do kit IniciantA V8, compatível com Arduino Uno
- Sensor ultrassônico HC-SR04
- LED RGB de **cátodo comum**
- 3 resistores de 220 Ω (um em cada canal R, G e B)
- Buzzer piezoelétrico passivo
- Protoboard e jumpers

## Ligações

O diagrama abaixo mostra as conexões utilizadas no código (`estacionamento_inteligente.ino`).

![Diagrama de ligação do assistente de estacionamento](https://private-us-east-1.manuscdn.com/sessionFile/7sxDsQO67InGiIpWXFUF5D/sandbox/cZDKdHMLXzxYWi12aikLdz-images_1791500080162_na1fn_L2hvbWUvdWJ1bnR1L2VzdGFjaW9uYW1lbnRvLWludGVsaWdlbnRlL2RpYWdyYW1hL2xpZ2Fjb2Vz.png?Policy=eyJTdGF0ZW1lbnQiOlt7IlJlc291cmNlIjoiaHR0cHM6Ly9wcml2YXRlLXVzLWVhc3QtMS5tYW51c2Nkbi5jb20vc2Vzc2lvbkZpbGUvN3N4RHNRTzY3SW5HaUlwV1hGVUY1RC9zYW5kYm94L2NaREtkSE1MWHp4WVdpMTJhaWtMZHotaW1hZ2VzXzE3OTE1MDAwODAxNjJfbmExZm5fTDJodmJXVXZkV0oxYm5SMUwyVnpkR0ZqYVc5dVlXMWxiblJ2TFdsdWRHVnNhV2RsYm5SbEwyUnBZV2R5WVcxaEwyeHBaMkZqYjJWei5wbmciLCJDb25kaXRpb24iOnsiRGF0ZUxlc3NUaGFuIjp7IkFXUzpFcG9jaFRpbWUiOjE3OTM0OTEyMDB9fX1dfQ__&Key-Pair-Id=K2QY5QTL8JSY6C&Signature=MEQCID-73MXv~S5-tOSqRcUrf5rtx4g2IbHVoUwLM9kAplK1AiBKwmwE6W66Sxq2t0thLp8hIpz21bc9dy18Z1-9UZVPjw__)

| Componente | Pino do componente | Pino da placa |
|---|---|---|
| HC-SR04 | VCC | 5V |
| HC-SR04 | GND | GND |
| HC-SR04 | TRIG | D9 |
| HC-SR04 | ECHO | D10 |
| LED RGB cátodo comum | Cátodo comum | GND |
| LED RGB | R (com resistor de 300 Ω em série) | D3 |
| LED RGB | G (com resistor de 300 Ω em série) | D5 |
| LED RGB | B (com resistor de 300 Ω em série) | D6 |
| Buzzer piezo passivo | positivo/sinal | D8 |
| Buzzer piezo passivo | negativo | GND |

**Importante:** confirme o pinout do seu LED RGB antes de ligar. Os terminais variam entre modelos. O código assume um LED de cátodo comum. Se o seu LED for de ânodo comum, conecte o terminal comum ao 5V e inverta HIGH/LOW na função `definirCor()`.

## Como carregar e testar

1. Abra `estacionamento_inteligente.ino` na Arduino IDE.
2. Conecte a placa ao computador por USB.
3. Selecione a placa compatível com Arduino Uno e a porta correta em **Ferramentas**.
4. Clique em **Verificar** e depois em **Carregar**.
5. Abra o Monitor Serial em **9600 baud**.
6. Aproxime um objeto do sensor e observe as cores e a frequência dos bipes.

## Arquivos

- `estacionamento_inteligente.ino` — código-fonte do projeto.
- `diagrama/ligacoes.mmd` — fonte editável do diagrama Mermaid.
- `diagrama/ligacoes.png` — diagrama renderizado para consulta e entrega.

## Foto ou GIF do protótipo

O diagrama de ligações está incluído acima. Para documentar o protótipo físico funcionando, adicione uma foto ou GIF à pasta `imagens/` e inclua aqui, por exemplo:

```markdown
![Protótipo funcionando](imagens/projeto-funcionando.jpg)
```

Tire a foto depois de montar o circuito real; não substitua por uma imagem ilustrativa.
