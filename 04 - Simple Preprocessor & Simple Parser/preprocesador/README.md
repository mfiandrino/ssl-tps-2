Formalizar la máquina de estados como una n-upla de Preprocesador

M = {Q, E, T, qo, F}

Q = {OUT, IN}

E = {ASCII}

T = {OUT => c==('\n'||'\t'||' ') => OUT, OUT => ++nc => IN, IN => c!=('\n'||'\t'||' ') => IN, IN => ++contadores[nc] nc=0 => OUT }

qo = OUT

F = {OUT, IN}
