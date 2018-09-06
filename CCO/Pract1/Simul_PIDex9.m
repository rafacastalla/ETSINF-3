%**********************************************************
% OBTENCION DE Ku POR PRUEBA Y ERROR
%**********************************************************

%**********************************************************
% VALORER Kc y Tu del CONTROLADOR PI
Ku= 56.2438;

Kc=(0.6*Ku)*0.075;
Tu=0.02;
Ti=(3*(Tu/2))*0.399;
Td=Tu/8;
%**********************************************************

%**********************************************************
% PARAMETROS FIJOS: MODELO, ESCALON, T
a= -0.9614;
b= 0.0349;
T=  0.01;
Escalon=3;
%**********************************************************
C0=Kc*(1+(Td/T));
C1=Kc*(-1+(Td/Ti)-(2*Td/T));
C2=Kc*(Td/T);
%Inicializar Variables
MUEST=300; y=[]; error=[]; u=[]; t=[];



%Bucle de Generación de Datos
for i=1:MUEST+1
    
    % Almacenar valor del instante actual
    t(i)=((i-1)*T);
    
    %Calculo Salida Bucle Cerrado
    if (i==1) y(i)=0;
    else y(i)=-a*y(i-1)+b*u(i-1);
    end;
    
    % Calculo error
    error(i)=Escalon-y(i);
%Modificar para realiza tambien con cont. P y PID        
    % Calculo accion de control
    if (i==1) u(i)=C0*error(i);
    elseif (i==2) u(i)=u(i-1)+C0*error(i)+C1*error(i-1);
    else  u(i)=u(i-1)+C0*error(i)+C1*error(i-1)+C2*error(i-2);
    end;
    
    %  if (u(i)>10) u(i)=10; end;
    %  if (u(i)<0) u(i)=0; end;
       
end;

% Almacenar datos en un fichero de texto
t=t'; y=y'; u=u';error=error';

figure;
plot(t,y);
title('Velocidad Motor')
figure;
plot(t,u,'r');
title('Acción de Control-Salida Controlador')