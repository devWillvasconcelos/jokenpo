#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #define LIMPAR_TELA "cls"
#else
    #define LIMPAR_TELA "clear"
#endif

// Cores para terminal
#define COR_RESET   "\033[0m"
#define COR_VERMELHO "\033[31m"
#define COR_VERDE    "\033[32m"
#define COR_AMARELO  "\033[33m"
#define COR_AZUL     "\033[34m"
#define COR_MAGENTA  "\033[35m"
#define COR_CIANO    "\033[36m"
#define COR_BRANCO   "\033[37m"
#define COR_FUNDO_VERDE "\033[42m"
#define COR_NEGRITO  "\033[1m"

void limparTela() {
    system(LIMPAR_TELA);
}

void exibirCabecalho() {
    printf(COR_CIANO COR_NEGRITO);
    printf("╔════════════════════════════════════╗\n");
    printf("║        JOGO DE JOKENPO            ║\n");
    printf("║        Pedra ✊ | Papel ✋ | Tesoura ✌️  ║\n");
    printf("╚════════════════════════════════════╝\n");
    printf(COR_RESET "\n");
}

void exibirMenu() {
    printf(COR_AMARELO "Escolha uma opção:\n" COR_RESET);
    printf("  " COR_VERMELHO "1" COR_RESET " ✊  Pedra\n");
    printf("  " COR_VERMELHO "2" COR_RESET " ✋  Papel\n");
    printf("  " COR_VERMELHO "3" COR_RESET " ✌️  Tesoura\n");
    printf("  " COR_VERMELHO "0" COR_RESET " 🚪  Sair do jogo\n");
    printf(COR_CIANO "\nSua escolha: " COR_RESET);
}

void exibirResultadoRodada(int jogador, int computador, int resultado) {
    char* jogadorNome;
    char* computadorNome;
    char* iconeJogador;
    char* iconeComputador;
    
    switch(jogador) {
        case 1: jogadorNome = "Pedra"; iconeJogador = "✊"; break;
        case 2: jogadorNome = "Papel"; iconeJogador = "✋"; break;
        case 3: jogadorNome = "Tesoura"; iconeJogador = "✌️"; break;
    }
    
    switch(computador) {
        case 1: computadorNome = "Pedra"; iconeComputador = "✊"; break;
        case 2: computadorNome = "Papel"; iconeComputador = "✋"; break;
        case 3: computadorNome = "Tesoura"; iconeComputador = "✌️"; break;
    }
    
    printf(COR_BRANCO "\n╔════════════════════════════════════╗\n");
    printf("║         RESULTADO DA RODADA        ║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║  Jogador: %s %-15s ║\n", iconeJogador, jogadorNome);
    printf("║  Computador: %s %-12s ║\n", iconeComputador, computadorNome);
    printf("╠════════════════════════════════════╣\n");
    
    if(resultado == 0) {
        printf("║  " COR_AMARELO COR_NEGRITO "        ⚡ EMPATE! ⚡            " COR_RESET "║\n");
    } else if(resultado == 1) {
        printf("║  " COR_VERDE COR_NEGRITO "        🎉 VOCÊ GANHOU! 🎉         " COR_RESET "║\n");
    } else {
        printf("║  " COR_VERMELHO COR_NEGRITO "        😢 VOCÊ PERDEU! 😢        " COR_RESET "║\n");
    }
    
    printf("╚════════════════════════════════════╝\n" COR_RESET);
}

int determinarResultado(int jogador, int computador) {
    if(jogador == computador) return 0; // Empate
    if((jogador == 1 && computador == 3) || 
       (jogador == 2 && computador == 1) || 
       (jogador == 3 && computador == 2)) {
        return 1; // Vitória
    }
    return -1; // Derrota
}

