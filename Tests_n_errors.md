# Testes e erros

## Testes

### Teste 1: Leitura de um arquivo de entrada

## Erros

### Erro 1: Abertura de um arquivo inexistente

**Descrição:** Este erro ocorre quando o programa tenta abrir um arquivo que não existe.

**Motivo:** Pode ocorrer, por exemplo, quando o usuário especifica um arquivo que não existe, ou quando o programa tenta abrir um arquivo que não pode acessar.

**Saída:** Arquivo `nome_arq` inexistente.

**Código de retorno:** 1

### Erro 2: Abertura inválida de um arquivo para gravação

**Descrição:** Este erro ocorre quando o programa tenta abrir um arquivo que não pode ser aberto.

**Motivo:** Pode ocorrer, por exemplo, quando o usuário especifica um arquivo que não pode ser aberto, ou quando o programa tenta abrir um arquivo que não pode ser gravado.

**Saída:** Erro ao abrir arquivo `nome_arq`.

**Código de retorno:** 2

### Erro 3: Alocação de memória inválida ou insuficiente

**Descrição:** Este erro ocorre quando o programa fica sem memória disponível para alocar ou tenta alocar em memória inacessível.

**Motivo:** Pode ocorrer, por exemplo, quando o programa tenta alocar grandes quantidades de memória, quando tenta sobreescrever memória que não foi disponibilizada ou quando falta memória na máquina.

**Saída:** Erro ao alocar memória.

**Código de retorno:** 3
