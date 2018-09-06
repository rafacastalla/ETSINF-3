%**********************************************************
% Programa de Prueba del Motor de Corriente Continua
%**********************************************************

% Se inicializa la tarjeta, y si hay error se para ejecución
if (Ini_tarjetas2~=0), return; end;

%Inicializar Variables
MUEST=1000; Vel=[]; u=[]; t=[];

t0=milisec3b;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ASIGNAR VALOR DEL ESCALON (entre 0..8) 
v_ent= 2;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Bucle de Generación de Datos
for i=1:MUEST
    
    % Almacenar valor del instante actual
    t(i)=milisec3b-t0;
    
    % Lectura por el canal 0 (Velocidad) de la PCI9112
    calllib('PCIDask','AI_VReadChannel',cardID,0,AD_B_10_V,pDatoAI);
    Vel(i)=get(pDatoAI,'Value');
    
    % Escritura en el canal 0 de la PCI9112 del valor u
    calllib('PCIDask','AO_VWriteChannel',cardID,0,v_ent/2+Offset);
    
    % Esperar 10 milisegundos
    esperah3(10-((milisec3b-t0)-t(i)));
end;

% Escritura en el canal 0 de la PCI9112 el valor 0 Voltios
calllib('PCIDask','AO_VWriteChannel',cardID,0,0/2+Offset);

Fin_tarjetas2;

% Almacenar datos en variables t1, Vel1, u1
t1=t'/1000; Vel1=Vel'; u1=v_ent*ones(length(Vel1),1);

figure;
plot(t1,Vel1);
hold;
plot(t1,u1,'r');
