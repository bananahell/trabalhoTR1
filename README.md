# Trabalho de TR1

Trabalho da matéria de Teleinformática e Redes
14/0065032 - Pedro Nogueira
UnB - 2020/2

## Especificações

### PDF's

Os PDF's do professor estão na raiz do projeto. Qualquer coisa a mais que aparecer, vamos salvar aqui.

### fonte

Pasta com todo o código do trabalho.

#### makefile

Contém vários comandos, mas só precisa de um na console ```make ajuda``` para que as mostre.

#### lib, include e src

Organização que o makefile faz:

* lib - Recebe bibliotecas importadas
* include - Onde vão os headers (nosso caso, .h's)
* src - Onde vai o código (.cpp's)
* bin - Recebe arquivos gerados de objeto (.o's)

### Esse README.md

Vamos sempre atualizar, se atentando ao formato markdown dele. Inclusive os espaços no final das linhas!!!

## Estilo

O [VSCode](code.visualstudio.com) tem uma ótima integração com o [WSL2](ubuntu.com/wsl), por isso vou usar E RECOMENDO seu uso também.  
Nele vou estar usando [a extensão de C++ mais famosa lá](marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) e vou configurar para usar o estilo da Google, simples e puro.  
Para documentação, vamos fazer em LaTeX no [overleaf](overleaf.com), e recomendo a gente explorar [esses templates da IEEE](http://www.ieee.org/conferences_events/conferences/publishing/templates.html).

## Conteúdo do trabalho

Em teleinformática e redes, é estudado como se faz a metade mais baixo nível de uma rede: as camadas física e de enlace. Esse trabalho visa simular essas duas camadas em C++, transportando uma mensagem de texto de um ponto ao outro passando por protocolos estudados na matéria.

### Camada Física

Essa camada é encarregada de carregar bits brutos que foram processados várias e várias vezes em suas camadas anteriores de um ponto ao outro. Para isso, ela pode adaptar um de vários protocolos, e nesse trabalho simulamos três deles:

#### Codificação Binária

Codificação que simplesmente carrega o fluxo bruto de bits exatamente como recebido:
``010011`` -> sinal recebido
``010011`` -> sinal enviado

#### Codificação Manchester

Codificação que aumenta a banda de sinal dos bits fazendo uma XOR do sinal com um clock de frequência igual ao período de um único bit:
``` 0 1 0 0 1 1``` -> sinal recebido
 ```010101010101``` -> clock
 ```011001011010``` -> sinal enviado

#### Codificação Bipolar

Codificação que aumenta a amplitude do sinal original dos bits alternando os bits ```1``` entre ```1``` e ```-1```:
```  0  1  0  0  1  1``` -> sinal recebido
 ```  0  1  0  0 -1  1``` -> sinal enviado