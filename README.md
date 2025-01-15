# Grafo em C++

Este é um pequeno projeto meu de alguns anos atrás, em C++, que fiz enquanto estudava sobre grafos.

Basicamente, ele implementa o grafo não direcionado da figura abaixo, realiza a visitação (busca)
dos nodos por largura (BFS) e profundidade (DFS), lista os componentes do grafo e seus vértices
e aplica o algoritmo do Caminho Mínimo (ou simplesmente &ldquo;algoritmo de Dijkstra&rdquo;).

![Grafo não-direcionado](https://raw.githubusercontent.com/rddevitte/grafo-cpp/master/graph.svg)

## Compilação

Assumindo que você já tenha instalado o CMake versão 3.16 ou a mais recente, execute o *script*
`./build`.

## Executar

Após compilado, execute `./_build/grafo-cpp`.

## Limpeza

Apenas execute `rm -r _build`.

## Compilação e execução (Docker)

Assumindo que tenha instalado a *engine* do Docker localmente, basta executar o *script*
`./docker-build-and-run`.
