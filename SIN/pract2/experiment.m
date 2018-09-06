#!/usr/bin/octave -qf

if (nargin!=3)
  printf("Usage: experiment <data> <alphas> <bes>\n");
  exit(1);
end;

# {"datos/OCR_14x14", "[.1]", "[1000]"};
# ./experiment.m OCR_14x14 "[.1 1 10 100 1000 10000 100000]" "[.1 1 10 100 1000 10000 100000]"

arg_list = argv(); # Get arguments 
data = arg_list{1}; # Get de firts argument (data)
as = str2num(arg_list{2}); # Get de second argument (a)
bs = str2num(arg_list{3}); # Get de third argument (b)

load(data); # Load data
# N -> numero de mostres que hiha
# L -> numero de columnes que hiha
[ N, L ] = size(data); # Load size of matrix data

# D -> numero de caracteristiques dels objectes.
# L tambe inclou la clase a la que pertany lobjecte
D = L-1; # Load the number of characteristics

# ll -> te les diferents clases
# C -> numero de classes
ll = unique(data(:,L));
C = numel(ll);

# Indiquem a la funcio rand quina semilla volem utilitzar
# per a que sempre que repetim el experiment ens mescle 
# les dades de la mateixa forma
rand("seed",23);
# mesclem les dades i les guardem en data altra vega
data = data(randperm(N),:);

# NTr -> numero dades per a entrenament
NTr = round(.7*N);

# M -> numero de mostres per a test
M = N - NTr;

# te -> almacenem les dades de test
te = data(NTr+1:N,:);

printf("       a        b   E   k Ete  Ete (%%)    Ite (%%)\n");
printf("-------- -------- --- --- --- -------- ----------\n");

for a=as # a=[.1 1 10 100 1000 10000 100000]

  for b=bs # b=[.1 1 10 100 1000 10000 100000]
    
    # Cridem al perceptro (dades entrenament, b, a, iteracions, iw=vector de pesos inicial)
    # w -> vector de pesos entrenat
    # E -> numero de erros
    # k -> iteracions
    [w, E, k] = perceptron(data(1:NTr,:), b, a);

    # creem una matriu tot a ceros (en realitat un vector perque te un component)
    rl = zeros(M, 1);
    
    # Recorregem les mostres de test i les clasifiquem
    # en rl tenim la clase de cada dada segons les funcions entrenades
    for n=1:M
      # obtenim la clase en la qual sha clasificat la dada
      rl(n) = ll(linmach(w,[1 te(n, 1:D)]')); #'
    end
    
    # comprovem que cada mostra esta ben clasificada
    # m -> esta matriu ens diu en que classe sha clasificat cada dada
    [nerr m] = confus(te(:, L), rl);

    # numero errors / mostres de test
    perr = nerr/M;

    # Interval de confiaca al 95%
    s = sqrt(perr* (1-perr)/M);
    r = 1.96*s;

    # normalitzem els resultats per a mostrarlos
    pe = perr*100;
    ies = (perr-r)*100;
    idt = (perr+r)*100;

    if(ies < 0) ies = 0; end

    printf("%8.1f %8.1f %3d %3d %3d      %1.1f [%1.1f, %1.1f]\n", a, b, E, k, nerr, pe, ies, idt);

  end
  
  printf("\n");
end

printf("\n");
printf("a: Alpha utilitzada\n");
printf("b: Beta utilitzada\n");
printf("E: Numero de error produits en l'ultima iteracio de perceptro.\n");
printf("k: Iteracions nessesaries\n");
printf("Ete: Error estimat\n");
printf("Ete (%%): Percentage de error\n");
printf("Ite (%%): Interval de confiança\n");

