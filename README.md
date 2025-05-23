# Invasores do Espaço

## 👥 Integrantes
- João Guilherme Aires Chagas de Oliveira (jgaco@cesar.school)
- Bruno Henrique Leite Braga (bhlb@cesar.school)
- Glauco Santos Seixas Cerqueira (gssc@cesar.school)

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
   git clone https://github.com/seu-usuario/projeto-tetris.git
   cd projeto-tetris
   
## Sobre o jogo:

Space Invaders é um clássico jogo de arcade lançado em 1978 pela empresa japonesa Taito e criado por Tomohiro Nishikado. Considerado um dos títulos mais influentes da história dos videogames, ele ajudou a estabelecer os fundamentos do gênero de tiro (shoot 'em up) e marcou o início da era de ouro dos arcades.

## Funcionalidades:

O jogador controla um canhão laser (também chamado de base) localizado na parte inferior da tela.

O movimento é limitado ao eixo horizontal, indo da esquerda para a direita.

O jogador pode atirar para cima com projéteis que atingem os inimigos.

## 🎮 Descrição das Mecânicas do Jogo:

Objetivo
O jogador controla uma nave representada pelos caracteres </^\>, posicionada na parte inferior da tela. O objetivo é eliminar os inimigos que aparecem na parte superior.

Jogabilidade
Movimentação do Jogador:
O jogador pode se mover horizontalmente para a esquerda ou para a direita usando as teclas "<" (esquerda) e ">" (direita). A nave se desloca apenas em linha reta na parte inferior da tela.

Tiro:
O jogador dispara projéteis verticais pressionando a tecla Espaço. O tiro parte da posição atual da nave e viaja em linha reta para cima até atingir o topo da tela ou colidir com um inimigo.

Inimigos:
Os inimigos são representados pelos caracteres /("..")\. Eles aparecem na parte superior da tela em múltiplas posições.

Colisão:
Quando o tiro do jogador atinge um inimigo, o inimigo é eliminado e desaparece da tela. O tiro também desaparece após o impacto.

Como rodar
bash:

./jogo.exe
