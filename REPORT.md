# Rapport

## Phase 1

### Gestion des operateurs de base

Dans cette partie, j'ai simplement appliqué l'algorithme de Shunting-Yard :
 - `split` de la chaine de caractère représentant l'éxpression.
 - `stringToTokens` pour obtenir les tokens correspondant a chaque "morceaux" de l'expression.
 - `rpnFromString` apelle `stringToTokens` et met ces tokens dans l'ordre de la notation polonaise inverse.
 - `Expr::eval` récupère les token en RPN et evalue ainsi l'expression.

Un matching d'expression reguliere me permet de filtrer les expressions a evaluer : 
```cpp
expr.m_hasSemi = std::regex_match(expr.m_expr, std::regex(".*;"));
```

### Gesion des variables

Au sein de la classe `Expr`, j'ai déclaré une map statique comportant tous les noms de variables associés à une valeur. Lorsqu'une variable est parsed dans une expression, sa valeur est retrouvée via un `std::map::at`. Lorsque le signe `=` est utilisé, soit on ajoute une nouvelle variable a la map (avec `std::map::insert`), soit la variable existe déjà et sa valeur est mise à jour (avec `std::map::at`).

## Phase 2

### Gestion des fonctions

J'ai décidé de créer un nouveau Token, `TokenFun` prenant en attribut un nom. De la même maniere que les variables, une map statique comporte tous les noms de fonctions associés à une valeur (de type `std::function<double(std::deque<double>)>`). Je pouvais donc traiter la fonction comme un token et simplement l'appliquer au premier TokenNum dans la pile de valeurs. Cela n'est plus vrai lorsque le nombre d'arguments est supérieur a 1 ET variable. Effectivement, en plus de devoir utiliser une `std::deque` pour la liste d'arguments, j'ai utilisé un marqeur dans le RPN afin de retrouver le dernier arguments de la fonction appelée :
```txt
> 2 + pow(2, 2)
> RPN >> 2 ; 2 2 pow +
	   ^
```

## Phase 3

### Spécification partielle

De manière semblable aux fonctions de base, j'ai créé une nouvelle map prenant une chaine de caractere en clé (le nom de la fonction), et une autre chaine de caractères en valeur (la fonction à identifier partiellement).

Dans la map, la fonction a identifier sera mise en forme pour pouvoir etre directement utilisée comme expression apres y avoir ajouté le dernier argument.
Par exemple, si l'utilisateur entre `l = lerp(a, b);`, la map de fonctions utilisateurs se verra ajouter le couple `"l", "lerp(a, b,"`.

Remarque : la suppression de la parenthese fermante et l'ajout d'une virgule permet, lorsque l'utilisateur entre `l(x)` d'évaluer l'expression dont la chaine de caractere est : `lerp (a, b, x)` (`"lerp(a, b," + "x" + ")"`)
