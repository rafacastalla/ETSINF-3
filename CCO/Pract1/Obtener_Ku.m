%**********************************************************
% OBTENCION DE Ku POR PRUEBA Y ERROR
%**********************************************************

%**********************************************************
% PROPONER VALOR DE Ku
Ku= 56.2438;
%**********************************************************

%**********************************************************
% PARAMETROS FIJOS: MODELO, ESCALON, T
a= -0.9614;
b= 0.0349;
T=  0.01;
Escalon=3;
%**********************************************************

%Inicializar Variables
MUEST=50; y=[]; error=[]; u=[]; t=[];

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
        
    % Calculo accion de control
    u(i)=Ku*error(i);
    
       
end;

% Almacenar datos en un fichero de texto
t=t'; y=y'; u=u';error=error';

figure;
plot(t,y);