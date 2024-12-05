#include "BingoManager.h"
#include <iostream>

BingoManager::BingoManager() {
    // Construtor para inicializar listas de cartelas e números chamados
}

BingoManager::~BingoManager() {
    // Destruidor para limpar memória alocada
    for (auto &cartela : cartelas) {
        delete cartela; // Deletar cartelas alocadas dinamicamente
    }
}

void BingoManager::criarCartelas() {
    int quantidade;
    std::cout << "Quantas cartelas deseja criar? ";
    std::cin >> quantidade;

    for (int i = 0; i < quantidade; ++i) {
        BingoCard* novaCartela = new BingoCard();
        novaCartela->gerarCartela();
        cartelas.push_back(novaCartela);

        // Salvar cartela em ./cartelas
        std::string nomeArquivo = "cartela_" + std::to_string(cartelas.size()) + ".txt";
        novaCartela->salvarEmArquivo(nomeArquivo);
    }
    std::cout << quantidade << " cartela(s) criada(s) e salvas em arquivos na pasta './cartelas'!\n";
}

void BingoManager::exibirCartelas() {
    if (cartelas.empty()) {
        std::cout << "Nenhuma cartela criada ainda.\n";
        return;
    }

    for (auto &cartela : cartelas) {
        cartela->exibir(); // Usando ponteiro para acessar a cartela
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
        cartela->marcarNumero(numero); // Usando ponteiro para marcar o número
    }

    verificarBingo();
    verificarLinhaEColuna();
    verificarQuaseCompleta();
}

void BingoManager::verificarBingo() {
    for (auto &cartela : cartelas) {
        if (cartela->temBingo()) {
            std::cout << "BINGO!\n";
            return; // Retorna ao menu inicial após detectar o BINGO
        }
    }
}

void BingoManager::verificarLinhaEColuna() {
    for (auto &cartela : cartelas) {
        if (cartela->temLinhaCompleta()) {
            std::cout << "LINHA completa!\n";
        }
        if (cartela->temColunaCompleta()) {
            std::cout << "COLUNA completa!\n";
        }
    }
}

void BingoManager::verificarQuaseCompleta() {
    for (auto &cartela : cartelas) {
        if (cartela->estaQuaseCompleta()) {
            std::cout << "Olha a boa!\n";
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