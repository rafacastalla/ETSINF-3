%**********************************************************
% Programa de CONTROL PROPORCIONAL de la Velocidad del Motor
%**********************************************************

% Se inicializa la tarjeta, y si hay error se para ejecuci�n
if (Ini_tarjetas2~=0), return; end;

%Inicializar Variables
MUEST=1000; Vel=[]; u=[]; error=[]; Ref=[]; t=[];

% Se definen la constante K del control proporcional 
% K for the Proportional Controller
% *************************************
Ku= 56.2438;

Kc=(0.5*Ku)*0.116;
% *************************************

% Se definen la Referencia
Ref=ones(1,MUEST)*3.0; 

t0=milisec3b;

%Bucle de Generaci�n de Datos
for i=1:MUEST
    
    % Almacenar valor del instante actual
    t(i)=milisec3b-t0;
    
    % Lectura por el canal 0 (Velocidad) de la PCI9112
    calllib('PCIDask','AI_VReadChannel',cardID,0,AD_B_10_V,pDatoAI);
    Vel(i)=get(pDatoAI,'Value');
    
    % C�lculo del error / Error computation
    % *************************************************
    error(i)=Ref(i)-Vel(i);
    % *************************************************
    
    % C�lculo de la acci�n de control / Control action
    % *************************************************
     u(i)=Kc*error(i);
    % *************************************************
      
     % Saturar acci�n de control
    if (u(i)>10.0) u(i)=10.0;  end;  
    if (u(i)<0.0) u(i)=0.0;  end;   
    
    
    % Escritura en el canal 0 de la PCI9112 del valor u
    calllib('PCIDask','AO_VWriteChannel',cardID,0,u(i)/2+Offset);
    
    % Esperar 10 milisegundos
    esperah3(10-((milisec3b-t0)-t(i)));
end;

% Escritura en el canal 0 de la PCI9112 el valor 0 Voltios
calllib('PCIDask','AO_VWriteChannel',cardID,0,0/2+Offset);

Fin_tarjetas2;

% Almacenar datos en un fichero de texto
t=t'/1000; %datos1=[Ref',Vel',error',u'];
Vel=Vel'; error=error'; u=u'; Ref=Ref';

figure;
plot(t,Vel);
hold;
plot(t,Ref,'k');
figure;
plot(t,u,'r');
figure;
plot(t,error,'k');

