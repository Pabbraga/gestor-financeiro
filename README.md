# Gestor Financeiro
Gerenciador simples de transferências financeiras feito em C, operado via terminal. Desenvolvido para praticar conceitos de listas encadeadas na disciplina de Estruturas de Dados.

## Objetivo
- Praticar manipulação de listas encadeadas em C.
- Exercitar modularização e boas práticas.

## Funcionalidades
- **Inserir transação:** Cadastra uma nova transferência (descrição, valor e tipo).
- **Atualizar transação:** Altera dados de uma transferência existente pelo ID.
- **Remover transação:** Exclui uma transferência do histórico, com confirmação.
- **Buscar transação:** Consulta detalhes de uma transferência pelo ID.
- **Mostrar todas as transações:** Lista todas as transferências cadastradas e balanço atual.

## Instalação
Para instalar, basta clonar o repositório ou baixar o arquivo ZIP.
```bash
git clone git@github.com:Pabbraga/gestor-financeiro.git
cd gestor-financeiro
```
## Windows
Você precisará baixar um compilador próprio, IDEs compatíveis com C são uma boa escolha.

Ao abrir a pasta do projeto, basta compilar e executar.
## Linux
1. Instalar compilador:
```bash
apt install gcc
```
2. Compile o projeto:
```bash
gcc main.c -o gestor-financeiro
```
3. Execute:
```bash
./gestor-financeiro
```

## Observações
- Todo o controle é feito via terminal.
- Código modularizado, fácil de expandir.
- Projeto acadêmico, sem persistência de dados.