# 🔫🎒 Desafio Free Fire — edição personalizada

![C](https://img.shields.io/badge/language-C-0078d7?style=flat-square&logo=c)
![Challenge](https://img.shields.io/badge/challenge-Faculdade%20Est%C3%A1cio%20de%20S%C3%A1-orange?style=flat-square)
![Status](https://img.shields.io/badge/status-WIP-yellow?style=flat-square)
![Fork](https://img.shields.io/badge/fork-yes-blue?style=flat-square)

Este repositório é um fork do desafio utilizada como atividade do curso de **Engenharia de Software** da **Faculdade Estácio de Sá**.

O objetivo é propor exercícios práticos em **C** que evoluem por três níveis de complexidade. A abordagem é incremental: cada nível adiciona conceitos e técnicas que reforçam boas práticas de programação e raciocínio algorítmico.

**Estrutura do repositório**

- `FreeFire.c`: versão base / arquivo principal
- `FreeFire-novato.c`: implementação do nível Novato (inventário básico)
- `FreeFire-aventureiro.c`: implementação com busca sequencial
- `FreeFire-mestre.c`: versão avançada com ordenação e busca binária
- `.gitignore`: regras para ignorar binários e arquivos temporários

**Objetivo do desafio**

Proporcionar uma sequência de pequenos programas em C que permitam:

- Entender e manipular `structs` e arrays
- Praticar entrada/saída via terminal (`scanf`, `printf`)
- Implementar algoritmos de busca e ordenação simples
- Raciocinar sobre complexidade e desempenho de operações básicas

**Como executar**

Compile cada versão com `gcc` e execute o binário gerado. Exemplo:

```bash
gcc -o FreeFire-novato FreeFire-novato.c
./FreeFire-novato

gcc -o FreeFire-aventureiro FreeFire-aventureiro.c
./FreeFire-aventureiro

gcc -o FreeFire-mestre FreeFire-mestre.c
./FreeFire-mestre
```

Se preferir, você pode usar um `Makefile` simples para automatizar a compilação.

**Principais temas estudados neste projeto**

- **Modularização em C**: dividir responsabilidades entre funções e arquivos
- **Estruturas e tipos compostos**: modelar dados com `struct` e `enum`
- **Algoritmos clássicos**: insertion sort, busca sequencial e binária
- **Leitura e validação de entrada**: garantir comportamento previsível
- **Noções de desempenho**: contar comparações e discutir eficiência

## 📚 Análise por Nível — O que foi aprendido e utilizado


**Nível Novato** (`FreeFire-novato.c`):
- **O que faz:** inventário básico com adicionar, remover e listar itens.
- **Principais construções usadas:** `struct` para modelar `Item`; vetor estático para armazenar até `MAX_ITENS`; funções para modularizar comportamento; menu com `switch` e loop `do/while`.
- **I/O e tratamento de strings:** leitura com `fgets` para nomes/tipos e `scanf` para números; uso de `strcspn` para remover `\n`; função `limparBufferEntrada()` para evitar resíduos do `stdin`.
- **Conceitos aprendidos:** modelagem de dados simples, manipulação de arrays estáticos, leitura/validação básica de entrada, remoção por deslocamento de elementos no array.

**Nível Aventureiro** (`FreeFire-aventureiro.c`):
- **O que faz:** adiciona busca sequencial por nome ao inventário; mantém adicionar/remover/listar.
- **Principais construções usadas:** mesma base do Novato (`struct`, vetor estático, menu), mais uma função `buscarItemPorNome()` que percorre a lista sequencialmente (linear search) usando `strcmp`.
- **I/O e UX:** mantém `fgets` + `scanf` e mensagens amigáveis; controle de flags (`encontrado`) para informar resultados.
- **Conceitos aprendidos:** busca sequencial (complexidade O(n)), comparação segura de strings em C (`strcmp`), separação de responsabilidades por função (melhora na legibilidade e testes manuais).

**Nível Mestre** (`FreeFire-mestre.c`):
- **O que faz:** adiciona campo `prioridade`, oferece opções de ordenação por `nome`, `tipo` ou `prioridade` (insertion sort), e busca binária por nome quando a lista está ordenada por nome.
- **Principais construções usadas:** novos campos na `struct` (`prioridade`), `enum` (`CriterioOrdenacao`) para escolher critério, tipo `bool` para controle de estado (`ordenadaPorNome`), `insertionSort()` parametrizado por critério e contador de comparações para análise de desempenho.
- **Busca binária:** `buscarItemPorNome()` valida pré-condição (lista ordenada por nome) e realiza busca binária clássica; conta comparações internas para demonstrar diferenças de desempenho frente à busca sequencial.
- **Conceitos aprendidos:** ordenação estável simples (Insertion Sort) e análise de custo (contagem de comparações); importância de pré-condições para algoritmos (lista ordenada para busca binária); design de APIs internas (passar ponteiros/flags para indicar estado — por exemplo, `bool *ordenadaPorNome`).

**Observações gerais e boas práticas aplicadas em todo o projeto**
- Uso consistente de funções para separar responsabilidades (entrada, exibição, operações sobre o vetor) — facilita testes e manutenção.
- Tratamento de entrada do usuário com `fgets` em vez de `gets` (segurança) e limpeza do buffer para evitar comportamento inesperado.
- Documentação básica nos comentários do código — facilita entender o propósito de cada arquivo.
- Inclusão no `README.md` de instruções de compilação e execução para cada versão.

---

Feito com amor por Wilson Oliveira ❤️
