#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

class ContaBanco {
private:
    float saldo;
    bool status;
    std::string dono;
    std::string tipo;
    std::vector<int> numConta; // agora é atributo da classe

public:
    // Construtor
    ContaBanco(std::string nome, std::string tipo) {
        this->dono = nome;
        this->tipo = tipo;
        this->saldo = 0;
        this->status = false;
    }

    // Destrutor
    ~ContaBanco() {}

    // Getters e Setters
    std::string getTitular() {
        return this->dono;
    }

    void setTitular(std::string nome) {
        this->dono = nome;
    }

    std::string getTipo() {
        return this->tipo;
    }

    void setTipo(std::string tipo) {
        this->tipo = tipo;
    }

    bool getStatus() {
        return this->status;
    }

    void setStatus(bool status) {
        status = true;
        this->status = status;
    }

    float getSaldo() {
        return this->saldo;
    }

    void setSaldo(float saldo) {
        this->saldo = saldo;
    }

    // Gerar número da conta (6 dígitos)
    void gerarNumConta() {
        numConta.clear(); // limpa vetor
        std::mt19937 gerador(static_cast<unsigned int>(std::time(0)));
        std::uniform_int_distribution<int> dist(0, 9);

        for (int i = 0; i < 6; i++) {
            numConta.push_back(dist(gerador));
        }
    }

    std::vector<int> getNumConta() {
        return this->numConta;
    }

    // Mostrar informações
    void exibirInfo() {
        std::cout << "Titular: " << this->dono << std::endl;
        std::cout << "Tipo: " << this->tipo << std::endl;
        std::cout << "Saldo: " << this->saldo << std::endl;
        std::cout << "Status: " << (status ? "Ativa" : "Inativa") << std::endl;
        std::cout << "Numero da Conta: ";
        for (int digito : numConta) {
            std::cout << digito;
        }
        std::cout << std::endl;
    }

    void fecharConta(){
        if(this->saldo != 0){
            std::cout << "\nERRO: A conta deve estar zerada para poder ser encerrada\n" << std::endl;
        }else{
            std::cout << "\nConta fechada com sucesso!\n" << std::endl;
        }
    }
    
    void depositar(){
        float valor;

        if(this->status == false){
            std::cout << "\nERRO: Para depositar você deve ter uma conta ativa\n" << std::endl;
        }else{
            std::cout << "Saldo atual: " << this->saldo << "\nQuanto deseja depositar: " << std::endl;
            std::cin >> valor;

            this -> saldo += valor;
            std::cout << "\nDepósito realizado com sucesso!\n" << "Saldo atual: " << this->saldo << std::endl;
        }
    }

    void sacar(){
        float valor;

        if(this->saldo == 0){
            std::cout << "\nERRO: conta zerada\n" << std::endl;
        }

        do{
            std::cout << "Saldo atual: " << this->saldo << "\nQuanto deseja sacar: " << std::endl;
            std::cin >> valor;

            if(valor > this->saldo){
                std::cout << "\nERRO: Valor maior que o seu saldo atual\n" << std::endl;
            }

            if(valor > this->saldo){
                std::cout << "\nERRO: Saldo insuficiente!\nSaque uma quantidade menor ou igual que o seu saldo atual\n" << std::endl;
            }
        }while(valor > this->saldo);

        this-> saldo = this->saldo - valor;

        std::cout << "\nSaque realizado com sucesso!\n" << "Saldo atual: " << this->saldo << std::endl;
    }

    void pagarMensal(){
        float mensalidade;

        if(this->tipo == "CP"){
            std::cout << "A mensalidade do tipo CP é de R$ 20,00" << std::endl;
            mensalidade = 20;

            if(this->saldo < mensalidade){
                std::cout << "\nERRO: Saldo insuficiente para pagar a mensalidade\n" << std::endl;
                exit(1);
            }

            this->saldo = saldo - mensalidade;
            std::cout << "\nPagamento realizado com sucesso!\n" << "Saldo atual: " << this->saldo << std::endl;

        }else{
            std::cout << "A mensalidade do tipo CC é de R$ 12,00" << std::endl;
            mensalidade = 12;

            if(this->saldo < mensalidade){
                std::cout << "\nERRO: Saldo insuficiente para pagar a mensalidade\n" << std::endl;
                exit(1);
            }

            this->saldo = saldo - mensalidade;
            std::cout << "\nPagamento realizado com sucesso!\n" << "Saldo atual: " << this->saldo << std::endl;

        }
    }
};

int main() {
    std::string nome;
    std::string tipo;
    int opcao;

    std::cout << "Digite o nome do titular: ";
    std::getline(std::cin, nome); // permite espaços no nome

    do{
        std::cout << "Digite o tipo da conta (CC para corrente, CP para poupanca): ";
        std::cin >> tipo;
    }while(tipo != "CC" && tipo != "CP");
    
    // Cria a conta com os dados do usuário
    ContaBanco conta(nome, tipo);
    conta.setStatus(true);
    conta.gerarNumConta();
    
        if(tipo == "CP"){
            conta.setSaldo(50);
        }else{
            conta.setSaldo(150);
        }


    std::cout << std::endl << "=== Dados da Conta ===" << std::endl;
    conta.exibirInfo();

    do{
        std::cout << "\n---OPÇÕES---\n" << "1- Fechar conta\n" << "2- Depositar\n" << "3- Sacar\n" << "4- Pagar mensal\n" << "5- Sair" << std::endl;
        std::cin >> opcao;

        switch (opcao)
        {
        case 1:
            conta.fecharConta();
            break;
        
        case 2:
            conta.depositar();
            break;

        case 3:
            conta.sacar();
            break;

        case 4:
            conta.pagarMensal();
            break;
        
        case 5:
            std::cout << "Saindo ..." << std::endl;
        default:
            break;
        }
    }while(opcao != 5);

    return 0;
}
