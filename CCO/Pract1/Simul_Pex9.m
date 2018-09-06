%**********************************************************
% OBTENCION DE Ku POR PRUEBA Y ERROR
% Diseñar y simula un controlador P que, manteniendo la condición
%  u(k)[0,10], haga que la velocidad del motor se estabilice más pronto
%**********************************************************

%**********************************************************
% VALORER Kc  del CONTROLADOR P
Ku= 56.2438;

Kc=(0.5*Ku)*0.107;


%**********************************************************

%**********************************************************
% PARAMETROS FIJOS: MODELO, ESCALON, T
a= -0.9614;
b= 0.0349;
T=  0.01;
Escalon=3;
%**********************************************************

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
    u(i)=Kc*error(i);
  
    
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