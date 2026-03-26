# ✊ Jokenpo - Pedra, Papel e Tesoura 🎮

Um jogo clássico de Pedra, Papel e Tesoura desenvolvido em C com interface colorida, estatísticas em tempo real e suporte a UTF-8.

## 📋 Sobre o Projeto

Este é um jogo interativo de Jokenpo (Pedra, Papel e Tesoura) desenvolvido em linguagem C. O projeto foi criado para praticar conceitos de programação como estruturas de controle, loops, tratamento de entrada do usuário e manipulação de cores no terminal.

### Características
- 🎨 Interface colorida e amigável
- 🔄 Loop contínuo de jogo
- 📊 Estatísticas em tempo real
- 🌐 Suporte completo a UTF-8 e acentuação
- 🛡️ Validação robusta de entrada
- 🎯 Sistema de pontuação
- 💻 Compatível com Windows e Linux

## 🎮 Como Jogar

### Regras do Jogo
- **Pedra** ✊ quebra **Tesoura** ✌️
- **Tesoura** ✌️ corta **Papel** ✋
- **Papel** ✋ embrulha **Pedra** ✊

### Comandos
- Digite `1` para escolher **Pedra** ✊
- Digite `2` para escolher **Papel** ✋
- Digite `3` para escolher **Tesoura** ✌️
- Digite `0` para sair do jogo

## 🚀 Como Executar

### Pré-requisitos
- Compilador C (GCC recomendado)
- Terminal com suporte a cores ANSI

### Compilação e Execução

#### No Windows (CMD/PowerShell)
```bash
gcc jokenpo.c -o jokenpo.exe
jokenpo.exe
No Linux/Mac
bash
gcc jokenpo.c -o jokenpo
./jokenpo
Usando Git Bash (Windows)
bash
gcc jokenpo.c -o jokenpo
./jokenpo
📁 Estrutura do Projeto
text
jokenpo/
├── jokenpo.c          # Código fonte principal
├── README.md          # Documentação do projeto
└── LICENSE            # Licença do projeto
🎯 Funcionalidades
Interface Interativa
Menu colorido com ícones intuitivos

Limpeza automática da tela entre rodadas

Exibição clara dos resultados

Estatísticas
Contador de vitórias, derrotas e empates

Taxa de vitórias em porcentagem

Resumo final do jogo

Tratamento de Erros
Validação de entrada do usuário

Prevenção contra caracteres inválidos

Mensagens de erro amigáveis

💻 Exemplo de Jogo
text
╔════════════════════════════════════╗
║        JOGO DE JOKENPO            ║
║        Pedra ✊ | Papel ✋ | Tesoura ✌️  ║
╚════════════════════════════════════╝

Escolha uma opção:
  1 ✊  Pedra
  2 ✋  Papel
  3 ✌️  Tesoura
  0 🚪  Sair do jogo

Sua escolha: 1

╔════════════════════════════════════╗
║         RESULTADO DA RODADA        ║
╠════════════════════════════════════╣
║  Jogador: ✊ Pedra                  ║
║  Computador: ✌️ Tesoura             ║
╠════════════════════════════════════╣
║         🎉 VOCÊ GANHOU! 🎉          ║
╚════════════════════════════════════╝
🔧 Tecnologias Utilizadas
Linguagem C - Core do jogo

Bibliotecas Padrão: stdio.h, stdlib.h, time.h, locale.h, string.h

ANSI Escape Codes - Cores e formatação no terminal

📊 Melhorias Futuras
Adicionar modo multiplayer

Criar ranking de pontuação

Implementar diferentes níveis de dificuldade

Adicionar efeitos sonoros

Criar versão gráfica (SDL ou Raylib)

Salvar estatísticas em arquivo

🤝 Contribuindo
Contribuições são sempre bem-vindas! Sinta-se à vontade para:

Fazer um fork do projeto

Criar uma branch para sua feature (git checkout -b feature/AmazingFeature)

Commit suas mudanças (git commit -m 'Add some AmazingFeature')

Push para a branch (git push origin feature/AmazingFeature)

Abrir um Pull Request

📝 Licença
Este projeto está sob a licença MIT. Veja o arquivo LICENSE para mais detalhes.

👨‍💻 Autor
Will Vasconcelos

