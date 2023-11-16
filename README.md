# minishell

Este é um projeto bastante abrangente e desafiador! Quebrei os requisitos do projeto em passos menores para ter uma visão do macro.

#### 1. Exibir um Prompt e Histórico de Trabalho

 \- **Prompt:** usar a função `readline()` da sua biblioteca para exibir um prompt e ler a entrada do usuário. 

\- **Histórico:** A `readline()` também gerencia um histórico. Usar `add_history()` para adicionar comandos ao histórico.

#### 2. Executar Comandos

 \- **Procurar Executáveis:** Usar a variável de ambiente `PATH` para encontrar executáveis. A função `execve()` pode ser útil aqui.

\- **Caminhos Relativos ou Absolutos:** Tratar entradas que começam com `./` ou `/` como caminhos relativos ou absolutos.

####  3. Manipulação de Sinais

 \- **Variável Global para Sinais:** Definir uma variável global para capturar sinais. Usar funções como `signal()` ou `sigaction()` para manipular sinais.

####  4. Aspas e Caracteres Especiais

 \- **Aspas Simples e Duplas:** Implementar uma lógica para tratar strings entre aspas, prestando atenção em como os caracteres são interpretados.

\- **Redirecionamentos e Pipes:** Implementar a lógica para `<`, `>`, `<<`, `>>`, e `|`. Usar funções como `pipe()`, `dup()` ou `dup2()` para manipulação de pipes e redirecionamentos de arquivos.

####  5. Variáveis de Ambiente e Expansão

 \- **Expansão de Variáveis:** Implementar a expansão de variáveis de ambiente quando encontrar `$`.

\- **Status de Saída:** Usar a variável `?` para armazenar o status de saída do último comando executado.

####  6. Manipulação de ctrl-C, ctrl-D, e ctrl-\

 \- **Comportamento dos Controles:** Implementar manipuladores para esses casos, provavelmente usando a manipulação de sinais.

####  7. Builtins

 \- Implementar os builtins especificados (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`). Cada um deles requer uma abordagem específica.

####  8. Parte do Bônus

 \- **Operadores Lógicos e Parênteses:** Implementar a lógica para `&&`, `||`, e o uso de parênteses.

\- **Caracteres Curinga:** Implementar a lógica para tratar o asterisco `*` para expansão de nomes de arquivos no diretório atual.
