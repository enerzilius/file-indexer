# file-indexer

## Como funciona?

Este é um aplicativo simples de linha de comando que simula um mecanismo de busca em arquivos de texto. Ele lê os arquivos, constrói um índice invertido e o salva em um arquivo. Depois disso, é possível buscar palavras-chave, retornando uma lista de documentos que contêm o termo pesquisado.

## Construindo e executando

* Execute (no Linux):

```bash
$ make && ./main
```

* Isso colocará você dentro da interface de linha de comando (CLI) do aplicativo. Você poderá então executar os comandos desejados:

```bash
>> indice construir <caminho_do_diretorio>  # Processa os arquivos dentro do diretório especificado, constrói o índice invertido e o salva como index.dat  
>> indice buscar <termo_de_busca>          # Se existir um arquivo `index.dat` no diretório, ele é carregado e imprime os arquivos relevantes
```

* Use `ctrl+c` para sair do programa.
