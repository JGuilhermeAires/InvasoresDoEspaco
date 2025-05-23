# Invasores do Espaço

## 👥 Integrantes
- João Guilherme (@JGuilhermeAires)
- Bruno Braga (@Bruno-h-Braga)
- Glauco Santos (@glaucosantos002)

## 🧑‍🏫 Disciplina
Programação Imperativa e Funcional - 2025.1

## 🏫 Instituição
CESAR School

## 🧰 Como compilar e executar

### Pré-requisitos:
- Compilador C (como `gcc`)
- Terminal (Linux, macOS ou Windows com WSL)
- (Opcional) Biblioteca `ncurses` se usar entrada em tempo real

### Instruções:

1. Clone o repositório:
   ```bash
git clone https://github.com/JGuilhermeAires/SpaceInvaders.git
cd SpaceInvaders

sudo apt install build-essential libncurses5-dev libncursesw5-dev

make

./spaceinvaders
   
## 🎮 sobre o Jogo:

Esta é uma versão simplificada do clássico jogo Space Invaders, adaptada para ser jogada em uma interface de linha de comando (terminal). 
Você controla uma nave na parte inferior da tela com o objetivo de destruir todas as naves inimigas que aparecem acima.

Objetivo Principal:

Destruir todas as naves inimigas para vencer o jogo!
Como Jogar e Interagir:

Sua Nave:

Você controla a nave representada pelos caracteres: <^^>
Sua nave está localizada na parte inferior da área de jogo.
Inimigos:

As naves inimigas são representadas pelos caracteres: ['.']
Elas aparecem em múltiplas fileiras na parte superior da área de jogo (configuramos para 3 fileiras de 5 inimigos cada).
Controles:

Mover para a Esquerda: Pressione a tecla A (ou a) ou a Seta Esquerda do teclado.
Mover para a Direita: Pressione a tecla D (ou d) ou a Seta Direita do teclado.
Atirar: Pressione a tecla Espaço. Sua nave disparará um projétil (^) para cima.
Sair do Jogo: Pressione a tecla Q (ou q) a qualquer momento para encerrar o jogo.
Mecânicas do Jogo:

Movimentação: Sua nave pode se mover horizontalmente dentro dos limites de uma área de jogo demarcada por bordas.
Disparos: Ao atirar, um projétil é lançado da sua nave em direção ao topo da tela.
Destruindo Inimigos: Se um dos seus projéteis atingir uma nave inimiga, ela será destruída e sua pontuação aumentará.
Múltiplos Tiros: Você pode ter um número limitado de projéteis ativos na tela ao mesmo tempo.
Como Vencer:

Você vence o jogo ao destruir com sucesso todas as naves inimigas na tela.
Ao vencer, a mensagem "Parabens voce venceu" será exibida.
Fim de Jogo:

O jogo termina se você pressionar Q para sair.
O jogo também termina após a mensagem de vitória ser exibida por alguns segundos.
Divirta-se jogando sua versão do Space Invaders!
