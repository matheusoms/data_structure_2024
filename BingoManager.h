#ifndef BINGOMANAGER_H
#define BINGOMANAGER_H

#include <list>
#include "BingoCard.h"

class BingoManager {
private:
    std::list<BingoCard*> cartelas;
    std::list<int> numerosChamados;

    void verificarBingo();
    void verificarLinhaEColuna();
    void verificarQuaseCompleta();

public:
    BingoManager();
    ~BingoManager();

    void criarCartelas();
    void exibirCartelas();
    void marcarNumero();
    void exibirNumerosChamados();
};

#endif