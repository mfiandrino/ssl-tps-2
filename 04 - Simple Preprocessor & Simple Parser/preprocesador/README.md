Formalizar la máquina de estados como una n-upla de Preprocesador

M = {}

Q = {comentarioFinDeLinea,comentarioMultilinea,posibleFinDeComentarioMultilinea, FinDeComentarioMultilinea, posibleComentario,
     aperturaComillasSimples,entreComillasSimples, cierreComillasSimples,
     aperturaComillasDobles,cierreComillasDobles,entreComillasDobles,
     d,de,def,defi,defin,define,defineEspacio,defineIdentificador,identificadorInvalido,defineIdentificadorEspacio,textoDefineInvalido,defineTexto,
      u, un, und, unde, esUndef, undefEspacio, undefIdentificador}

E = {ASCII}

T = {OUT => c==('\n'||'\t'||' ') => OUT, OUT => ++nc => IN, IN => c!=('\n'||'\t'||' ') => IN, IN => ++contadores[nc] nc=0 => OUT }

qo = OUT

F = {OUT, IN}
