% Constantes de la Tarjeta
global cardID PCI_9112; % Vbles Globales (para utilizarlas en Ini_tarjetas2) 
PCI_9112=22; %Identificador que aparece en Dask.h
AD_B_10_V=1; %Identificador que aparece en Dask.h
Offset=5; % Desplazamiento para 0 Voltios en salida bipolar

% Puntero para el dato de entrada (para leer canales de entrada
DatoAI=double(0.0);
pDatoAI = libpointer('doublePtr', DatoAI);

% Se inicializa la tarjeta, y si hay error se para ejecución
if (Ini_tarjetas2~=0), return; end;

% Escritura en el canal 0 de la PCI9112 el valor 0 Voltios
calllib('PCIDask','AO_VWriteChannel',cardID,0,0/2+Offset);

% Se finaliza la tarjeta
Fin_tarjetas2;