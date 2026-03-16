#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_CIDADES 50
#define MAX_NOME 100

typedef struct {
    char nome[MAX_NOME];
    char estado[MAX_NOME];
    char uf[3];
    char regiao[MAX_NOME];
    long long populacao;
    float area;
    long long pib;
    int pontos_turisticos;
    float idh;
    float densidade;
    long long pib_per_capita;
} Cidade;

// Função para limpar espaços e aspas de uma string
void limpar_string(char *str) {
    char *inicio = str;
    char *fim;
    
    // Remover espaços no início
    while(isspace((unsigned char)*inicio)) inicio++;
    
    // Remover aspas no início
    while(*inicio == '"') inicio++;
    
    // Encontrar o final
    fim = str + strlen(str) - 1;
    
    // Remover espaços, aspas e vírgulas no final
    while(fim > inicio && (isspace((unsigned char)*fim) || *fim == '"' || *fim == ',' || *fim == ']' || *fim == '}')) fim--;
    
    // Mover para o início
    if(inicio != str) {
        memmove(str, inicio, fim - inicio + 1);
    }
    str[fim - inicio + 1] = '\0';
}

// Função para extrair valor de uma linha JSON
void extrair_valor(char *linha, char *valor) {
    char *inicio = strchr(linha, ':');
    if (inicio) {
        inicio++; // Pular o ':'
        strcpy(valor, inicio);
        limpar_string(valor);
    } else {
        valor[0] = '\0';
    }
}

// Função para carregar cidades do arquivo JSON
int carregar_cidades(const char *arquivo, Cidade cidades[]) {
    FILE *file = fopen(arquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        return 0;
    }
    
    char linha[512];
    int num_cidades = 0;
    int lendo_cidade = 0;
    
    while (fgets(linha, sizeof(linha), file)) {
        // Remover espaços extras
        char *ptr = linha;
        while (*ptr == ' ' || *ptr == '\t') ptr++;
        
        // Verificar se é início de uma cidade
        if (strstr(ptr, "{") && !lendo_cidade) {
            lendo_cidade = 1;
            continue;
        }
        
        if (lendo_cidade) {
            char valor[256];
            
            if (strstr(ptr, "\"nome\"")) {
                extrair_valor(ptr, valor);
                strcpy(cidades[num_cidades].nome, valor);
            }
            else if (strstr(ptr, "\"estado\"") && !strstr(ptr, "regiao")) {
                extrair_valor(ptr, valor);
                strcpy(cidades[num_cidades].estado, valor);
            }
            else if (strstr(ptr, "\"uf\"")) {
                extrair_valor(ptr, valor);
                strcpy(cidades[num_cidades].uf, valor);
            }
            else if (strstr(ptr, "\"regiao\"")) {
                extrair_valor(ptr, valor);
                strcpy(cidades[num_cidades].regiao, valor);
            }
            else if (strstr(ptr, "\"populacao\"")) {
                extrair_valor(ptr, valor);
                cidades[num_cidades].populacao = atoll(valor);
            }
            else if (strstr(ptr, "\"area\"")) {
                extrair_valor(ptr, valor);
                cidades[num_cidades].area = atof(valor);
            }
            else if (strstr(ptr, "\"pib\"")) {
                extrair_valor(ptr, valor);
                cidades[num_cidades].pib = atoll(valor);
            }
            else if (strstr(ptr, "\"pontos_turisticos\"")) {
                extrair_valor(ptr, valor);
                cidades[num_cidades].pontos_turisticos = atoi(valor);
            }
            else if (strstr(ptr, "\"idh\"")) {
                extrair_valor(ptr, valor);
                cidades[num_cidades].idh = atof(valor);
            }
            else if (strstr(ptr, "}")) {
                // Verificar se a cidade tem nome (válida)
                if (strlen(cidades[num_cidades].nome) > 0) {
                    // Calcular atributos derivados
                    if (cidades[num_cidades].area > 0) {
                        cidades[num_cidades].densidade = (float)cidades[num_cidades].populacao / cidades[num_cidades].area;
                    } else {
                        cidades[num_cidades].densidade = 0;
                    }
                    
                    if (cidades[num_cidades].populacao > 0) {
                        cidades[num_cidades].pib_per_capita = cidades[num_cidades].pib / cidades[num_cidades].populacao;
                    } else {
                        cidades[num_cidades].pib_per_capita = 0;
                    }
                    
                    num_cidades++;
                }
                lendo_cidade = 0;
            }
        }
    }
    
    fclose(file);
    return num_cidades;
}

// Função para exibir uma cidade (usando strings literais UTF-8)
void exibir_cidade(Cidade c) {
    printf("\n=== %s (%s) ===\n", c.nome, c.uf);
    printf("Estado: %s\n", c.estado);
    printf("Região: %s\n", c.regiao);
    printf("População: %lld habitantes\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: R$ %lld\n", c.pib);
    printf("Pontos Turísticos: %d\n", c.pontos_turisticos);
    printf("IDH: %.3f\n", c.idh);
    printf("Densidade Demográfica: %.2f hab/km²\n", c.densidade);
    printf("PIB per capita: R$ %lld\n", c.pib_per_capita);
}

// Função para exibir linha decorativa
void exibir_linha() {
    for(int i = 0; i < 50; i++) {
        printf("=");
    }
    printf("\n");
}

