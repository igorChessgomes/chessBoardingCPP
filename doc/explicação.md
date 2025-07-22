- [Compilação do Projeto](#compilação-do-projeto)
- [Escolhas de Design](#escolhas-de-design)
  - [Definição vs Declaração](#definição-vs-declaração)
  - [`#pragma once`](#pragma-once)
  - [Boas Práticas](#boas-práticas)
    - [Nomes Descritivos e Claros](#nomes-descritivos-e-claros)
    - [Espaçamento Adequado](#espaçamento-adequado)
    - [Localização de Certos Operadores e Blocos de Código](#localização-de-certos-operadores-e-blocos-de-código)
      - [Blocos](#blocos)
      - [Operadores](#operadores)
    - [Comentários](#comentários)
    - [Indentação](#indentação)
    - [Responsabilidade de Código](#responsabilidade-de-código)
    - [Funções e Métodos Pequenos e Objetivos](#funções-e-métodos-pequenos-e-objetivos)
    - [Estrutura de uma Classe Padrão](#estrutura-de-uma-classe-padrão)
    - [Getters e Setters](#getters-e-setters)
    - [Nomenclatura de Membros de Classes](#nomenclatura-de-membros-de-classes)
- [Análise do Código Reformulado](#análise-do-código-reformulado)
  - [src/main.cpp](#srcmaincpp)
- [Notas](#notas)
  - [Classes Estáticas](#classes-estáticas)



Opa, esse arquivo é a explicação da reformularização do código do projeto de xadrez. Vou explicar alguns conceitos que talvez você não conheça e a lógica por trás do design do código.


## Compilação do Projeto

Estou utilizando a ferramente GNU Make, que é basicamente um script de compilação de arquivos C/C++. Dentro da pasta do projeto, tem um arquivo chamado `Makefile`, que é onde está o script. A maioria das ferramentas e bibliotecas para trabalhar com C++ são feitas exclusivamente para Linux. No caso do Make, tem uma [Versão Para Windows](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download?use_mirror=sinalbr&download), mas eu recomendo mudar pro Linux quando possível. Depois de ter instalado ele, deve ser possível chamá-lo diretamente pela linha de comando (talvez seja necessário editar as variáveis de ambiente pra incluir o caminho da ferramente Make). Dentro da pasta do projeto, execute, no terminal, `make debug` ou `make release` para compilar o projeto. Os arquivos de compilação, incluindo o executável, vão para `build/`. Caso queira executar o projeto diretamente pelo terminal, use `make ... RULE=run`.


## Escolhas de Design
### Definição vs Declaração

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

### `#pragma once`

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


### Boas Práticas
#### Nomes Descritivos e Claros

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


#### Espaçamento Adequado

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


#### Localização de Certos Operadores e Blocos de Código
##### Blocos

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

##### Operadores


Outra pergunta, qual você acha o certo?:

`Piece* piece`/`std::string& text`

ou

`Piece *piece`/`std::string &text`

A resposta pra esse caso também é a mesma da de cima: gosto pessoal.
Minha recomendação pessoal é o primeiro caso, pois acho que faz mais sentido. O importante é ser consistente e não variar no estilo.


#### Comentários

Comentários servem para literalmente adicionar algum texto explicativo em algum lugar do código. Todo comentário é ignorado pelo compilador e serve apenas para propósitos descritivos e de documentação. Uma vez eu vi uma frase que dizia que todo código deve ser compreensível mesmo sem comentários. Isso significa que, caso vá adicionar um comentário em algum lugar, veja se consegue alterar o próprio código a fim de torná-lo autoexplicativo, como melhorar o nome de uma variável, extrair um trecho de código para uma função, etc. Essa regrinha tem excessões, já que tem alguns casos onde realmente se precisa de comentários para uma melhor compreensão, como é o caso de funções completamente baseadas em matemática.


#### Indentação

A indentação é um recurso opcional adotado por praticamente todas as linguagens para organizar melhor blocos de código. Talvez você esteja se perguntando o porquê do "opcional", a verdade é que você pode concluir um projeto inteiro sem nunca clicar no botão `Enter` do seu teclado, ou seja, sem quebra de linha. Isso acontece porque o compilador não se importa com os espaços e quebra de linhas que nós programadores criamos, mas isso não vem ao caso. Parece irônico o que vou falar, mas sempre tente evitar a indentação. Muitas vezes, muitos graus de indentação pode deixar o código mais difícil de ler. Não quero dizer que você ira escrever da seguinte forma:

```C++
if (condition)
thisIsMyCoolFunction();
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


#### Responsabilidade de Código

Toda função e classe deve fazer exatamente o que seu nome sugere, nada mais nada menos. Isso cria código que chamamos de responsável, pois faz apenas o que deve fazer. No código original, você misturou a lógica do tabuleiro com a lógica de printar o tabuleiro na tela na mesma classe. É recomendável separar a lógica de mostrar alguma coisa para o usuário (via terminal ou UI) da lógica do software em si, então eu recomendaria a criação de uma classe separada (não precisa ser necessariamente uma classe) contendo a lógica de printar coisas, como foi feito no código reformulado que será analisado mais adiante.


#### Funções e Métodos Pequenos e Objetivos

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


#### Estrutura de uma Classe Padrão

A seguir está a ordem de diferentes items de uma classe. Seguir essa ordem é opcional e depende do seu gosto, mas acho interessante adotá-la. Cada comentário é uma seção; cada seção pode possuir os delimitadores de visibilidade `public`, `protected` ou `private`, que podem ser definidos aonde o programador quiser.

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


#### Getters e Setters

Geralmente, uma classe possui ao menos uma propriedade que serve para armazenar valores relacionadas à instância da classe. No entanto, é uma boa prática sempre definir as propriedades de uma classe como privadas, limitando seu acesso, que deve ser realizado através de métodos auxiliares chamados de getters e setters. Um getter é um método público que retorna o valor de uma propriedade não-pública, enquanto um setter é um método que modifica o valor de uma propriedade não-pública. Note que nem toda propriedade não-pública precisa ter um getter ou um setter. As vezes o programador realmente quer que uma propriedade seja totalmente privada ou protegida. Exemplo de uma classe com getters e setters:

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


#### Nomenclatura de Membros de Classes

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


## Análise do Código Reformulado

A seguir, analisarei o código novo que reformulei baseado no seu original. Fiz isso principalmente pra criar esse arquivo de explicação, no qual tenho como objetivo lhe ensinar tanto alguns conceitos da própria linguagem C++ quanto alguns padrões e recomendações de design e código limpo. Irei fornecer links de documentação caso você queira saber mais sobre alguma funcionalidade em específica, as informações aqui serão resumidas. O site de minha escolha de documentação será o da Microsoft, e caso você não consiga entender muito bem com base na descrição deles (concordo que é meio complexo), utilizar o ChatGPT ou perguntar pra mim mesmo é uma boa ideia.


### src/main.cpp

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

Esse é o arquivo principal, que contém a função principal que é chamada ao rodar o projeto. Dentro da função `main`, eu instancio dois objetos: `Board board` e `BoardRenderer renderer`. Aplicando o conceito de responsabilidade de código, não posso botar a lógica de printar coisas no terminal na classe `Board`, que deve ser utilizada exclusivamente para a lógica do tabuleiro em si. Por isso as duas classes, `Board`, que é o tabuleiro, e `BoardRenderer`, que contém a lógica que printa o tabuleiro no terminal. Na inicialização do mesmo: `BoardRenderer renderer(board, ColorPalette::defaultTheme());`, temos a parte `(board, ColorPalette::defaultTheme())`. Perceba `ColorPalette::defaultTheme()`: Seria interessante criar a funcionalidade de diversos temas de cores para o tabuleiro e peças, então criei essa [Classe Estática](#classes-estaticas), que contém a cor para as casas e peças. No seu código original, vi que utilizou um método `Tabuleiro::inicializar()` para inicializar o tabuleiro, sendo que você poderia ter utilizado o construtor da classe, que é a maneira mais adequada e recomendada para inicializar alguma coisa relacionada ao objeto. O construtor é, em sua base, uma função, que é chamada no momento em que um novo objeto da classe é instanciado (criado). Você pode também declarar parâmetros no construtor para receber valores que podem ser utilizados para alguma coisa. [Saiba Mais Sobre Construtores](https://learn.microsoft.com/pt-br/cpp/cpp/constructors-cpp?view=msvc-170). A linhas `std::cout << renderer.render() << std::endl;` printa todo o tabuleiro no terminal, utilizando o tema atual de cores.


## Notas
### Classes Estáticas

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