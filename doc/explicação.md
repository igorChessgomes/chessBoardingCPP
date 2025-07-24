- [Compilação do Projeto](#compilação-do-projeto)
- [Escolhas de Design](#escolhas-de-design)
  - [Boas Práticas](#boas-práticas)
    - [Nomes Descritivos e Claros](#nomes-descritivos-e-claros)
    - [Espaçamento Adequado](#espaçamento-adequado)
    - [Localização de Certos Operadores e Blocos de Código](#localização-de-certos-operadores-e-blocos-de-código)
      - [Blocos](#blocos)
    - [Operadores](#operadores)
    - [Comentários](#comentários)
    - [Indentação](#indentação)
    - [Ordem dos `#include`](#ordem-dos-include)
    - [`#pragma once` vs Include Guards](#pragma-once-vs-include-guards)
    - [Responsabilidade de Código](#responsabilidade-de-código)
    - [Funções e Métodos Pequenos e Objetivos](#funções-e-métodos-pequenos-e-objetivos)
    - [Estrutura de uma Classe Padrão](#estrutura-de-uma-classe-padrão)
    - [Getters e Setters](#getters-e-setters)
    - [Nomenclatura de Membros de Classes](#nomenclatura-de-membros-de-classes)
    - [Otimizações](#otimizações)
      - [Evite Cópias de Objetos](#evite-cópias-de-objetos)
      - [Use `const`](#use-const)
      - [Use `const` em Métodos](#use-const-em-métodos)
      - [Use `noexcept` em funções](#use-noexcept-em-funções)
      - [Sobre `inline`](#sobre-inline)
    - [Princípios SOLID](#princípios-solid)
- [Desconstruindo C++](#desconstruindo-c)
  - [Função ou Método?](#função-ou-método)
  - [Parâmetro ou Argumento?](#parâmetro-ou-argumento)
  - [Definição ou Declaração?](#definição-ou-declaração)
  - [Memória](#memória)
    - [Stack](#stack)
    - [Heap](#heap)
  - [Ponteiros](#ponteiros)
  - [Referências](#referências)
  - [Garbage Collector / Coletor de Lixo](#garbage-collector--coletor-de-lixo)
  - [Excessões](#excessões)
  - [Classes Estáticas](#classes-estáticas)
- [Análise do Código Reformulado](#análise-do-código-reformulado)
  - [src/main.cpp](#srcmaincpp)



Opa, esse arquivo é a explicação da reformularização do código do projeto de xadrez. Vou explicar alguns conceitos que talvez você não conheça e a lógica por trás do design do código.





# Compilação do Projeto

Estou utilizando a ferramente GNU Make, que é basicamente um script de compilação de arquivos C/C++. Compilar arquivos C++ manualmente é meio complicado a medida que o projeto escala, então é uma boa ideia utilizar ferramentas como essa, que automatizam esse processo. Dentro da pasta do projeto, tem um arquivo chamado `Makefile`, que é onde está o script. A maioria das ferramentas e bibliotecas para trabalhar com C++ são feitas exclusivamente para Linux. No caso do Make, tem uma [Versão Para Windows](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download?use_mirror=sinalbr&download), mas eu recomendo mudar pro Linux quando possível. Depois de ter instalado ele, deve ser possível chamá-lo diretamente pela linha de comando (talvez seja necessário editar as variáveis de ambiente pra incluir o caminho da ferramente Make). Note que você precisa ter um compilador C++ já instalado, que suporte a versão C++20 ou maior. Como recomendação e escolha pessoal, lhe sugiro utilizar o [clang](https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.8/clang+llvm-18.1.8-x86_64-pc-windows-msvc.tar.xz). Caso opte por algum outro compilador, você terá que modificar uma pequena parte do arquivo Makefile, nada muito grave. Dentro da pasta do projeto, execute, no terminal, `make debug` ou `make release` para compilar o projeto. Os arquivos de compilação, incluindo o executável, vão para `build/`. Caso queira executar o projeto diretamente pelo terminal, use `make ... RULE=run`.





# Escolhas de Design
## Boas Práticas
### Nomes Descritivos e Claros

O nome de variáveis e qualquer coisa que utilize nomenclatura (incluindo arquivos) no código deve ser em inglês.
No código original, vi que você nomeou algumas variáveis utilizando uma ou duas letras. Para facilitar a leitura do código, é importante nomear variáveis, classes e funções de forma que o próprio nome explique pelo menos um pouco do que a variável, classe ou função faz. Por exemplo:

```C++
Tabuleiro t;

t.inicializar();
t.mostrar();

...
```

Nesse caso não é o fim do mundo porque dá pra ter uma ideia do que `t` é graças ao nome do tipo (outro motivo pra usar nomes explicativos ao nomear classes). Mas e se o tipo não fosse tão legível ou fosse genérico demais? Por exemplo:

``` C++
bool Tabuleiro::movimento(int lo, int co, int ld, int cd)
{
    
    if (co < 0 || co > 7 || lo < 0 || lo > 7
		|| cd < 0 ||cd > 7 || ld < 0 ||ld > 7)
			return false;
	...
}
```

Os parâmetros `lo`, `co`, `ld`, `cd` são do tipo `int`, que significa que são números inteiros. Porém, números inteiros podem ser utilizados para muitas coisas. Então a única forma de saber de forma clara o que significa e para quê são usados esses parâmetros é através de seus nomes. Mas, nesse caso, os nomes são apenas duas letras, o que sugere uma espécie de sigla. Mas que sigla será essa? Ao ver esses parâmetros pela primeira vez, não pude saber claramente o significado desses parâmetros tão descaradamente, o que dificultou a leitura e compreensão da função como um todo. Em projetos reais, muitos programadores trabalham em conjunto para criar alguma coisa. Por isso, é importante que todo o código seja escrito de forma clara, pois se ele for escrito de forma que apenas a pessoa no qual escreveu possa saber o que ele faz, o código se torna um desafio para algum outro programador dentro do time, que não sabe o significado das siglas enigmáticas. Não é que usar siglas é algo proíbido, mas é importante ter cuidado no contexto. Se a sigla for algo muito comum ou global, como `IO`, que praticamente sempre significará "InputOutput", então não haverá problemas. Mas sempre que possível, evite nomes que usem siglas ou apenas uma letra. No caso de nomes com uma letra, há excessões no caso de um loop `for`: Nomear as variáveis do `for` como `i`, `j`, `o`, `k`, `l`, ou alguma coisa do tipo não tem problema.






### Espaçamento Adequado

Por mais que nesse caso seja algo subjetivo e pessoal, eu recomendo adicionar um espaço depois e antes de algum operador, a fim de aumentar a legibilidade. Por exemplo:

Não recomendável:
```C++
int value = (var1+var2)*3.1415/2
bool condition = value>=5&&false!=true
```

Recomendável:
```C++
int value = (var1 + var2) * 3.1415 / 2
bool condition = value >= 5 && false != true
```

O segundo caso tende a deixar o código mais legível. Isso também se enquadra no caso das linhas, embora nesse caso o bom senso seja mais adequado. No geral, sempre adicione uma linha após uma seção de código que tem relação entre si ou que faz parte de uma lógica só:

```C++
// lógica de desinicialização de algum objeto...
board.clear();
board.freeMemory()

// uma linha de espaçamento para separar a lógica
// lógica de mostrar alguma coisa no terminal...
std::cout << "something" << std::endl;
```

Uma linha ou mais (como preferir ou achar melhor) entre declaração/definição de funções e classes. Caso sejam funções que compartilham da mesma lógica ou contexto, não é necessário haver espaço:

```C++
// declaração de funções relacionadas ao estado de inicialização de um sistema...
void startSystem();
void shutdownSystem();
void restartSystem();


// gosto de usar duas linhas, mas pode ser só uma mesmo.
// declaração de funções relacionadas completamente à matemática...
int sum(int a, int b);
int sub(int a, int b);
int mult(int a, int b);
int div(int a, int b);
```

Note que caso seja a definição, não declaração, use, no mínimo, uma linha de espaçamento após o bloco de código:

```C++
int sum(int a, int b)
{
	return a + b;
}

/* uma linha de espaço após o bloco da função anterior.
Caso a próxima função seja algo nada a ver com a lógica da função anterior,
recomendo utilizar mais linhas de espaço (como duas) para separar melhor.*/
int sub(int a, int b)
{
	return a - b;
}
```





### Localização de Certos Operadores e Blocos de Código
#### Blocos

Qual você acha que é certo?:

```C++
if (condition) {
	...
}
```

ou

```C++
if (condition)
{
	...
}
```

A resposta é que depende da linguagem e do gosto pessoal. Algumas linguagens (no caso, a comunidade da linguagem) encorajam o primeiro caso, como Rust e Javascript, enquanto outras preferem o segundo, como C#, Java... Há também as linguagens onde isso tanto faz, que é o caso de C++. Meu gosto pessoal é sempre utilizar o segundo caso em C++. Inclusive, existem algumas linguagens (e C++ entra nessa lista), onde a seguinte sintaxe é possível, caso haja apenas uma linha de código:

```C++
if (condition)
	doSomething();
```

ou

```C++
if (condition) doSomething();
```

Prefiro usar a sintaxe do primeiro caso para evitar a poluição dos delimitadores de bloco (`{` e `}`) caso o bloco em questão tenha apenas uma linha. O segundo caso, onde não há quebra de linha, é possível e também depende do gosto. Note que isso só funciona nas instruções `if`, `else`, `while`, `do-while` e `for` (que eu me lembre).





### Operadores

Outra pergunta, qual você acha o certo?:

`Piece* piece`/`std::string& text`

ou

`Piece *piece`/`std::string &text`

A resposta pra esse caso também é a mesma da de cima: gosto pessoal.
Minha recomendação pessoal é o primeiro caso, pois acho que faz mais sentido. O importante é ser consistente e não variar no estilo.





### Comentários

```C++
// comentário de linha única

/*
Comentário com
mais de uma
linha
*/
```

Comentários servem para literalmente adicionar algum texto explicativo em algum lugar do código. Todo comentário é ignorado pelo compilador e serve apenas para propósitos descritivos e de documentação. Uma vez eu vi uma frase que dizia que todo código deve ser compreensível mesmo sem comentários. Isso significa que, caso vá adicionar um comentário em algum lugar, veja se consegue alterar o próprio código a fim de torná-lo autoexplicativo, como melhorar o nome de uma variável, extrair um trecho de código para uma função, etc. Essa regrinha tem excessões, já que tem alguns casos onde realmente se precisa de comentários para uma melhor compreensão, como é o caso de funções completamente baseadas em matemática.





### Indentação

A indentação é um recurso opcional adotado por praticamente todas as linguagens para organizar melhor blocos de código. Talvez você esteja se perguntando o porquê do "opcional", a verdade é que você pode concluir um projeto inteiro sem nunca clicar no botão `Enter` (e `Tab`) do seu teclado, ou seja, sem quebra de linha. Isso acontece porque o compilador não se importa com os espaços e quebra de linhas que nós, programadores, criamos. Mas isso não vem ao caso. Parece irônico o que vou falar, mas sempre tente evitar a indentação. Muitas vezes, muitos graus de indentação pode deixar o código mais difícil de ler. Não quero dizer que você ira escrever da seguinte forma:

```C++
void myCoolFunction()
{
if (condition)
thisIsMyCoolFunction();
}
```

O que quero dizer, é que caso você tenha algum trecho de código, como dentro do bloco de uma função, que tenha muita indentação, tente simplificar o código de forma que as indentações possam ser diminuídas. Exemplo:

```C++
ServerOperation* sendUserDataToServer(Server& server, const UserData& data)
{
    if (server.CanSendData)
    {
        if (!data.IsUserBlocked)
        {
            ServerOperation* operation = server.SendData(data);

            if (operation->Failed)
                System::log("O bagulho deu ruim mermão.");

            return operation;
        }
    }

    return nullptr;
}
```

O código acima é uma função que, baseando-se no seu nome e no seu conteúdo, parece enviar dados do usuário ao servidor. No entanto, a função não envia nada caso certas condições não sejam atendidas. O trecho acima contém um total de 4 graus de indentação. Isso torna-o um pouco difícil de ler. Refatorando o código para diminuir os graus de indentação, pode-se obter algo mais legível:

```C++
ServerOperation* sendUserDataToServer(Server& server, const UserData& data)
{
    if (!server.CanSendData)
        return nullptr;

    if (data.IsUserBlocked)
        return nullptr;

    ServerOperation* const operation = server.SendData(data);

    if (operation->Failed)
        System::log("O bagulho deu ruim mermão.");

    return operation;
}
```

Essa modificação basicamente inverteu a lógica dos `if`s, de forma que o comportamento da função permaneça o mesmo. Só com isso, pude diminuir o grau de indentação máximo para 2.





### Ordem dos `#include`

Não é uma boa prática organizar os `#include`s de forma aleatória. Siga a seguinte ordem:
1. Headers da linguagem C (`cctype`, `cstring`, `calgumacoisa`...);
2. Headers da linguagem C++ (`string`, `vector`, `map`, `iostream`...);
3. Headers de bibliotecas externas, caso tenha alguma (no caso do nosso projeto, não tem nenhuma);
4. Headers do projeto em si.

Para cada ponto acima, adicione uma linha de espaço e siga a seguinte ordem: Inclua arquivos menos dependentes primeiro, seguido dos mais dependentes. Em outras palavras, inclua arquivos headers mais simples primeiro, depois os mais complexos. Por exemplo:

```C++
#include <ctype>    // declara tipos primitivos C, parece simples
#include <cstring>  // declara funções para mexer com strings em C, um pouco mais complexo
#include <cstdio>   // declara funções de entrada/saída, complexo

#include <string>   // std::string, o mais simples dessa seção
#include <vector>   // std::vector, parece mais complexo que std::string
#include <map>      // std::map, acho que é mais complexo ainda
#include <iostream> // entrada/saída, complexo

// suponha que isso é uma biblioteca externa que fornece funcionalidades
// para criar jogos (biblioteca gráfica)
#include <graphics/system.hpp>  // parece ser o sistema básico, simples
#include <graphics/control.hpp> // parece fornecer controles (teclado, mouse), mais complexo
#include <graphics/audio.hpp>   // audio, acho que é mais complexo que controles
#include <graphics/video.hpp>   // vídeo, mais complexo ainda
#include <graphics/render.hpp>  // lógica de renderizar coisas na tela, simples não é
#include <graphics/window.hpp>  // lógica para mexer com a janela do sistema operacional, complexo

// usando o projeto como referência
#include <chess/position.hpp>   // declara apenas a struct "Position", ultra simples
#include <chess/piece.hpp>      // declara a lógica base das peças, mais complexo
#include <chess/square.hpp>     // casas do tabuleiro, tão complexo quanto as peças
#include <chess/board.hpp>      // o tabuleiro, o mais complexo de todos
```

Analisando a ordem acima melhor, você também pode utilizar a seguinte lógica (mais recomendável):

```C++
// declara a lógica de posicionamento (inclusive no terminal). Todo o projeto vai utilizar essa lógica, então esse header é o menos dependente, já que todo o projeto depende dele. Faz sentido ser o primeiro a ser incluído.
#include <chess/position.hpp>

// declara a lógica base das peças. Incluir antes de "square.hpp", pois uma casa do tabuleiro só faz sentido com uma peça. (embora uma peça também não faça sentido sem uma casa do tabuleiro.)
#include <chess/piece.hpp>
#include <chess/square.hpp>

// é o header mais dependente, pois declara o tabuleiro, que utiliza tanto as peças, casas do tabuleiro e posicionamento. Incluir por último
#include <chess/board.hpp>
```

Utilize o bom senso. Note que, teoricamente, a ordem dos headers incluídos não influencia no comportamento do programa.





### `#pragma once` vs Include Guards

A maioria dos compiladores C++ possui a funcionalidade `#pragma once`, que faz o mesmo trabalho que as include guards: impedir que um arquivo header seja incluído mais de uma vez, o que pode resultar em erros de declaração/definição múltipla. A diferença é que o `#pragma once` é mais limpo:

**pragma_once.hpp**
```C++
#pragma once


class MyClass
{
	...
};
```

**include_guards.hpp**
```C++
#ifndef INCLUDE_GUARDS
#define INCLUDE_GUARDS

class MyClass
{
	...
};

#endif
```

Minha recomendação pessoal é usar o `#pragma once`, mas depende do seu gosto pessoal mesmo.




### Responsabilidade de Código

Toda função e classe deve fazer exatamente o que seu nome sugere, nada mais nada menos. Isso cria código que chamamos de responsável, pois faz apenas o que deve fazer. No código original, você misturou a lógica do tabuleiro com a lógica de printar o tabuleiro na tela na mesma classe. É recomendável separar a lógica de mostrar alguma coisa para o usuário (via terminal ou UI) da lógica do software em si, então eu recomendaria a criação de uma classe separada (não precisa ser necessariamente uma classe) contendo a lógica de printar coisas, como foi feito no código reformulado que será analisado mais adiante.





### Funções e Métodos Pequenos e Objetivos

Evite ao máximos funções muito grandes, sempre tente ver se consegue extrair certo pedaço de código de uma função para outra função, pois isso deixa o código mais claro e legível, além de facilitar a manutenção e alteração. Caso você tenha um pedaço de código que se repete em outro lugar, geralmente é uma ótima ideia extrair tal pedaço de código em uma função. Outra coisa, não ponha lógicas diferentes em uma mesma função. Isso significa que uma função deve fazer apenas uma coisa. Um exemplo:

```C++
void Tabuleiro::mostrar()
{
    std::cout << "  A B C D E F G H" << std::endl;

    for (int i = 0; i < 8; i++)
	{
        std::cout << 8 - i << " ";
        
		for (int j = 0; j < 8; j++)
		{
            char peca = casas[i][j];
            std::string fundo = ((i + j) % 2 == 0) ? "47" : "42";

            if (std::islower(peca))
                std::cout << "\033[35;" << fundo << "m" << peca << " \033[0m";
			else
                std::cout << "\033[31;" << fundo << "m" << peca << " \033[0m";
            
        }

    	std::cout << 8 - i << " ";
    	std::cout << std::endl;
    }

    std::cout << "  A B C D E F G H" << std::endl;
}
```

Pode-se notar que `std::cout << "  A B C D E F G H" << std::endl;` e `std::cout << 8 - i << " ";` são utilizadas duas vezes, no início e fim da função. Para aumentar a legibilidade e reutilizar código, transformar essas linhas em funções é recomendável:

```C++
void Tabuleiro::mostrar()
{
    printBoardLetterGuide();

    for (int i = 0; i < 8; i++)
	{
        std::cout << 8 - i << " ";
        
		for (int j = 0; j < 8; j++)
		{
            char peca = casas[i][j];
            std::string fundo = ((i + j) % 2 == 0) ? "47" : "42";

            if (std::islower(peca))
                std::cout << "\033[35;" << fundo << "m" << peca << " \033[0m";
			else
                std::cout << "\033[31;" << fundo << "m" << peca << " \033[0m";
            
        }

    	std::cout << 8 - i << " ";
    	std::cout << std::endl;
    }

    printBoardLetterGuide();
}

void printBoardLetterGuide() noexcept
{
	std::cout << "  A B C D E F G H" << std::endl;
}

void printBoardNumericGuide() noexcept
{
	std::cout << 8 - i << " ";
}
```

No seguinte trecho de código:

```C++
if (std::islower(peca))
	std::cout << "\033[35;" << fundo << "m" << peca << " \033[0m";
else
	std::cout << "\033[31;" << fundo << "m" << peca << " \033[0m";
```

Percebe-se que as duas linhas que estão após o `if` e `else` são quase idênticas, com uma diferença mínima. Sempre que houver linhas de código idênticos, tente ver se consegue extrair a diferença para alguma variável ou simplificar de alguma forma.

```C++
for (int j = 0; j < 8; j++)
{
	char peca = casas[i][j];
	std::string fundo = ((i + j) % 2 == 0) ? "47" : "42";
	std::string plano = std::islower(peca) ? "\033[35;" : "\033[31;" // extraí para uma variável

	std::cout << plano << fundo << "m" << peca << " \033[0m";
}
``` 

Outro pedaço de código que pode ser extraído para uma função é o loop `for` responsável por printar as colunas do tabuleiro.
Código completo:

```C++
void Tabuleiro::mostrar()
{
	printBoardLetterGuide();

	for (int i = 0; i < 8; i++)
	{
		printBoardNumericGuide();
		printBoardColumns(i);
		printBoardNumericGuide();

		std::cout << std::endl;
	}

    printBoardLetterGuide();
}

void Tabuleiro::printBoardColumns(int currentRowIndex)
{
	for (int j = 0; j < 8; j++)
	{
		char peca = casas[currentRowIndex][j];
		std::string fundo = ((currentRowIndex + j) % 2 == 0) ? "47" : "42";
		std::string plano = std::islower(peca) ? "\033[35;" : "\033[31;"

		std::cout << plano << fundo << "m" << peca << " \033[0m";
	}
}

void Tabuleiro::printBoardLetterGuide()
{
    std::cout << "  A B C D E F G H" << std::endl;
}

void Tabuleiro::printBoardNumericGuide()
{
	std::cout << 8 - i << " ";
}
```

Embora o tamanho total de código tenha aumentado, a função principal que estava sendo refatorada (modificada) ficou bem mais legível.





### Estrutura de uma Classe Padrão

A seguir está a ordem de diferentes items de uma classe. Seguir essa ordem é totalmente opcional e depende do seu gosto. Cada comentário é uma seção; cada seção pode possuir os delimitadores de visibilidade `public`, `protected` ou `private`, que podem ser definidos aonde o programador quiser.

```C++
class MyClass
{
	// propriedades ou constantes estáticas
	// propriedades ou constantes
	// construtores ou destrutores
	// getters
	// setters
	// métodos
	// métodos estáticos
};
```

Exemplo:

```C++
class Circle
{

public:
	// propriedades ou constantes estáticas
	static float pi;


private:
	// propriedades ou constantes
	Position _position;
	Color _color;
	float _radius;


public:
	// construtores ou destrutores
	Ball() = default;
	~Ball() = default;

	
	// getters
	const Position& position() const noexcept;
	const Color& color() const noexcept;
	float radius() const noexcept;

	// setters
	void setPosition(const Position& position) noexcept;
	void setColor(const Color& color) noexcept;
	void setRadius(float radius) noexcept;


	// métodos
	void drawToScreen(Screen* screen) noexcept;

protected:
	void drawToTexture(Texture* texture) noexcept;
	void drawToBuffer(Buffer* buffer) noexcept;


private:
	float calculateAverageResolution() const noexcept;


public:
	float calculateCircunference() const noexcept;


	// métodos estáticos
	static float distanceBetween(const Circle& c1, const Circle& c2) noexcept;
};
```





### Getters e Setters

Geralmente, uma classe possui ao menos uma propriedade que serve para armazenar valores relacionadas à instância da classe. No entanto, é uma boa prática sempre definir as propriedades de uma classe como privadas, limitando seu acesso, que deve ser realizado através de métodos auxiliares chamados de getters e setters. Essa técnica é chamada de encapsulamento (Saiba mais sobre [Encapsulamento](https://en.wikipedia.org/wiki/Encapsulation_(computer_programming))). Um getter é um método público que retorna o valor de uma propriedade não-pública, enquanto um setter é um método que modifica o valor de uma propriedade não-pública. Note que nem toda propriedade não-pública precisa ter um getter ou um setter. As vezes o programador realmente quer que uma propriedade seja totalmente privada ou protegida. Exemplo de uma classe com getters e setters:

```C++
#include <string>


class Account
{
private:
	// propriedades privadas
	std::string _email;
	std::string _password;
	std::string _username;


public:
	...

	// getters
	const std::string& email() const noexcept { return _email; }
	const std::string& password() const noexcept { return _password; }
	const std::string& username() const noexcept { return _username; }

	// setters
	void setEmail(const std::string& email) const noexcept { _email = email; }
	void setPassword(const std::string& password) const noexcept { _password = password; }
	void setUsername(const std::string& username) const noexcept { _username = username; }
};
```

Botei a definição dos getters e setters no mesmo lugar por praticidade, mas o recomendado seria botar em um arquivo fonte mesmo.





### Nomenclatura de Membros de Classes

Propriedades que estiverem no campo `private` de uma classe devem ser prefixadas com `_`. Caso estejam no campo `protected`, prefixe com `m_`. Na pratica, isso não muda absolutamente nada, é só um estilo que eu adotei pra diferenciar facilmente a visibilidade de uma propriedade. Não precisa adotá-lo também, mas seria legal manter a consistência de estilo nesse projeto. Exemplo:

```C++
#pragma once

#include <string>


class Person
{
private:
	int _age;
	std::string _name;


public:

};
```





### Otimizações

C++ é muito popular principalmente no aspecto de perfomance. Por ser uma linguagem que contém funcionalidades de baixo nível, em destaque a administração de memória manual (ao alocar memória, é responsabilidade do programador liberá-la. Ver [Memória](#memória)), a linguagem não possui os chamados "overheads" (sobrecarga no aspecto de desempenho), que seriam causados por técnicas que possibilitam um manuseio automático da memória, como o [Garbage Collector](#garbage-collector--coletor-de-lixo), adotado em muitas outras linguagens de alto nível. Resumindo, C++ é mais rápido que a maioria das outras linguagens no mundo, com certas desvantagens em outros aspectos, claro. No entanto, um código mal-otimizado pode até fazer uma das linguagens mais rápidas atuar como uma tartaruga, por isso é importante saber as boas práticas a respeito de otimizações. C++ possui muitas funcionalidades que podem aumentar o desempenho de um código, além de torná-lo menos propenso a erros:


#### Evite Cópias de Objetos

Aprenda sobre [Ponteiros](#ponteiros) e [Referências](#referências) antes. 

Por padrão, tudo em C++ é copiado após ser atribuído à uma variável. No entanto, a cópia de objetos (principalmente grandes) na memória é lenta e pode se tornar um problema de desempenho em projetos de larga escala. Por isso, sempre que possível, é recomendável evitar a cópia desnecessária de objetos quando for utilizá-los como argumentos de uma função, propriedades de uma classe, etc. Esse problema de cópia pode ser resolvido utilizando uma referência ou um ponteiro, pois ao invés de copiarem o objeto em questão, ambos armazenam seu endereço na memória, com algumas diferenças. Falando de forma simples, ponteiros são mais flexíveis, principalmente por conseguirem ser nulos (`nullptr`), enquanto referências são mais seguras (não podem ser nulas). Sempre que possível, tente optar por usar uma referência ao invés de um ponteiro. Mas há situações onde queremos usar ponteiros graças ao comportamento único deles de poderem ser nulos. Exemplo:

```C++
class Database
{
    // um banco de dados contendo uma quantidade massiva de dados...
};


void printDatabase(Database database)
{
    std::cout << database.toString() << std::endl;
}


int main()
{
    Database database = Database::fromServer("localhost://1234");

    while (database.processing)
    {
        database.process();

        printDatabase(database);
    }

    return 0;
}
```

No código acima, foque-se no trecho `void printDatabase(Database database)`, que declara a função. Lembre-se que tudo em C++ é copiado, então `(Database database)` que é apenas um parâmetro normal, é copiado quando passado como argumento pra função. O código acima também possui um loop que é executado enquanto uma condição não for atingida. Dentro do loop, podemos ver a linha `printDatabase(database);`. Como o tipo do parâmetro não é uma referência ou ponteiro, temos um problema: o objeto `database` é copiado ao ser passado pra função, o que aniquila o desempenho do programa. Para resolver isso, ou use um ponteiro ou uma referência (prefira sempre referências) ao declarar o parâmetro: `void printDatabase(Database& database)`. Note que, mesmo caso o argumento recebido pelo parâmetro seja uma referência, se o parâmetro em si não for também, ele será copiado. Exemplo:

```C++
void doSomething(Object object) { ... }

Object& object = Memory::getRandomObject();

// embora "object" seja uma referência, o parâmetro da função não é, resultando na cópia do objeto mesmo assim.
doSomething(object);
```


#### Use `const`

Em C++, ao declarar variáveis, elas podem, por padrão, serem modificadas quantas vezes quiserem, contanto que o novo valor seja do mesmo tipo. No entanto, existem casos onde temos um valor, mas não queremos modificá-lo. Quando se encontrar em uma situação dessas, use a palavra-chave `const`. Quando o compilador detecta uma variável (ou parâmetro) que tenha sido declarado como `const`, ele consegue **otimizar um pouco o código**, pois a variável em questão não será alterada após sua declaração. Exemplo:

```C++
unsigned int getBytesBeingUsedByDatabase(const Database& database)
{
    unsigned int bytes = 0;

    for (const Item& item : database.items())
        bytes += item.sizeInBytes();

    return bytes;
}
```

Na declaração da função, `unsigned int getBytesBeingUsedByDatabase(const Database& database)`, em `(const Database& database)`, pode-se ver a palavra-chave `const` antes do tipo do parâmetro, pois o código dentro da função não modifica de forma alguma o objeto `database`, logo, ele é constante. Note que também foi utilizado uma referência, para evitar a cópia do objeto. Essa combinação de `const Type& value` é muito comum e utilizada em vários locais em C++. Você irá ver trechos como esse em várias declarações de funções diferentes.


#### Use `const` em Métodos

`const` é tão poderoso e flexível que ele pode ser utilizado até mesmo para definir métodos constantes! Um método constante é aquele que não muda o estado de uma classe, ou seja, ele não altera absolutamente nenhum valor pertencente à classe. Métodos marcados como `const` também são otimizados pelo compilador.

```C++
class App
{
private:
    bool _running;


public:
    void stop() noexcept { _running = false; }


    bool isRunning() const noexcept { return _running; }
};
```

No código acima, perceba que o método `isRunning()` possui o modificador `const`, pois não altera o valor de nada na classe, enquanto `stop()` não pode ser marcado como constante, pois altera a propriedade `_running`. Embora seja estranho, a localização do `const` em métodos é assim mesmo. Ambos os métodos acima possuem o modificador `noexcept`, que você verá agora.

[Saiba mais sobre `const`](https://learn.microsoft.com/pt-br/cpp/cpp/const-cpp?view=msvc-170)


#### Use `noexcept` em funções

A grande maioria das linguagens de programação no mundo possuem uma funcionalidade (ou algo similar) chamada de [Excessão](#excessões). C++ a possui, e elas servem para tratar erros em tempo de execução, alterando o fluxo do programa dependendo de qual erro aconteceu. O `noexcept` indica ao compilador que aquela função não irá lançar excessões, o que permite otimizações por parte do compilador. Como excessões acontecem em tempo de execução, o compilador não sabe se uma função vai ou não lançar excessões em tempo de compilação. Consequentemente, funções marcadas com `noexcept` não são impedidas de lançarem excessões, embora essa funcionalidade não vá funcionar como o esperado...


```C++
void doNoThing() noexcept
{
    return;
}
```

A função acima não lança nenhuma excessão (não tem como uma função que não faz nada lançar uma excessão), então pode ser marcada como `noexcept`.

[Saiba mais sobre `noexcept`](https://learn.microsoft.com/pt-br/cpp/cpp/exception-specifications-throw-cpp?view=msvc-170)


#### Sobre `inline`

`inline` é uma palavra-chave que, ao ser inserida na declaração de uma função, faz uma "sugestão" ao compilador para, ao invés de chamar a função (lento), copiar o código da função no local que for chamada (rápido), o que diminui a sobrecarga de várias chamadas de função.

```C++
inline void sum(const int a, const int b)
{
    return a + b;
}
```

Esse tópico é só uma menção honrosa mesmo, já que esse especificador não precisa mais ser utilizado hoje em dia, pois compiladores modernos são mais inteligentes que programadores no aspecto de otimização de código e sabem quando é uma boa ideia ou não usar `inline` em uma função. [Saiba mais sobre `inline`](https://learn.microsoft.com/pt-br/cpp/cpp/inline-functions-cpp)





### Princípios SOLID

O SOLID é uma lista de princípios para criar código flexível e de fácil manutenção. Trata-se de uma sigla para as seguintes normas:

1. **Single responsibility principle** (é o que eu digo [aqui](#responsabilidade-de-código))
2. **Open–closed principle**
3. **Liskov substitution principle**
4. **Interface segregation principle**
5. **Dependency inversion principle**

Não precisar seguir tudo isso logo agora, mas é uma referência legal no futuro. [Saiba mais a respeito do SOLID](https://en.wikipedia.org/wiki/SOLID)





# Desconstruindo C++
## Função ou Método?

No mundo da programação, geralmente nos referimos a "função" como... uma função. Acredito que você saiba o que é uma função, então não vou me aprofundar. Mas e o que é um método? Um método geralmente se refere à uma função associada à uma classe. Ou seja, se uma função faz parte de uma classe, ela é um método. Todo método é uma função, mas nem toda função é um método.

```C++
class AtomicNuclearBomb
{
public:
    // Isso é um método, pois pertence à uma classe.
    void destroyEverything(); 
};


// Isso é uma função, pois não pertence à uma classe.
HydrogenBomb createHydrogenBomb();
```





## Parâmetro ou Argumento?

Um parâmetro é uma variável declarada na declaração de uma função que serve como a forma da função de receber valores externos. Um argumento é o valor passado na chamada de uma função. Parâmetro é o que recebe o valor, argumento é o valor passado para função:

```C++

// "number" é um parâmetro para receber um argumento.
bool transformNumber(float number)
{
    return number * number % 41876 -(0.1 * 0.2 * 0.3);
}


int main()
{
    // "3.14159" é o valor que está sendo passado para o parâmetro "number", logo, um argumento.
    transformNumber(3.14159);

    return 0;
}
```





## Definição ou Declaração?

C/C++ é uma linguagem única no sentido de usar o sistema de headers (cabeçalhos). Não conheço nenhuma outra linguagem (acredito que Objective-C / Objective-C++ também usa) que forneça esse recurso. Por causa desse sistema, é necessário saber a diferença entre declaração e definição. Declaração é quando você fala pro compilador que existe um identificador (nome), que pode ser uma função, classe, variável, etc..., mas não diz ao compilador o valor ou o que o identificador faz. Definição é quando você fala pro compilador o que o identificador faz ou qual é o seu valor, no caso de uma variável. Geralmente, declarações ficam em arquivos header (`.h` / `.hpp`), enquanto definições das respectivas declarações ficam em arquivos fonte (`.c` / `.cpp`). Exemplo prático:

**coffee.hpp** (header)

```C++
#include <string>


class Coffee
{
private:
	std::string _type;


public:
	Coffee(const std::string& type);

	
	const std::string& type() const noexcept;


	// declaração, só Deus sabe pra que serve essa função, mas pelo menos sabemos que ela existe.
	void drink() noexcept;
};
```


**coffee.cpp** (source)
```C++
#include <coffee.hpp>


Coffee::Coffee(const std::string& type) _type(type)
{}


const std::string& Coffee::type() const noexcept { return _type; }


// definição, fala pro compilador o que a função faz
void Coffee::drink() noexcept
{
	...
}
```





## Memória

Esse assunto é extremamente complexo e amplo, tudo aqui é resumido e simplificado. Nem eu sei completamente todos os detalhes de como a memória funciona por trás dos panos. Caso queira saber mais sobre o assunto que será discutido, recomendo três vídeos de um canal muito bom e especialista em temas envolvendo o baixo nível, embora seja em inglês. O nome do canal é [Core Dumped](https://www.youtube.com/@CoreDumpped), sendo os vídeos em questão: [O Tamanho de Suas Variáveis Importa](https://www.youtube.com/watch?v=hwyRnHA54lI) (introdução), [Por que a Stack é tão Rápida?](https://www.youtube.com/watch?v=N3o5yHYLviQ) (stack), [Por que a Heap é tão Lenta?](https://www.youtube.com/watch?v=ioJkA7Mw2-U) (heap)

Em C++ (e em todas as linguagens de programação), todos os valores criados ou objetos instanciados são armazenados na memória do computador, que é a memória RAM. Toda operação envolvendo alocação e liberação de memória é feita através do sistema operacional. É ele o responsável por alocar a quantiade de memória necessário por cada aplicativo. Sistemas operacionais modernos criam dois locais na memória no qual um valor pode ser armazenado: a **stack** e a **heap**.


### Stack

Assim que um novo aplicativo começar a ser executado, o sistema operacional aloca (separar para utilização) uma certa quantidade de memória que esse aplicativo pode utilizar. Isso é a stack, uma região na memória pre-alocada para armazenar dados do programa em questão.
O termo "stack" significa literalmente "pilha", em inglês. Em programação, stack é uma estrutura de dados que tem duas operações: `push` e `pop`. A operação `push` adiciona um valor no fim da stack, enquanto o `pop` remove um valor do fim da stack. Essa região compartilha de um comportamento semelhante à estrutura de mesmo nome, por isso o nome igual. Em C++, sempre que você cria um valor convencionalmente, esse valor será armazenado na stack. Por exemplo:

```C++
int number = 10;        // armazenado na stack
char character = 'x';   // também armazenado na stack
```

Algumas estruturas de dados como `std::vector` e tipos não-primitivos como `std::string` não usam a stack, optando por outra região na memória mais flexível, que será explicada mais a frente.
A stack é rápida, porque sua funcionalidade é simples e seu tamanho não muda, o que a torna uma ótima escolha na maioria dos casos. No entanto, como dito anteriormente, a stack é pre-alocada pelo sistema operacional, significando que seu tamanho não muda após o início de um programa. Levando isso em conta e a lógica por trás da stack, a criação de estrutura de dados que possam mudar de tamanho (como `std::vector`) se torna impossível. É por isso que você precisa especificar o tamanho de um array em C, pois como valores na stack não podem mudar de tamanho, é necessário que se saiba o tamanho máximo do array. Só que em muitos casos, é necessário o armazenamento de vários dados de forma dinâmica e flexível. É por esse, e outros motivos, que objetos como `std::vector`, `std::map` e `std::string`, ambos compartilhando a característica de alterar seu tamanho, utilizam um outro local na memória, a Heap, que será analisada daqui a pouco.
Uma outra razão pra usar a heap, é que, em C++, valores alocados na stack são removidos dela logo após saírem de seu escopo de declaração. Isso significa que, caso você queira que um determinado valor ou objeto continue "vivo" após sair do escopo, você precisará alocá-lo na heap, onde essa limitação de escopo não existe.


```C++
// escopo principal

int outer = 10;

{
    // escopo interno

    int inner = 123;

    // variável "number2" é removida da stack no final do escopo em que ela foi declarada.
}

// "outer" ainda existe pois seu escopo ainda não chegou ao fim. No entanto, "inner" já foi removida da stack e não pode ser mais acessada. O compilador detecta os limites de escopo de um identificador e gera um erro de compilação, nesse caso.

std::cout << outer * inner << std::endl;
```


### Heap

Heap, traduzindo literalmente, "montão", no sentido de montante; aglomerado. É um local na memória que, contrário à stack, pode mudar de tamanho de acordo com as necessidades. No entanto, essa capacidade de alteração no tamanho faz com que o sistema operacional tenha que alocar novos blocos de memória em tempo de real toda vez que a heap não possuir mais espaço para armazenar os dados atuais, causando uma perda no desempenho geral do programa. Ao contrário da stack, no geral, a heap é um pouco mais lenta. Em C++, você pode alocar coisas na heap utilizando a palavra-chave `new`:

```C++
int* myPointerToANumber = new int(10);
```

Valores alocados na heap precisam ser acessador via um ponteiro, por isso o `*` após o tipo. Essa linha diz ao sistema operacional para alocarmos na heap a quantidade de memória necessária para guardar um inteiro, cujo valor é 10. Um valor alocado na heap permanecerá pra sempre na memória, a menos que o software que o alocou seja fechado ou a menos que nós ordenemos ao sistema para liberá-la. Essa limitação e responsabilidade faz com que alguns problemas surjam:

```C++
class Shape { ... };


int main()
{
    while (true)
        Shape* shape = new Shape();

    return 0;
}
```

O código acima contém um loop que aloca, infinitamente, objetos do tipo `Shape` na heap. Se o estivéssemos alocando na stack, o código acima seria apenas um loop inútil, pois o valor alocado seria liberado logo após sair do seu escopo, que é o bloco do loop `while`. No entanto, como o estamos alocando na heap, mesmo que o ponteiro que aponta para o local dele na heap saia do escopo e seja liberado da stack, o valor em si continuará na heap, ocupando espaço real da memória de forma inútil. Isso significa que esse código ira executar enquanto houve memória RAM livre. Parábens, você acabou de criar um vírus que suga toda a memória do computador. Fácil, não?

A menos que você queira seu projeto alocando memória indefinidamente, é necessário liberar a memória alocada na heap sempre que não for mais utilizá-la. Para fazer isso, você precisa utilizar a palavra-chave `delete`:

```C++
class Shape { ... };


int main()
{
    while (true)
    {
        Shape* shape = new Shape();
        delete shape;
    }

    return 0;
}

```

Agora, o código acima volta a ser apenas inútil, pois aloca memória e a libera logo após.


## Ponteiros

Ponteiros são, basicamente, variáveis que armazenam um local na memória para outro valor. Por isso o nome "ponteiro", pois "aponta" para outro local na memória. Ponteiros são muito importantes em C++ por três motivos:

- São a única forma de acessar valores na [Heap](#heap).
- Certa parte do polimorfismo (orientação a objetos) precisa de ponteiros para funcionar corretamente.
- Em C++, sempre que você atribui uma variável um valor, o mesmo valor será copiado, o que significa que não é o mesmo valor atribuido.

Exemplo:

```C++
struct Person
{
    std::string name;
    unsigned int age;
}


int main()
{
    Person peter { .name = "peter", .age = 23 };
    Person peterCopy = peter; // cópia

    // ponteiro que aponta para o endereço na memória onde "peter" está localizado
    Person* ptrPeter = &peter;

    std::cout << peter.name << std::endl; // -> peter
    std::cout << peterCopy.name << std::endl; // -> peter

    // por apontar pro mesmo lugar na memória que o objeto original, modificações feitas através no ponteiro são refletidas no objeto real.

    ptrPeter->name = "another peter";

    std::cout << peter.name << std::endl; // -> another peter
    std::cout << peterCopy.name << std::endl; // -> peter

    // ponteiros podem ser nulos!
    ptrPeter = nullptr;
    
    
    return 0;
}
```

O operador `*` após o tipo indica que o tipo é um ponteiro. O operador `&` antes de um valor retorna seu endereço na memória. Para acessar membros de um ponteiro, utilize `->` ao invés de `.`.

[Saiba mais sobre Ponteiros](https://learn.microsoft.com/pt-br/cpp/cpp/raw-pointers?view=msvc-170)





## Referências

Referências são muito similares à [Ponteiros](#ponteiros). Com a diferença que referências nunca podem ser nulas, nem podem mudar sua referência original após uma vez declarada. Exemplo:

```C++
int main()
{
    std::string bestLanguage = "C++";

    std::string bestLanguageCopy = bestLanguage;
    std::string& bestLanguageReference = bestLanguage;

    // Por ser uma cópia, não afeta o objeto original
    bestLanguageCopy = "C#";

    std::cout << bestLanguage << std::endl; // -> C++

    // É uma referência, então afeta o objeto original.
    // Note que mesmo utilizando o operador de atribuição "=", a referência mudou o valor do objeto original em vez de mudar o objeto que se deve referenciar.
    bestLanguageReference = "Rust";

    std::cout << bestLanguage << std::endl; // -> Rust

    // isso irá gerar um erro de compilação.
    int& genericReference = nullptr;


    return 0;
}
```

O operador `&` após um tipo (não confunda com `&` antes de um valor, que retorna seu endereço na memória) indica que o tipo é uma referência. Como mostrado no código acima, referências não podem mudar sua referência original após a declaração.

[Saiba mais sobre Referências](https://learn.microsoft.com/pt-br/cpp/cpp/references-cpp?view=msvc-170)





## Garbage Collector / Coletor de Lixo

Garbage Collector, ou Coletor de Lixo, em inglês, é uma técnica e ferramenta presente na maioria das linguagens de programação (com excessão de C/C++ e outras). Seu propósito é remover a necessidade de manualmente ter que liberar a memória alocada na [Heap](#heap), resolvendo alguns problemas envolvidos à essa responsabilidade. Infelizmente, linguagens que implementam um Garbage Collector pagam um preço: Desempenho, que é sacrificado em troco de praticidade. Isso acontece porque um Garbage Collector procura por valores na heap que não estão sendo utilizados a todo momento, o que diminui a perfomance de um programa. [Saiba mais sobre Garbage Collectors](https://en.wikipedia.org/wiki/Garbage_collection_(computer_science))





## Excessões

Ainda não botei nada aqui.





## Classes Estáticas

Classes estáticas são classes que não podem ser instanciadas. Seus valores e métodos são acessados diretamente pelo tipo. Esse tipo de classe é muito utilizada para configurações globais. Note que um membro tamném pode ser estático em uma classe convencional. Exemplo:

```C++
class Settings
{
	// para criar uma classe estática, remova todos os construtores e delete o construtor padrão.
	Settings() = delete;

	
	// todos os membros precisam ser definidos fora do header, em um arquivo fonte.
	// todos os membros precisam ter o modificador `static`

	static bool enablePremove;
	static int maxPremoves;


	static void toDefaultSettings() noexcept;
};
```





# Análise do Código Reformulado

A seguir, analisarei o código novo que reformulei baseado no seu original. Fiz isso principalmente pra criar esse arquivo de explicação, no qual tenho como objetivo lhe ensinar tanto alguns conceitos da própria linguagem C++ quanto alguns padrões e recomendações de design e código limpo. Irei fornecer links de documentação caso você queira saber mais sobre alguma funcionalidade em específica, as informações aqui serão resumidas. O site de minha escolha de documentação será o da Microsoft, e caso você não consiga entender muito bem com base na descrição deles (concordo que é meio complexo), utilizar o ChatGPT ou perguntar pra mim mesmo é uma boa ideia.





## src/main.cpp

```C++
#include <chess/board.hpp>
#include <terminal/renderer.hpp>

#include <iostream>


int main()
{
    Board board;
    BoardRenderer renderer(board, ColorPalette::defaultTheme());

    std::cout << renderer.render() << std::endl;

    return 0;
}
```

Esse é o arquivo principal, que contém a função principal que é chamada ao rodar o projeto. Dentro da função `main`, eu instancio dois objetos: `Board board` e `BoardRenderer renderer`. Aplicando o conceito de responsabilidade de código, não posso botar a lógica de printar coisas no terminal na classe `Board`, que deve ser utilizada exclusivamente para a lógica do tabuleiro em si. Por isso as duas classes, `Board`, que é o tabuleiro, e `BoardRenderer`, que contém a lógica que printa o tabuleiro no terminal. Na inicialização do mesmo: `BoardRenderer renderer(board, ColorPalette::defaultTheme());`, temos a parte `(board, ColorPalette::defaultTheme())`. Perceba `ColorPalette::defaultTheme()`: Seria interessante criar a funcionalidade de diversos temas de cores para o tabuleiro e peças, então criei essa [Classe Estática](#classes-estaticas), que contém a cor para as casas e peças. No seu código original, vi que utilizou um método `Tabuleiro::inicializar()` para inicializar o tabuleiro, sendo que você poderia ter utilizado o construtor da classe, que é a maneira mais adequada e recomendada para inicializar alguma coisa relacionada ao objeto. O construtor é, em sua base, uma função, que é chamada no momento em que um novo objeto da classe é instanciado (criado). Você pode também declarar parâmetros no construtor para receber valores que podem ser utilizados para alguma coisa. [Saiba Mais Sobre Construtores](https://learn.microsoft.com/pt-br/cpp/cpp/constructors-cpp?view=msvc-170). A linha `std::cout << renderer.render() << std::endl;` printa todo o tabuleiro no terminal, utilizando o tema atual de cores.