// Função para listar cidades disponíveis
void listar_cidades(Cidade cidades[], int total) {
    printf("\n");
    exibir_linha();
    printf("   CAPITAIS BRASILEIRAS\n");
    exibir_linha();
    printf("Total: %d capitais\n\n", total);
    
    // Listar por região
    char *regioes[] = {"Norte", "Nordeste", "Centro-Oeste", "Sudeste", "Sul"};
    
    for (int r = 0; r < 5; r++) {
        printf("\n%s:\n", regioes[r]);
        printf("------------------------\n");
        
        for (int i = 0; i < total; i++) {
            if (strcmp(cidades[i].regiao, regioes[r]) == 0) {
                printf("%2d. %s (%s)\n", i + 1, cidades[i].nome, cidades[i].uf);
            }
        }
    }
}

// Função para comparar atributos
int comparar_atributos(Cidade c1, Cidade c2, int atributo) {
    switch(atributo) {
        case 1: // População (maior vence)
            return c1.populacao > c2.populacao ? 1 : (c1.populacao < c2.populacao ? -1 : 0);
        case 2: // Área (maior vence)
            return c1.area > c2.area ? 1 : (c1.area < c2.area ? -1 : 0);
        case 3: // PIB (maior vence)
            return c1.pib > c2.pib ? 1 : (c1.pib < c2.pib ? -1 : 0);
        case 4: // Pontos Turísticos (maior vence)
            return c1.pontos_turisticos > c2.pontos_turisticos ? 1 : 
                   (c1.pontos_turisticos < c2.pontos_turisticos ? -1 : 0);
        case 5: // IDH (maior vence)
            return c1.idh > c2.idh ? 1 : (c1.idh < c2.idh ? -1 : 0);
        case 6: // Densidade (menor é melhor)
            return c1.densidade < c2.densidade ? 1 : (c1.densidade > c2.densidade ? -1 : 0);
        case 7: // PIB per capita (maior vence)
            return c1.pib_per_capita > c2.pib_per_capita ? 1 : 
                   (c1.pib_per_capita < c2.pib_per_capita ? -1 : 0);
        default:
            return 0;
    }
}

// Função para limpar o buffer do teclado
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    // Configurar locale para português brasileiro com UTF-8
    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    // Se não funcionar, tente:
    // setlocale(LC_ALL, "Portuguese_Brazil.1252");
    
    Cidade cidades[MAX_CIDADES];
    int total_cidades;
    
    printf("\n");
    exibir_linha();
    printf("   SUPER TRUNFO - CAPITAIS BRASILEIRAS\n");
    exibir_linha();
    
    // Carregar cidades do arquivo JSON
    total_cidades = carregar_cidades("capitais.json", cidades);
    
    if (total_cidades == 0) {
        printf("\nErro ao carregar capitais.\n");
        printf("Verifique se o arquivo 'capitais.json' existe no mesmo diretório.\n");
        return 1;
    }
    
    printf("\nTotal de capitais carregadas: %d\n", total_cidades);
    printf("Arquivo: capitais.json\n");
    
    int continuar = 1;
    
    while (continuar) {
        listar_cidades(cidades, total_cidades);
        
        int escolha1, escolha2, atributo;
        
        printf("\n");
        exibir_linha();
        printf("Escolha a primeira capital (1-%d): ", total_cidades);
        scanf("%d", &escolha1);
        limpar_buffer();
        
        printf("Escolha a segunda capital (1-%d): ", total_cidades);
        scanf("%d", &escolha2);
        limpar_buffer();
        
        if (escolha1 < 1 || escolha1 > total_cidades || 
            escolha2 < 1 || escolha2 > total_cidades) {
            printf("\nEscolha inválida!\n");
            continue;
        }
        
        Cidade c1 = cidades[escolha1 - 1];
        Cidade c2 = cidades[escolha2 - 1];
        
        printf("\n");
        exibir_linha();
        printf("   CONFRONTO: %s (%s) vs %s (%s)\n", 
               c1.nome, c1.uf, c2.nome, c2.uf);
        exibir_linha();
        
        printf("\nEscolha o atributo para comparar:\n");
        printf("1. População (maior vence)\n");
        printf("2. Área (maior vence)\n");
        printf("3. PIB (maior vence)\n");
        printf("4. Pontos Turísticos (maior vence)\n");
        printf("5. IDH (maior vence)\n");
        printf("6. Densidade Demográfica (menor vence)\n");
        printf("7. PIB per capita (maior vence)\n");
        printf("Opção: ");
        scanf("%d", &atributo);
        limpar_buffer();
        
        if (atributo < 1 || atributo > 7) {
            printf("\nAtributo inválido!\n");
            continue;
        }
        
        printf("\n");
        exibir_linha();
        printf("   DETALHES DAS CIDADES\n");
        exibir_linha();
        exibir_cidade(c1);
        exibir_cidade(c2);
        
        int resultado = comparar_atributos(c1, c2, atributo);
        
        printf("\n");
        exibir_linha();
        printf("   RESULTADO DO CONFRONTO\n");
        exibir_linha();
        
        if (resultado > 0) {
            printf("\n   🏆 %s (%s) VENCEU!\n", c1.nome, c1.uf);
        } else if (resultado < 0) {
            printf("\n   🏆 %s (%s) VENCEU!\n", c2.nome, c2.uf);
        } else {
            printf("\n   🤝 EMPATE!\n");
        }
        
        printf("\nDeseja jogar novamente? (1-Sim / 0-Não): ");
        scanf("%d", &continuar);
        limpar_buffer();
    }
    
    printf("\n");
    exibir_linha();
    printf("   Obrigado por jogar Super Trunfo das Capitais!\n");
    exibir_linha();
    printf("\n");
    
    return 0;
}