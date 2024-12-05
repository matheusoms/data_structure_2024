#ifndef BINGOCARD_H
#define BINGOCARD_H

#include <array>
#include <string>

struct BingoCard {
    std::array<std::array<std::string, 5>, 5> cartela;

    BingoCard();
    void gerarCartela();
    void exibir() const;
    void marcarNumero(int numero);
    bool temLinhaCompleta() const;
    bool temColunaCompleta() const;
    bool temBingo() const;
    bool estaQuaseCompleta() const;
    void salvarEmArquivo(const std::string& nomeArquivo) const;
};

#endif