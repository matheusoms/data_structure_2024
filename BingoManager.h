#ifndef BINGOMANAGER_H
#define BINGOMANAGER_H

#include <list>
#include <set>
#include "BingoCard.h"

class BingoManager {
private:
    std::list<BingoCard*> cartelas;
    std::list<int> numerosChamados;

    // Estados para evitar mensagens duplicadas
    std::set<int> linhasCompletas;
    std::set<int> colunasCompletas;

    void verificarBingo();
    void verificarLinhaEColuna();
    void verificarQuaseCompleta();
    void exibirMensagem(const std::string& mensagem) const;

public:
    BingoManager();
    ~BingoManager();

    void criarCartelas();
    void exibirCartelas();
    void marcarNumero();
    void exibirNumerosChamados();
};

#endif