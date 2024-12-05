#include "BingoCard.h"
#include <iostream>
#include <fstream>
#include <set>
#include <iomanip>
#include <random>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

const std::array<int, 5> limitesInferiores = {1, 16, 31, 46, 61};
const std::array<int, 5> limitesSuperiores = {15, 30, 45, 60, 75};

BingoCard::BingoCard() {
    for (auto &linha : cartela) {
        for (auto &celula : linha) {
            celula = "";
        }
    }
}

void BingoCard::gerarCartela() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::set<int> numerosUsados;

    for (int coluna = 0; coluna < 5; ++coluna) {
        std::uniform_int_distribution<int> dist(limitesInferiores[coluna], limitesSuperiores[coluna]);

        for (int linha = 0; linha < 5; ++linha) {
            if (coluna == 2 && linha == 2) { // Centro é "FREE"
                cartela[linha][coluna] = "FREE";
                continue;
            }

            int numero;
            do {
                numero = dist(rng);
            } while (numerosUsados.count(numero) > 0);

            numerosUsados.insert(numero);
            cartela[linha][coluna] = std::to_string(numero);
        }
    }
}

void BingoCard::exibir() const {
    std::cout << " B    I    N    G    O\n";
    for (const auto &linha : cartela) {
        for (const auto &celula : linha) {
            std::cout << std::setw(4) << celula << " ";
        }
        std::cout << "\n";
    }
}

void BingoCard::marcarNumero(int numero) {
    std::string strNumero = std::to_string(numero);
    for (int linha = 0; linha < 5; ++linha) {
        for (int coluna = 0; coluna < 5; ++coluna) {
            if (linha == 2 && coluna == 2) continue; // Ignorar o FREE
            if (cartela[linha][coluna] == strNumero) {
                cartela[linha][coluna] = "X";
            }
        }
    }
}

bool BingoCard::temLinhaCompleta() const {
    for (const auto &linha : cartela) {
        if (std::all_of(linha.begin(), linha.end(), [](const std::string &celula) { return celula == "X"; })) {
            return true;
        }
    }
    return false;
}

bool BingoCard::temColunaCompleta() const {
    for (int coluna = 0; coluna < 5; ++coluna) {
        bool completa = true;
        for (int linha = 0; linha < 5; ++linha) {
            if (linha == 2 && coluna == 2) continue; // Ignorar o FREE
            if (cartela[linha][coluna] != "X") {
                completa = false;
                break;
            }
        }
        if (completa) return true;
    }
    return false;
}

bool BingoCard::temBingo() const {
    int marcados = 0;

    for (int linha = 0; linha < 5; ++linha) {
        for (int coluna = 0; coluna < 5; ++coluna) {
            if (linha == 2 && coluna == 2) continue; // Ignorar o FREE
            if (cartela[linha][coluna] == "X") ++marcados;
        }
    }

    return marcados == 24; // 24 células preenchidas sem contar o FREE
}

bool BingoCard::estaQuaseCompleta() const {
    int marcados = 0;

    for (int linha = 0; linha < 5; ++linha) {
        for (int coluna = 0; coluna < 5; ++coluna) {
            if (linha == 2 && coluna == 2) continue; // Ignorar o FREE
            if (cartela[linha][coluna] == "X") ++marcados;
        }
    }

    return marcados == 23; // Faltando apenas uma célula para completar
}

void BingoCard::salvarEmArquivo(const std::string &nomeArquivo) const {
    // Criar a pasta ./cartelas, se não existir
    const std::string pasta = "./cartelas";
    if (!fs::exists(pasta)) {
        fs::create_directory(pasta);
    }

    // Caminho completo do arquivo
    std::string caminhoCompleto = pasta + "/" + nomeArquivo;

    std::ofstream arquivo(caminhoCompleto);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao salvar a cartela em arquivo!\n";
        return;
    }

    // Escrever a cartela no arquivo
    arquivo << " B    I    N    G    O\n";
    for (const auto &linha : cartela) {
        for (const auto &celula : linha) {
            arquivo << std::setw(4) << celula << " ";
        }
        arquivo << "\n";
    }

    arquivo.close();
    std::cout << "Cartela salva no arquivo: " << caminhoCompleto << "\n";
}