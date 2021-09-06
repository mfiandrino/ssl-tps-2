
# Maquina de Estados
Formalizar la máquina de estados como una 7-upla de Preprocesador
 

M = {E, A, A', T, e0, p0, F}


    E = {caracterComun, aperturaBracket , clausuraBracket , aperturaComillasSimples , caracterComillasSimples , clausuraComillasSimples , aperturaComillasDobles,                            caracterComillasDobles , clausuraComillasDobles , caracterContrabarraComillaSimple , caracterContrabarraComillaDoble} 
    
    A = { ASCII }
    
    A' = { { , [ , ( , } , ] , ) }
    
    T = T(CARACTER_COMUN,{,$) = { (APERTURA_BRACKET,{ )}
    
    e0 = {caracterComun}
    
    P0 = $
    
    F = {caracterComun, aperturaBracket , clausuraBracket , aperturaComillasSimples , caracterComillasSimples , clausuraComillasSimples , aperturaComillasDobles,                            caracterComillasDobles , clausuraComillasDobles , caracterContrabarraComillaSimple , caracterContrabarraComillaDoble}


    
    
    
