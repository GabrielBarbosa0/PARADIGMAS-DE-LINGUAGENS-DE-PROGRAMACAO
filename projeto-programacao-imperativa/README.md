# Projeto: Jogo de Adivinhação com CRUD
Linguagens: C e Perl

## Resumo
Programa simples que permite:
- Jogar um jogo de adivinhação (computador escolhe número entre intervalo dado pelo usuário).
- Salvar o resultado em arquivo (`results.txt`).
- Listar resultados salvos.
- Remover registros por id.

## Arquivos
- `guess_crud.c` — implementação em C.
- `guess_crud.pl` — implementação em Perl.
- `results.txt` — arquivo de dados (gerado na execução).
- `README.md` — este documento.

## Como compilar / executar
### C
gcc -o guess_crud guess_crud.c
./guess_crud

### Perl
perl guess_crud.pl

ou

chmod +x guess_crud.pl
./guess_crud.pl

## /////////////////////////////////

## Formato do arquivo de dados
Cada linha: `id|player|min|max|target|attempts|status`
Exemplo: `3|Gabriel|1|10|7|4|ACERTOU`

## Justificativa técnica (avaliação pedida pelo enunciado)
- Linguagens: **C** (estática, compilada) e **Perl** (dinâmica, interpretada). Usei C para demonstrar controle de memória e manipulação direta de arquivos com `stdio`. Usei Perl por ser conciso para manipulação de texto e IO.
- Tipagem: C → estática; Perl → dinâmica.
- Fluxo de controle: O menu principal usa `while` porque o loop deve continuar até o usuário escolher sair; nos laços de tentativa usei `while` também pois o número de iterações não é conhecido.
- Modularização: o código foi dividido em funções (ex.: `play_game`, `list_results`, `remove_result`) para separar responsabilidades, facilitar leitura e manutenção.
- Desempenho: programa é pequeno e I/O-bound; diferença de desempenho é irrelevante neste contexto.
- Segurança/concorrência: implementação simples; Perl tem lock básico ao escrever (flock). Para uso real simultâneo, seria necessário um DB ou locking mais robusto.


