# 📘 Paradigmas de Linguagens de Programação

Repositório dedicado às atividades, exercícios e projetos desenvolvidos na disciplina **Paradigmas de Linguagens de Programação**.  
Aqui serão incluídos códigos, relatórios e materiais de estudo relacionados aos diferentes paradigmas trabalhados em aula.

---

## 📂 Estrutura do Repositório
- `C/` → Projetos e exercícios implementados em **C**  
- `Perl/` → Projetos e exercícios implementados em **Perl**  
- `Docs/` → Relatórios, anotações e materiais auxiliares  

---

## 🧑‍🏫 Sobre a Disciplina
A disciplina de **Paradigmas de Linguagens de Programação** tem como objetivo estudar os principais estilos de programação, entendendo seus conceitos, vantagens, desvantagens e aplicabilidades.  

### 🔑 Conteúdos abordados:
- Programação Imperativa  
- Programação Funcional  
- Programação Lógica  
- Comparação entre paradigmas  


---

## 🛠️ Tecnologias Utilizadas
- [C](https://en.wikipedia.org/wiki/C_(programming_language))  
- [Perl](https://www.perl.org/)  


# Projeto de Paradigmas - CRUD + Jogo de Adivinhação

## 📌 Descrição
Este projeto implementa um **jogo de adivinhação** em duas linguagens (**C e Perl**), conforme solicitado na disciplina de **Paradigmas de Linguagens de Programação**.  
O usuário informa um intervalo (ex: 1 a 10), o computador sorteia um número e o jogador tenta adivinhar.  
Cada resultado é salvo em arquivo, permitindo **CRUD (Create, Read, Delete)** simples sobre os registros.

---

## ✅ Requisitos atendidos
- [x] Uso de **duas linguagens diferentes** (C e Perl).  
- [x] Implementação de **CRUD**:  
  - **Create** → salvar resultado ao fim de cada jogo.  
  - **Read** → listar resultados.  
  - **Delete** → remover resultado por ID.  
- [x] **Jogo de adivinhação** com sorteio no intervalo definido pelo usuário.  
- [x] **Armazenamento em lista** (arquivo `results.txt`).  
- [x] **Documentação e justificativas** (este README).  
- [x] Código simples e funcional, sem dependências externas.  

---

## 🔀 Principais diferenças entre C e Perl
| Aspecto          | C | Perl |
|------------------|---|------|
| **Execução**     | Compilada | Interpretada |
| **Tipagem**      | Estática, forte | Dinâmica, fraca |
| **Paradigma**    | Imperativo/procedural | Multiparadigma |
| **Controle**     | Baixo nível (memória, ponteiros) | Alto nível (manipulação de strings, I/O) |
| **Foco**         | Performance, controle detalhado | Produtividade, manipulação de texto |
| **Abstração**    | Menor (mais código para IO) | Maior (IO mais simples) |
| **Portabilidade**| Requer compilação por plataforma | Executa direto com interpretador |

---

## 🔧 Justificativa de Fluxo de Controle
- Foi escolhido **`while`/`loop infinito com break`** para o menu, pois o número de repetições é indefinido até o usuário sair.  
- No jogo, foi usado **loop `while`** porque não sabemos quantas tentativas serão necessárias até acertar.  
- Estruturas condicionais (`if/else`) foram usadas para comparar o palpite com o número sorteado.  

---

## 📚 Modularização e Legibilidade
- O código em **C** foi dividido em funções (`play_game`, `list_results`, `remove_result`, etc.) para separar responsabilidades.  
- O código em **Perl** foi organizado em **sub-rotinas** para manter legibilidade.  
- Isso melhora a **clareza**, facilita manutenção e evita repetição de código.  

---

## 📖 Regras sobre Bibliotecas
- **C:** foram usadas apenas bibliotecas padrão (`stdio.h`, `stdlib.h`, `string.h`, `time.h`). Nenhuma biblioteca externa foi utilizada, garantindo portabilidade.  
- **Perl:** foram usados apenas módulos embutidos (`strict`, `warnings`, `Fcntl` para lock de arquivo). Nenhum módulo externo foi necessário.  
- **Motivo:** O professor pediu que não fossem usadas bibliotecas que resolvam automaticamente o problema (como libs prontas para CRUD). A ideia era implementar de forma simples e didática.  

---


## 👨‍💻 Autor
**Gabriel Gomes Barbosa**  
- 🎓 Estudante de Bacharelado em Sistemas de Informação – UPE  
- 🔗 [LinkedIn](https://www.linkedin.com/in/gabriel-barbosa02)  
- 💻 [GitHub](https://github.com/GabrielBarbosa0)  

---
📅 *Repositório criado para fins acadêmicos na disciplina de Paradigmas de Linguagens de Programação.*