int obterEscolhaJogador() {
    int escolha;
    char entrada[10];
    
    while(1) {
        exibirMenu();
        
        if(fgets(entrada, sizeof(entrada), stdin) != NULL) {
            // Remove o newline da entrada
            size_t len = strlen(entrada);
            if(len > 0 && entrada[len-1] == '\n') {
                entrada[len-1] = '\0';
            }
            
            // Verifica se a entrada é um número
            int valido = 1;
            for(int i = 0; i < strlen(entrada); i++) {
                if(entrada[i] < '0' || entrada[i] > '9') {
                    valido = 0;
                    break;
                }
            }
            
            if(valido) {
                escolha = atoi(entrada);
                if(escolha >= 0 && escolha <= 3) {
                    return escolha;
                }
            }
        }
        
        printf(COR_VERMELHO "\n❌ Opção inválida! Digite 0, 1, 2 ou 3.\n" COR_RESET);
        printf("Pressione Enter para continuar...");
        getchar();
        limparTela();
        exibirCabecalho();
    }
}

void exibirEstatisticas(int vitorias, int derrotas, int empates, int totalJogos) {
    printf(COR_MAGENTA COR_NEGRITO "\n╔════════════════════════════════════╗\n");
    printf("║         ESTATÍSTICAS DO JOGO       ║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║  " COR_VERDE "Vitórias: %-23d" COR_MAGENTA "║\n", vitorias);
    printf("║  " COR_VERMELHO "Derrotas: %-23d" COR_MAGENTA "║\n", derrotas);
    printf("║  " COR_AMARELO "Empates:  %-23d" COR_MAGENTA "║\n", empates);
    printf("║  " COR_BRANCO "Total de jogos: %-18d" COR_MAGENTA "║\n", totalJogos);
    
    if(totalJogos > 0) {
        float taxaVitorias = (vitorias * 100.0) / totalJogos;
        printf("║  Taxa de vitórias: %-18.1f%% ║\n", taxaVitorias);
    }
    
    printf("╚════════════════════════════════════╝\n" COR_RESET);
}

void jogarNovamente() {
    char opcao;
    printf(COR_CIANO "\nDeseja jogar novamente? (s/n): " COR_RESET);
    scanf(" %c", &opcao);
    getchar(); // Limpa o buffer
    
    if(opcao != 's' && opcao != 'S') {
        printf(COR_VERDE "\nObrigado por jogar! Até mais! 🎮\n" COR_RESET);
        exit(0);
    }
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        system("chcp 65001 > nul");
    #endif
    
    int escolhaJogador, escolhaComputador, resultado;
    int vitorias = 0, derrotas = 0, empates = 0;
    int continuar = 1;
    
    srand(time(0));
    
    while(continuar) {
        limparTela();
        exibirCabecalho();
        
        escolhaJogador = obterEscolhaJogador();
        
        if(escolhaJogador == 0) {
            printf(COR_VERDE "\n✨ Saindo do jogo...\n" COR_RESET);
            break;
        }
        
        escolhaComputador = rand() % 3 + 1;
        resultado = determinarResultado(escolhaJogador, escolhaComputador);
        
        limparTela();
        exibirCabecalho();
        exibirResultadoRodada(escolhaJogador, escolhaComputador, resultado);
        
        // Atualiza estatísticas
        if(resultado == 0) {
            empates++;
        } else if(resultado == 1) {
            vitorias++;
        } else {
            derrotas++;
        }
        
        exibirEstatisticas(vitorias, derrotas, empates, vitorias + derrotas + empates);
        
        printf(COR_CIANO "\n────────────────────────────────────────\n" COR_RESET);
        char opcao;
        printf(COR_CIANO "Pressione ENTER para continuar jogando");
        printf(COR_AMARELO " ou 'q' para sair" COR_RESET);
        printf(COR_CIANO ": " COR_RESET);
        
        char entrada[10];
        fgets(entrada, sizeof(entrada), stdin);
        if(entrada[0] == 'q' || entrada[0] == 'Q') {
            continuar = 0;
        }
    }
    
    printf(COR_FUNDO_VERDE COR_NEGRITO "\n╔════════════════════════════════════╗\n");
    printf("║      RESUMO FINAL DO JOGO        ║\n");
    printf("╚════════════════════════════════════╝\n" COR_RESET);
    exibirEstatisticas(vitorias, derrotas, empates, vitorias + derrotas + empates);
    
    printf(COR_VERDE COR_NEGRITO "\n🎮 Obrigado por jogar! Até a próxima! 🎮\n" COR_RESET);
    
    return 0;
}
