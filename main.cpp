#include <iostream>
#include "BingoManager.h"

void displayMenu() {
    std::cout << "==== Bem-vindo ao Bingo ====\n";
    std::cout << "1. Criar nova(s) cartela(s)\n";
    std::cout << "2. Exibir cartelas\n";
    std::cout << "3. Marcar número\n";
    std::cout << "4. Ver números chamados\n";
    std::cout << "5. Sair\n";
    std::cout << "Escolha uma opção: ";
}

int main() {
    BingoManager manager;
    int opcao;

    do {
        displayMenu();
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                manager.criarCartelas();
                break;
            case 2:
                manager.exibirCartelas();
                break;
            case 3:
                manager.marcarNumero();
                break;
            case 4:
                manager.exibirNumerosChamados();
                break;
            case 5:
                std::cout << "Saindo do programa...\n";
                break;
            default:
                std::cout << "Opção inválida. Tente novamente.\n";
        }
    } while (opcao != 5);

    return 0;
}