%**********************************************************
% CONTROL PROPORCIONAL INTEGRAL de la Velocidad del Motor
%**********************************************************

% Se inicializa la tarjeta, y si hay error se para ejecución
if (Ini_tarjetas2~=0), return; end;

%Inicializar Variables
MUEST=1000; Vel=[]; u=[]; error=[]; Ref=[]; t=[];

%**********************************************************
% VALORER Kc y Tu del CONTROLADOR PI
Ku= 56.2438;

Kc=(0.6*Ku)*0.07;
Tu=0.02;
Ti=3*(Tu/2);
Td=Tu/8;

%**********************************************************
C0=Kc*(1+(Td/T));
C1=Kc*(-1+(Td/Ti)-(2*Td/T));
C2=Kc*(Td/T);


% Se definen la Referencia
Ref=ones(1,MUEST)*3.0; 

t0=milisec3b;

%Bucle de Generación de Datos
for i=1:MUEST
    
    % Almacenar valor del instante actual
    t(i)=milisec3b-t0;
    
    % Lectura por el canal 0 (Velocidad) de la PCI9112
    calllib('PCIDask','AI_VReadChannel',cardID,0,AD_B_10_V,pDatoAI);
    Vel(i)=get(pDatoAI,'Value');
     
    % Cálculo del error / Error computation
    % *************************************************
      error(i)=Ref(i)-Vel(i);
    % *************************************************
    
    % Cálculo de la acción de control / Control action
    % *************************************************
    if (i==1) u(i)=C0*error(i);
    elseif (i==2) u(i)=u(i-1)+C0*error(i)+C1*error(i-1);
    else  u(i)=u(i-1)+C0*error(i)+C1*error(i-1)+C2*error(i-2);
    end;
    % *************************************************
      
     % Saturar acción de control
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