digraph Bracket{
    
caracterComun -> aperturaBracket [label = " c == '{' or '[' or '(', \n push(c) "];
caracterComun -> clausuraBracket [label = " c == '}' or ']' or ')', && atenderClausuraBracket(c) "];
caracterComun -> bracketsNoBalanceados [label = " c == '}' or ']' or ')' && !(atenderClausuraBracket(c)) "];
caracterComun -> aperturaComillasSimples [label = " c == \' "];
caracterComun -> aperturaComillasDobles [label = " c == \" "];
caracterComun -> caracterComun [label = " c == EOC "];

aperturaBracket -> aperturaBracket [label = " c == '{' or '[' or '(', \n push(c) "];
aperturaBracket -> clausuraBracket [label = " c == '}' or ']' or ')', && atenderClausuraBracket(c) "];
aperturaBracket -> bracketsNoBalanceados [label = " c == '}' or ']' or ')' && !(atenderClausuraBracket(c)) "];
aperturaBracket -> aperturaComillasSimples [label = " c == \' "];
aperturaBracket -> aperturaComillasDobles [label = " c == \" "];
aperturaBracket -> caracterComun [label = " c == EOC "];

clausuraBracket -> aperturaBracket [label = " c == '{' or '[' or '(', \n push(c) "];
clausuraBracket -> clausuraBracket [label = " c == '}' or ']' or ')', && atenderClausuraBracket(c) "];
clausuraBracket -> bracketsNoBalanceados [label = " c == '}' or ']' or ')' && !(atenderClausuraBracket(c)) "];
clausuraBracket -> aperturaComillasSimples [label = " c == \' "];
clausuraBracket -> aperturaComillasDobles [label = " c == \" "];
clausuraBracket -> caracterComun [label = " c == EOC "];

aperturaComillasSimples -> caracterContrabarraComillaSimple [label = " c == '\\' "];
aperturaComillasSimples -> errorComillasDentroDeComillasSimples [label = " c == '\'' or '\"' "];
aperturaComillasSimples -> caracterComillasSimples [label = " c == EOC "];

caracterComillasSimples -> clausuraComillasSimples [label = " c == '\'' "];
caracterComillasSimples -> errorMasDeUnCaracterEnComillasSimples [label = " c == EOC "];

clausuraComillasSimples -> aperturaComillasDobles [label = " c == '\"' "];
clausuraComillasSimples -> aperturaComillasSimples [label = " c == '\'' "];
clausuraComillasSimples -> aperturaBracket [label = " c == '{' or '[' or '(', \n push(c) "];
clausuraComillasSimples -> clausuraBracket [label = " c == '}' or ']' or ')', && atenderClausuraBracket(c) "];
clausuraComillasSimples -> bracketsNoBalanceados [label = " c == '}' or ']' or ')' && !(atenderClausuraBracket(c)) "];
clausuraComillasSimples -> caracterComun [label = " c == EOC "];

aperturaComillasDobles -> caracterContrabarraComillaDoble [label = " c == '\\' "];
aperturaComillasDobles -> clausuraComillasDobles [label = " c == '\"' "];
aperturaComillasDobles -> caracterComillasDobles [label = " c == EOC "];

caracterComillasDobles -> caracterContrabarraComillaDoble [label = " c == '\\' "];
caracterComillasDobles -> clausuraComillasDobles [label = " c == '\"' "];
caracterComillasDobles -> caracterComillasDobles [label = " c == EOC "];

clausuraComillasDobles -> aperturaComillasDobles [label = " c == '\"' "];
clausuraComillasDobles -> aperturaComillasSimples [label = " c == '\'' "];
clausuraComillasDobles -> aperturaBracket [label = " c == '{' or '[' or '(', \n push(c) "];
clausuraComillasDobles -> clausuraBracket [label = " c == '}' or ']' or ')', && atenderClausuraBracket(c) "];
clausuraComillasDobles -> bracketsNoBalanceados [label = " c == '}' or ']' or ')' && !(atenderClausuraBracket(c)) "];
clausuraComillasDobles -> caracterComun [label = " c == EOC "];

caracterContrabarraComillaSimple -> caracterComillasSimples;

caracterContrabarraComillaDoble -> caracterComillasDobles;
}


