%**********************************************************
% Generación de datos para la identificación LSQ
%**********************************************************

% Se inicializa la tarjeta, y si hay error se para ejecución
if (Ini_tarjetas2~=0), return; end;

%Inicializar Variables
MUEST=1000; Vel=[]; u=[]; t=[];

% Cargar el fichero de datos PRBS13.txt
load prbs13.txt
valor_medio=5.0; desviacion=1.0; estiramiento=5.0;

t0=milisec3b;

%Bucle de Generación de Datos
for i=1:MUEST
    
    % Almacenar valor del instante actual
    t(i)=milisec3b-t0;
    
    % Lectura por el canal 0 (Velocidad) de la PCI9112
    calllib('PCIDask','AI_VReadChannel',cardID,0,AD_B_10_V,pDatoAI);
    Vel(i)=get(pDatoAI,'Value');
      
    % Acción de control
    u(i)=valor_medio+sign(prbs13(ceil(i/estiramiento))-0.5)*desviacion; 
       
    % Escritura en el canal 0 de la PCI9112 del valor u
    calllib('PCIDask','AO_VWriteChannel',cardID,0,u(i)/2+Offset);
    
    % Esperar 10 milisegundos
    esperah3(10-((milisec3b-t0)-t(i)));
end;

% Escritura en el canal 0 de la PCI9112 el valor 0 Voltios
calllib('PCIDask','AO_VWriteChannel',cardID,0,0/2+Offset);

Fin_tarjetas2;

% Almacenar datos en un variables t2, Vel2, u2
t2=t'/1000; Vel2=Vel'; u2=u';

figure;
plot(t2,Vel2);
hold;
plot(t2,u2,'r');