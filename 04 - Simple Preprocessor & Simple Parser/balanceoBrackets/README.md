
# Maquina de Estados
Formalizar la máquina de estados como una 7-upla de Preprocesador
 

M = {E, A, A', T, e0, p0, F}


    E = {caracterComun, aperturaBracket , clausuraBracket , aperturaComillasSimples , caracterComillasSimples , clausuraComillasSimples , aperturaComillasDobles,                            caracterComillasDobles , clausuraComillasDobles , caracterContrabarraComillaSimple , caracterContrabarraComillaDoble} 
    
    A = { ASCII }
    
    A' = { { , [ , ( , } , ] , ) }
    
    T ={
         caracterComun -> c == '{' or '[' or '(', \n push(c)-> aperturaBracket,
         caracterComun -> c == '}' or ']' or ')', && atenderClausuraBracket(c)->clausuraBracket,
         caracterComun -> c == '}' or ']' or ')' && !(atenderClausuraBracket(c))->bracketsNoBalanceados,
         caracterComun ->c == \' ->aperturaComillasSimples,
         caracterComun -> c == \" ->aperturaComillasDobles,
         caracterComun ->  c == EOC->caracterComun ,
         aperturaBracket ->c == '{' or '[' or '(', \n push(c) ->aperturaBracket,
         aperturaBracket ->  c == '}' or ']' or ')', && atenderClausuraBracket(c)->clausuraBracket,
         aperturaBracket ->c == '}' or ']' or ')' && !(atenderClausuraBracket(c)) ->bracketsNoBalanceados ,
         aperturaBracket -> c == \' ->aperturaComillasSimples,
         aperturaBracket -> c == \"->aperturaComillasDobles,
         aperturaBracket ->  c == EOC->caracterComun,
         clausuraBracket ->c == '{' or '[' or '(', \n push(c ->aperturaBracket ,
         clausuraBracket -> c == '}' or ']' or ')', && atenderClausuraBracket(c)->clausuraBracket ,
         clausuraBracket ->c == '}' or ']' or ')' && !(atenderClausuraBracket(c))->bracketsNoBalanceados,
         clausuraBracket -> c == \' ->aperturaComillasSimples,
         clausuraBracket -> c == \"->aperturaComillasDobles,
         clausuraBracket ->c == EOC->caracterComun ,
         aperturaComillasSimples -> c == '\\' ->caracterContrabarraComillaSimple ,
         aperturaComillasSimples ->c == '\'' or '\"'->errorComillasDentroDeComillasSimples,
         aperturaComillasSimples -> c == EOC->caracterComillasSimples ,
         caracterComillasSimples ->c == '\'' ->clausuraComillasSimples,
         caracterComillasSimples ->c == EOC  ->errorMasDeUnCaracterEnComillasSimples,
         clausuraComillasSimples ->c == '\"' ->aperturaComillasDobles,
         clausuraComillasSimples -> c == '\'' ->aperturaComillasSimples,
         clausuraComillasSimples -> c == '{' or '[' or '(', \n push(c)->aperturaBracket ,
         clausuraComillasSimples ->c == '}' or ']' or ')', && atenderClausuraBracket(c) ->clausuraBracket,
         clausuraComillasSimples ->c == '}' or ']' or ')' && !(atenderClausuraBracket(c)) ->bracketsNoBalanceados,
         clausuraComillasSimples -> c == EOC->caracterComun,
         aperturaComillasDobles ->c == '\\' ->caracterContrabarraComillaDoble,
         aperturaComillasDobles -> c == '\"' ->clausuraComillasDobles,
         aperturaComillasDobles -> c == EOC ->caracterComillasDobles,
         caracterComillasDobles ->c == '\\' ->caracterContrabarraComillaDoble,
         caracterComillasDobles -> c == '\"' ->clausuraComillasDobles,
         caracterComillasDobles ->c == EOC ->caracterComillasDobles,
         clausuraComillasDobles -> c == '\"'->aperturaComillasDobles,
         clausuraComillasDobles -> c == '\'' ->aperturaComillasSimples,
         clausuraComillasDobles ->c == '{' or '[' or '(', \n push(c) ->aperturaBracket,
         clausuraComillasDobles -> c == '}' or ']' or ')', && atenderClausuraBracket(c) ->clausuraBracket,
         clausuraComillasDobles -> c == '}' or ']' or ')' && !(atenderClausuraBracket(c))->bracketsNoBalanceados,
         clausuraComillasDobles ->  c == EOC->caracterComun,
         caracterContrabarraComillaSimple -> -> caracterComillasSimples,
         caracterContrabarraComillaDoble -> -> caracterComillasDobles       
       }
    
    e0 = {caracterComun}
    
    P0 = $
    
    F = {caracterComun, aperturaBracket , clausuraBracket , aperturaComillasSimples , caracterComillasSimples , clausuraComillasSimples , aperturaComillasDobles,                            caracterComillasDobles , clausuraComillasDobles , caracterContrabarraComillaSimple , caracterContrabarraComillaDoble}


    
    
    
