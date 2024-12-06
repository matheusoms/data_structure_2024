#include "BingoManager.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <set>

BingoManager::BingoManager() {
    // Inicializa listas de cartelas e números chamados
}

BingoManager::~BingoManager() {
    // Limpar memória alocada para as cartelas
    for (auto &cartela : cartelas) {
        delete cartela;
    }
}

void BingoManager::criarCartelas() {
    int quantidade;
    std::cout << "Quantas cartelas deseja criar? ";
    std::cin >> quantidade;

    // Gerar timestamp para nomes únicos
    auto agora = std::chrono::system_clock::now();
    auto tempo = std::chrono::system_clock::to_time_t(agora);
    std::stringstream timestamp;
    timestamp << std::put_time(std::localtime(&tempo), "%Y%m%d%H%M%S");

    for (int i = 0; i < quantidade; ++i) {
        BingoCard* novaCartela = new BingoCard();
        novaCartela->gerarCartela();
        cartelas.push_back(novaCartela);

        // Nome único para o arquivo da cartela
        std::string nomeArquivo = "cartela_" + timestamp.str() + "_" + std::to_string(i + 1) + ".txt";
        novaCartela->salvarEmArquivo(nomeArquivo);
    }

    std::cout << quantidade << " cartela(s) criada(s) e salvas em arquivos na pasta './cartelas'!\n";
}

void BingoManager::exibirCartelas() {
    if (cartelas.empty()) {
        std::cout << "Nenhuma cartela criada ainda.\n";
        return;
    }

    int index = 1;
    for (auto &cartela : cartelas) {
        std::cout << "\nCartela " << index++ << ":\n";
        cartela->exibir();
    }
}

void BingoManager::marcarNumero() {
    if (cartelas.empty()) {
        std::cout << "Nenhuma cartela criada ainda.\n";
        return;
    }

    int numero;
    std::cout << "Digite o número chamado: ";
    std::cin >> numero;

    numerosChamados.push_back(numero);

    for (auto &cartela : cartelas) {
        cartela->marcarNumero(numero);
    }

    verificarBingo();
    verificarLinhaEColuna();
    verificarQuaseCompleta();
}

void BingoManager::verificarBingo() {
    for (auto &cartela : cartelas) {
        if (cartela->temBingo()) {
            exibirMensagem("BINGO!");
            return; // Retorna ao menu após exibir o BINGO
        }
    }
}

void BingoManager::verificarLinhaEColuna() {
    size_t cartelaIndex = 0; // Índice para rastrear a cartela

    for (auto &cartela : cartelas) {
        // Verificar linhas completas
        for (int linha = 0; linha < 5; ++linha) {
            // Identificar linha única com índice global
            size_t linhaGlobal = cartelaIndex * 5 + linha;

            // Verifica apenas se a linha ainda não foi completada
            if (!linhasCompletas.count(linhaGlobal)) {
                bool linhaCompleta = true;

                // Verificar se a linha está completamente marcada
                for (int coluna = 0; coluna < 5; ++coluna) {
                    if (linha == 2 && coluna == 2) continue; // Ignorar o FREE
                    if (cartela->cartela[linha][coluna] != "X") {
                        linhaCompleta = false;
                        break;
                    }
                }

                if (linhaCompleta) {
                    linhasCompletas.insert(linhaGlobal); // Marca a linha como completa
                    exibirMensagem("LINHA COMPLETA!");
                }
            }
        }

        // Verificar colunas completas
        for (int coluna = 0; coluna < 5; ++coluna) {
            // Identificar coluna única com índice global
            size_t colunaGlobal = cartelaIndex * 5 + coluna;

            // Verifica apenas se a coluna ainda não foi completada
            if (!colunasCompletas.count(colunaGlobal)) {
                bool colunaCompleta = true;

                // Verificar se a coluna está completamente marcada
                for (int linha = 0; linha < 5; ++linha) {
                    if (linha == 2 && coluna == 2) continue; // Ignorar o FREE
                    if (cartela->cartela[linha][coluna] != "X") {
                        colunaCompleta = false;
                        break;
                    }
                }

                if (colunaCompleta) {
                    colunasCompletas.insert(colunaGlobal); // Marca a coluna como completa
                    exibirMensagem("COLUNA COMPLETA!");
                }
            }
        }

        ++cartelaIndex; // Atualiza o índice da cartela
    }
}

void BingoManager::verificarQuaseCompleta() {
    for (auto &cartela : cartelas) {
        if (cartela->estaQuaseCompleta()) {
            exibirMensagem("OLHA A BOA!");
        }
    }
}

void BingoManager::exibirNumerosChamados() {
    if (numerosChamados.empty()) {
        std::cout << "Nenhum número foi chamado ainda.\n";
        return;
    }

    std::cout << "Números chamados: ";
    for (int numero : numerosChamados) {
        std::cout << numero << " ";
    }
    std::cout << "\n";
}

void BingoManager::exibirMensagem(const std::string &mensagem) const {
    std::cout << "------------------------------\n";
    std::cout << "|                            |\n";
    std::cout << "|    " << mensagem << "      |\n";
    std::cout << "|                            |\n";
    std::cout << "------------------------------\n";
}